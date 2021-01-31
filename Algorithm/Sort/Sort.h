#pragma once
#include "../utilities.h"

template <typename T>
void BubbleSort(T* array, int length, bool (*comparer)(T, T)) {
	for (int i = 0; i < length - 1; i++)
		for (int j = i + 1; j < length; j++)
			if (!comparer(array[i], array[j])) SWAP(&array[i], &array[j]);
}

template <typename T>
void InsertSort(T* array, int length, bool (*comparer)(T, T)) {
	for (int i = 1; i < length; i++) {
		int value = array[i];
		int j = i - 1;
		while (j >= 0 && comparer(value, array[j])) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = value;
	}
}

template <typename T>
void SelectSort(T* array, int length, bool (*comparer)(T, T)) {
	for (int i = 0; i < length - 1; i++) {
		int index = i;
		for (int j = i + 1; j < length; j++)
			if (comparer(array[j], array[index])) index = j;
		if (index != i) SWAP(&array[i], &array[index]);
	}
}

template <typename T>
void MERGE(T* array, int begin, int end, int medium, bool (*comparer)(T, T)) {
	int length1 = medium - begin + 1;
	int length2 = end - medium;
	int* array1 = new int[length1];
	int* array2 = new int[length2];
	int i1 = 0, i2 = 0, count = begin;
	for (int i = 0; i < length1; i++) array1[i] = array[count++];
	for (int i = 0; i < length2; i++) array2[i] = array[count++];
	count = begin;
	while (i1 < length1 && i2 < length2) {
		if (comparer(array1[i1], array2[i2])) array[count++] = array1[i1++];
		else array[count++] = array2[i2++];
	}
	while (i1 < length1) array[count++] = array1[i1++];
	while (i2 < length2) array[count++] = array2[i2++];
}

template <typename T>
void MergeSort(T* array, int begin, int end, bool (*comparer)(T, T)) {
	if (begin < end) {
		int medium = (end + begin) / 2;
		MergeSort(array, begin, medium, comparer);
		MergeSort(array, medium + 1, end, comparer);
		MERGE(array, begin, end, medium, comparer);
	}
}
