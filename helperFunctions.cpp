#include "helperFunctions.h"
#include <ctime>

void printArray(int* array, int arrayLength, std::string heading) {
    std::cout << "========== " << heading << " ==========" << std::endl;
    for(int i = 0; i < arrayLength; i++) {
        if(i > 0) {
            std::cout << " - ";
        }
        std::cout << array[i];
    }
    std::cout << std::endl << "==============================================" << std::endl;
}

void generateRandomIntArray(int* array, int arrayLength) {
    std::srand(std::time(NULL));
    for(int i = 0; i < arrayLength; i++) {
        array[i] = rand() % 100000 + 1;
    }
}