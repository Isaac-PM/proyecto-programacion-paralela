#include "single_thread.hpp"
#include "multi_thread.hpp"

int main(int argc, char *argv[])
{
    // -----------------------------------------
    // Virus samples
    double averageTime = 0.0;
    try
    {
        fstream virusTimeResults(VIRUS_TIME_RESULTS, ios::out);
        virusTimeResults << "Threads,Average_Time\n";
        cout << "Reading virus samples...\n";
        testSingleThreaded("VIRUS", VIRUS_SAMPLES_NAMES, VIRUS_SAMPLES_PATH, VIRUS_SAMPLES_RESULTS_SINGLE_THREADED, averageTime);
        virusTimeResults << "1," << averageTime << '\n';
        for (int i = 5; i <= NUMBER_OF_THREADS; i += THREAD_STRIDE)
        {
            testMultiThreaded("VIRUS", VIRUS_SAMPLES_NAMES, VIRUS_SAMPLES_PATH, VIRUS_SAMPLES_RESULTS_MULTI_THREADED, i, averageTime);
            virusTimeResults << i << "," << averageTime << '\n';
        }
        virusTimeResults.close();
        cout << '\n';
    }
    catch (...)
    {
        cerr << "Error while running virus samples tests\n";
    }

    // -----------------------------------------
    // Clean samples
    try
    {
        fstream cleanTimeResults(CLEAN_TIME_RESULTS, ios::out);
        cleanTimeResults << "Threads,Average_Time\n";
        averageTime = 0.0;
        cout << "Reading clean samples...\n";
        testSingleThreaded("CLEAN", CLEAN_SAMPLES_NAMES, CLEAN_SAMPLES_PATH, CLEAN_SAMPLES_RESULTS_SINGLE_THREADED, averageTime);
        cleanTimeResults << "1," << averageTime << '\n';
        for (int i = 5; i <= NUMBER_OF_THREADS; i += THREAD_STRIDE)
        {
            testMultiThreaded("CLEAN", CLEAN_SAMPLES_NAMES, CLEAN_SAMPLES_PATH, CLEAN_SAMPLES_RESULTS_MULTI_THREADED, i, averageTime);
            cleanTimeResults << i << "," << averageTime << '\n';
        }
        cleanTimeResults.close();
    }
    catch (...)
    {
        cerr << "Error while running clean samples tests\n";
    }

    return EXIT_SUCCESS;
}
