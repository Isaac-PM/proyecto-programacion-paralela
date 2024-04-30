#include "common.hpp"

void countBytesSingleThreaded(FILE *file, vector<ByteCount> &bytes)
{
    long fileSize = getFileSizeIn(SizeUnit::BYTES, file);

    unsigned char byte;

    for (size_t i = 0; i < fileSize; i++)
    {
        byte = fgetc(file);
        if (byte == EOF)
        {
            break;
        }
        bytes[byte].count++;
    }
}

void testSingleThreaded(string sampleType, string sampleNamesFile, string samplePath, string resultsFile)
{
    double totalTime = 0.0;
    unsigned int numberOfSamples = 0;
    bool saveRunInfo = true;

    cout << "Single-threaded version with " << sampleType << " samples\n";

    for (int i = 0; i < NUMBER_OF_TESTS; i++)
    {
        cout << "(" << sampleType << ") Test " << i + 1 << '\n';
        vector<ByteCount> bytes;
        initByteCountVector(bytes);
        fstream samplesFile(sampleNamesFile, ios::in);
        string sampleName;

        while (samplesFile >> sampleName)
        {
            double startTime = 0.0, endTime = 0.0;
            FILE *sampleFile = fopen((samplePath + sampleName).c_str(), "rb");
            if (sampleFile != nullptr)
            {
                startTime = omp_get_wtime();
                countBytesSingleThreaded(sampleFile, bytes);
                endTime = omp_get_wtime();
                totalTime += endTime - startTime;
                numberOfSamples++;
                fclose(sampleFile);
            }
        }

        sortByteCountVector(bytes);
        if (saveRunInfo)
        {
            fstream resultsCSV(resultsFile, ios::out);
            resultsCSV << "Byte,Count\n";
            for (ByteCount byte : bytes)
            {
                resultsCSV << byte.byteId << "," << byte.count << '\n';
            }
            resultsCSV.close();
            saveRunInfo = false;
        }
    }

    cout << "(Single-threaded version with " << sampleType << " samples) Average time reading one file: "
         << totalTime / numberOfSamples << "s, each file was read " << NUMBER_OF_TESTS << " times\n";
}

int main(int argc, char *argv[])
{
    // -----------------------------------------
    // Virus samples
    testSingleThreaded("VIRUS", VIRUS_SAMPLES_NAMES, VIRUS_SAMPLES_PATH, VIRUS_SAMPLES_RESULTS_SINGLE_THREADED);

    cout << '\n';

    // -----------------------------------------
    // Clean samples
    testSingleThreaded("CLEAN", CLEAN_SAMPLES_NAMES, CLEAN_SAMPLES_PATH, CLEAN_SAMPLES_RESULTS_SINGLE_THREADED);

    return EXIT_SUCCESS;
}