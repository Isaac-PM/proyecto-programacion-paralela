#include "single_thread.hpp"
#include "multi_thread.hpp"

int main(int argc, char *argv[])
{
    // -----------------------------------------
    // Virus samples
    fstream virusTimeResults(VIRUS_TIME_RESULTS, ios::out);
    virusTimeResults << "Threads,Average Time\n";
    double averageTime = 0.0;
    testSingleThreaded("VIRUS", VIRUS_SAMPLES_NAMES, VIRUS_SAMPLES_PATH, VIRUS_SAMPLES_RESULTS_SINGLE_THREADED, averageTime);
    virusTimeResults << "1," << averageTime << '\n';
    for (int i = 5; i <= NUMBER_OF_THREADS; i += THREAD_STRIDE)
    {
        testMultiThreaded("VIRUS", VIRUS_SAMPLES_NAMES, VIRUS_SAMPLES_PATH, VIRUS_SAMPLES_RESULTS_MULTI_THREADED, i, averageTime);
        virusTimeResults << i << "," << averageTime << '\n';
    }
    virusTimeResults.close();
    cout << '\n';

    // -----------------------------------------
    // Clean samples
    fstream cleanTimeResults(CLEAN_TIME_RESULTS, ios::out);
    cleanTimeResults << "Threads,Average Time\n";
    testSingleThreaded("CLEAN", CLEAN_SAMPLES_NAMES, CLEAN_SAMPLES_PATH, CLEAN_SAMPLES_RESULTS_SINGLE_THREADED, averageTime);
    cleanTimeResults << "1," << averageTime << '\n';
    for (int i = 5; i <= NUMBER_OF_THREADS; i += THREAD_STRIDE)
    {
        testMultiThreaded("CLEAN", CLEAN_SAMPLES_NAMES, CLEAN_SAMPLES_PATH, CLEAN_SAMPLES_RESULTS_MULTI_THREADED, i, averageTime);
        cleanTimeResults << i << "," << averageTime << '\n';
    }
    cleanTimeResults.close();

    return EXIT_SUCCESS;
}
