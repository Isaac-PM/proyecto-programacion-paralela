#include "common.hpp"

using namespace std;

void countBytesMultiThreaded(const char *filename, int threadNumber, vector<ByteCount> &bytes)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }

    long fileSize = getFileSizeIn(SizeUnit::BYTES, file);
    int bytesPerThread = fileSize / threadNumber;
    int bytesForLastThread = fileSize % threadNumber + bytesPerThread;

    int globalByteCounts[256] = {0};
    unsigned int **byteCounts = new unsigned int *[threadNumber];

    for (int i = 0; i < threadNumber; ++i)
    {
        byteCounts[i] = new unsigned int[256]{0};
    }

#pragma omp parallel num_threads(threadNumber)
    {
        int threadId = omp_get_thread_num();
        FILE *fileLocal = fopen(filename, "rb");
        if (!fileLocal)
        {
            cerr << "Error opening file in thread " << threadId << endl;
#pragma omp cancel parallel
        }

        int start = threadId * bytesPerThread;
        int end = (threadId == threadNumber - 1) ? start + bytesForLastThread : start + bytesPerThread;

        fseek(fileLocal, start, SEEK_SET);

        for (int i = start; i < end; ++i)
        {
            int byte = fgetc(fileLocal);
            if (byte != EOF)
            {
                byteCounts[threadId][byte]++;
            }
        }

        fclose(fileLocal);
    }

    for (int i = 0; i < threadNumber; ++i)
    {
        for (int j = 0; j < 256; ++j)
        {
            bytes[j].count += byteCounts[i][j];
        }
        delete[] byteCounts[i];
    }
    delete[] byteCounts;

    fclose(file);
}

void testMultiThreaded(string sampleType, string sampleNamesFile, string samplePath, string resultsFile, int threadNumber, double &averageTime)
{
    double totalTime = 0.0;
    unsigned int numberOfSamples = 0;
    bool saveRunInfo = true;

    cout << "Multi-threaded version with " << sampleType << " samples and " << threadNumber << " threads\n";

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
            startTime = omp_get_wtime();
            countBytesMultiThreaded((samplePath + sampleName).c_str(), threadNumber, bytes);
            endTime = omp_get_wtime();
            totalTime += endTime - startTime;
            numberOfSamples++;
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
    cout << "(Multi-threaded version with " << sampleType << " samples) Average time reading one file: "
         << averageTime << "s, each file was read " << NUMBER_OF_TESTS << " times\n";
}