#ifndef COMMON_HPP
#define COMMON_HPP

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

// -----------------------------------------
// -- Constants
const string VIRUS_SAMPLES_NAMES = "filenames/virus_samples_names.txt";
const string VIRUS_SAMPLES_RESULTS_SINGLE_THREADED = "results/virus_samples_results_single_threaded.csv";
const string VIRUS_SAMPLES_RESULTS_MULTI_THREADED = "results/virus_samples_results_multi_threaded.csv";
const string VIRUS_TIME_RESULTS = "results/virus_time_results.csv";
const string VIRUS_SAMPLES_PATH = "./virus_samples/";

const string CLEAN_SAMPLES_NAMES = "filenames/clean_samples_names.txt";
const string CLEAN_SAMPLES_RESULTS_SINGLE_THREADED = "results/clean_samples_results_single_threaded.csv";
const string CLEAN_SAMPLES_RESULTS_MULTI_THREADED = "results/clean_samples_results_multi_threaded.csv";
const string CLEAN_TIME_RESULTS = "results/clean_time_results.csv";
const string CLEAN_SAMPLES_PATH = "./clean_samples/";

const unsigned int NUMBER_OF_BYTES = 256;
const unsigned int NUMBER_OF_TESTS = 3;
const unsigned int NUMBER_OF_THREADS = 50;
const unsigned int THREAD_STRIDE = 5;

// -----------------------------------------
// -- Structs
struct ByteCount
{
    unsigned int byteId;
    unsigned int count;
};

bool byteCountCompare(const ByteCount &a, const ByteCount &b)
{
    return a.count > b.count;
}

void byteCountPrint(ByteCount byte)
{
    cout << "Byte: " << byte.byteId << " Count: " << byte.count << '\n';
}

void initByteCountVector(vector<ByteCount> &bytes)
{
    for (size_t i = 0; i < NUMBER_OF_BYTES; i++)
    {
        ByteCount byteCount;
        byteCount.byteId = i;
        byteCount.count = 0;
        bytes.push_back(byteCount);
    }
}

void sortByteCountVector(vector<ByteCount> &bytes)
{
    sort(bytes.begin(), bytes.end(), byteCountCompare);
}

// -----------------------------------------
// -- Enums
enum SizeUnit
{
    BYTES = 1,
    BITS = 8
};

long getFileSizeIn(SizeUnit unit, FILE *file)
{
    if (file == nullptr)
    {
        return -1;
    }
    long currentPosition = ftell(file);
    if (currentPosition == -1L)
    {
        return -1;
    }
    if (fseek(file, 0, SEEK_END) != 0)
    {
        return -1;
    }
    long size = ftell(file);
    if (size == -1L)
    {
        return -1;
    }
    if (fseek(file, currentPosition, SEEK_SET) != 0)
    {
        return -1;
    }
    return size * unit;
}

#endif // COMMON_HPP