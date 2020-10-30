#pragma once
#ifndef SORT
#define SORT

enum TYPE_QUICK_SORT {
	HEAD,
	END
};

template <typename T>
void SWAP(T* element1, T* element2);

template <typename T>
void BubbleSort(T* array, int length, bool (*comparer)(T, T));

template <typename T>
int PartitionHeader(T* array, int low, int hight, bool (*comparer)(T, T));

template <typename T>
int PartitionEnd(T* array, int low, int hight, bool (*comparer)(T, T));

template <typename T>
void QuickSort(T* array, int begin, int end, bool (*comparer)(T, T), TYPE_QUICK_SORT type);

template <typename T>
void Merge(T* array, int begin, int end, int splip, bool (*comparer)(T, T));

template <typename T>
void MergeSort(T* array, int begin, int end, bool (*comparer)(T, T));

#include "Sort.cpp"
#endif
