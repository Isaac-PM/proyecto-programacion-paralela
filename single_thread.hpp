#include "common.hpp"

void countBytesSingleThreaded(FILE *file, vector<ByteCount> &bytes)
{
    long fileSize = getFileSizeIn(SizeUnit::BYTES, file);

    unsigned char byte;
    // Iterate over each byte in the file
    for (size_t i = 0; i < fileSize; i++)
    {
        byte = fgetc(file);
        if (byte == EOF)
        {
            break;
        }
        bytes[byte].count++; // Increment the count of the byte, each index represents a byte value
    }
}

void testSingleThreaded(string sampleType, string sampleNamesFile, string samplePath, string resultsFile, double &averageTime)
{
    double totalTime = 0.0;
    unsigned int numberOfSamples = 0;
    bool saveRunInfo = true;

    for (int i = 0; i < NUMBER_OF_TESTS; i++)
    {
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
    averageTime = totalTime / numberOfSamples;
    stringstream ss;
    ss << "[Single-threaded version with " << sampleType << " samples]\n";
    ss << "\tNumber of threads: 1\n";
    ss << "\tNumber of samples: " << (numberOfSamples / NUMBER_OF_TESTS) << '\n';
    ss << "\tAverage time reading one file: " << averageTime << "s, each file was read " << NUMBER_OF_TESTS << " times\n";
    cout << ss.str();
}