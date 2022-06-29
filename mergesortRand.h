#ifndef AUD_6_1_MERGESORTRAND_H
#define AUD_6_1_MERGESORTRAND_H

#include <iostream>
#include <time.h>

#pragma once

void merge(int array[], int left, int middle, int right);
void mergeSort(int array[], int left, int right);

void mergeRand(int* array, int left, int middle, int right);
void mergesortRand(int* array, int left, int right);

#endif //AUD_6_1_MERGESORTRAND_H
