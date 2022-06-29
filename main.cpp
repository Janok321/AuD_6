#include <cstring>
#include "helperFunctions.h"
#include "mergesortRand.h"
#include <chrono>
#include <vector>


class PerformanceTest {
private:
    double minExecutionTime;
    double maxExecutionTime;
    double totalExecutionTime;
    std::string algorithmName;

public:
    PerformanceTest() {
        this->minExecutionTime = 1000;
        this->maxExecutionTime = 0;
        this->totalExecutionTime = 0;
        this->algorithmName = "";
    };

    double getMinExecutionTime() {
        return this->minExecutionTime;
    }

    double getMaxExecutionTime() {
        return this->maxExecutionTime;
    }

    double getTotalExecutionTime() {
        return this->totalExecutionTime;
    }

    const std::string& getAlgorithmName() {
        return this->algorithmName;
    }

    void setAlgorithmName(std::string name) {
        this->algorithmName = name;
    }

    void processResult(std::chrono::high_resolution_clock::time_point startTime, std::chrono::high_resolution_clock::time_point endTime) {
        std::chrono::duration<double, std::milli> duration = (endTime - startTime);
        double execTime = duration.count();
        this->totalExecutionTime += execTime;
        if(execTime < this->minExecutionTime) {
            this->minExecutionTime = execTime;
            return;
        } else if(execTime > this->maxExecutionTime) {
            this->maxExecutionTime = execTime;
            return;
        }
    }
};

class PerformanceComparison {
private:
    int* baseArray;
    int arrayLength;
    int testsetSize;
    std::vector<PerformanceTest*> testResults;
public:
    PerformanceComparison(int arrayLength, int testsetSize) {
        this->arrayLength = arrayLength;
        this->testsetSize = testsetSize;
        this->baseArray = (int*)malloc(sizeof(int) * this->arrayLength * this->testsetSize);
        generateRandomIntArray(this->baseArray, this->arrayLength * this->testsetSize);
    }

    ~PerformanceComparison() {
        free(this->baseArray);
        for(unsigned int i = 0; i < this->testResults.size(); i++) {
            free(testResults[i]);
        }
    }

    void runTest(int algorithm) {
        PerformanceTest* pt = new PerformanceTest();
        if(algorithm == 1) {
            pt->setAlgorithmName("MergeSort");
            for(int i = 0; i < this->testsetSize; i++) {
                int testArray[this->arrayLength];
                std::memcpy(testArray, this->baseArray + (this->arrayLength * i), this->arrayLength * sizeof(int));
                auto startTime = std::chrono::high_resolution_clock::now();
                mergeSort(testArray, this->arrayLength, true);
                auto endTime = std::chrono::high_resolution_clock::now();
                pt->processResult(startTime, endTime);
            }

        } else if(algorithm == 2) {
            pt->setAlgorithmName("MergesortRand ");
            for(int i = 0; i < this->testsetSize; i++) {
                int testArray[this->arrayLength];
                std::memcpy(testArray, this->baseArray + (this->arrayLength * i), this->arrayLength * sizeof(int));
                auto startTime = std::chrono::high_resolution_clock::now();
                mergesortRand(testArray, this->arrayLength, true);
                auto endTime = std::chrono::high_resolution_clock::now();
                pt->processResult(startTime, endTime);
            }

            // } else if(algorithm == 3) {
            //     pt->setAlgorithmName("IS Optimized");
            //     for(int i = 0; i < this->testsetSize; i++) {
            //         int testArray[this->arrayLength];
            //         std::memcpy(testArray, this->baseArray + (this->arrayLength * i), this->arrayLength * sizeof(int));
            //         auto startTime = std::chrono::high_resolution_clock::now();
            //         insertionSortOptimized(testArray, this->arrayLength, true);
            //         auto endTime = std::chrono::high_resolution_clock::now();
            //         pt->processResult(startTime, endTime);
            //     }

            // } else if(algorithm == 4) {
            //     pt->setAlgorithmName("IS Recursive");
            //     for(int i = 0; i < this->testsetSize; i++) {
            //         int testArray[this->arrayLength];
            //         std::memcpy(testArray, this->baseArray + (this->arrayLength * i), this->arrayLength * sizeof(int));
            //         auto startTime = std::chrono::high_resolution_clock::now();
            //         insertionSortRecursive(testArray, this->arrayLength, true);
            //         auto endTime = std::chrono::high_resolution_clock::now();
            //         pt->processResult(startTime, endTime);
            //     }
            // } else if(algorithm == 5) {
            //     pt->setAlgorithmName("MergeSort");
            //     for(int i = 0; i < this->testsetSize; i++) {
            //         int testArray[this->arrayLength];
            //         std::memcpy(testArray, this->baseArray + (this->arrayLength * i), this->arrayLength * sizeof(int));
            //         auto startTime = std::chrono::high_resolution_clock::now();
            //         mergeSort(testArray, 0, this->arrayLength - 1);
            //         auto endTime = std::chrono::high_resolution_clock::now();
            //         pt->processResult(startTime, endTime);
            //     }

        } else {
            std::cerr << "Algorithm not recognized!" << std::endl;
            exit(1);
        }

        this->testResults.push_back(pt);
    };

    void printComparison(int mode) {
        if(mode == 1) {
            std::cout << "Algorithm\tMIN\tMAX\tAVG\tTOTAL" << std::endl;
            for(unsigned int i=0; i<this->testResults.size(); i++) {
                std::cout << this->testResults[i]->getAlgorithmName() << "\t" << this->testResults[i]->getMinExecutionTime() << "\t" << this->testResults[i]->getMaxExecutionTime() << "\t" << this->testResults[i]->getTotalExecutionTime() / this->testsetSize << "\t" << this->testResults[i]->getTotalExecutionTime() << std::endl;
            }
        } else if(mode == 2) {
            std::cout << "Algorithm\tTOTAL\t\tAVG" << std::endl;
            for(unsigned int i=0; i<this->testResults.size(); i++) {
                std::cout << this->testResults[i]->getAlgorithmName() << "\t" << this->testResults[i]->getTotalExecutionTime() << " \t" << this->testResults[i]->getTotalExecutionTime() / this->testsetSize << std::endl;
            }
        } else {
            std::cerr << "Mode not recognized!" << std::endl;
            exit(1);
        }
    }
};


#define ARRAYLENGTH 13

int main() {
    srand(time(NULL));

    //int array[] = {5, 9, 1, 2, 8, 6, 7, 3, 5, 3, 13, 17, 29};
    //int array2[] = {5, 9, 1, 2, 8, 6, 7, 3, 5, 3, 13, 17, 29};
    int array[ARRAYLENGTH];
    int array2[ARRAYLENGTH];

    generateRandomIntArray(array, ARRAYLENGTH);
    memcpy(array2, array, ARRAYLENGTH * sizeof(int));

    mergeSort(array, 0, ARRAYLENGTH-1);
    printArray(array, ARRAYLENGTH, "Mergesort");

    mergesortRand(array2, 0, ARRAYLENGTH-1);
    printArray(array2, ARRAYLENGTH, "Mergesort Rand");

    PerformanceComparison pc(20000, 10000);
    pc.runTest(1);
    pc.runTest(2);
    pc.printComparison(1);
}
