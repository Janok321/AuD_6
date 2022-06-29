#include "mergesortRand.h"
#define ARRAYLENGTH 13

void merge(int array[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int leftArray[n1];
    int rightArray[n1];

    for(int i= 0; i < n1; i++) {
        leftArray[i] = array[left + i];
    }
    for(int j = 0; j < n2; j++) {
        rightArray[j] = array[middle + j + 1];
    }

    int k = 0, l = 0, m = left;
    while(k < n1 && l < n2){
        if(leftArray[k] <= rightArray[l]) {
            array[m] = leftArray[k];
            k++;
        } else {
            array[m] = rightArray[l];
            l++;
        }
        m++;
    }

    while(k<n1){
        array[m] = leftArray[k];
        k++;
        m++;
    }

    while(l<n2){
        array[m] = rightArray[l];
        l++;
        m++;
    }
}

void mergeSort(int array[], int left, int right) {
    if(left < right) {
        int middle = left+(right-left)/2;
        mergeSort(array, left, middle);
        mergeSort(array, middle+1, right);
        merge(array, left, middle, right);
    }
}

//-----------------------------------------------------------------
// Mergesort mit Teilung an Zufallszahl"
//-----------------------------------------------------------------

void mergeRand(int* array, int left, int middle, int right) {
/*
    // Zufallszahl muss im Intervall right - left liegen
    int randomNumber = rand() % (right - left);

    // Setze Zufallszahl als middle
    middle = randomNumber;
*/
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int leftArray[n1];
    int rightArray[n1];

    for(int i= 0; i < n1; i++) {
        leftArray[i] = array[left + i];
    }
    for(int j = 0; j < n2; j++) {
        rightArray[j] = array[middle + j + 1];
    }

    int k = 0, l = 0, m = left;
    while(k < n1 && l < n2){
        if(leftArray[k] <= rightArray[l]) {
            array[m] = leftArray[k];
            k++;
        } else {
            array[m] = rightArray[l];
            l++;
        }
        m++;
    }

    while(k<n1){
        array[m] = leftArray[k];
        k++;
        m++;
    }

    while(l<n2){
        array[m] = rightArray[l];
        l++;
        m++;
    }
}

void mergesortRand(int* array, int left, int right) {
    if(left < right) {
        int middle = rand() % (left+(right-left));
        mergesortRand(array, left, middle);
        mergesortRand(array, middle+1, right);
        mergeRand(array, left, middle, right);
    }
}