#pragma once
#include "../Sort/Sort.h"
template <typename T>
int Inversion(T* array, int length, bool (*comparer)(T, T)) {
	int count = 0;
	for (int i = 0; i < length - 1; i++)
		for (int j = i + 1; j < length; j++)
			if (!comparer(array[i], array[j])) count++;
	return count;
}

template <typename T>
int InversionMerge(T* array, int begin, int end, int medium, bool (*comparer)(T, T)) {
	int length1 = medium - begin + 1;
	int length2 = end - medium;
	int length3 = length1 + length2;
	int* array1 = new int[length1];
	int* array2 = new int[length2];
	int count = begin;
	for (int i = 0; i < length1; i++) array1[i] = array[count++];
	for (int i = 0; i < length2; i++) array2[i] = array[count++];
	MergeSort(array1, 0, length1 - 1, comparer);
	MergeSort(array2, 0, length2 - 1, comparer);
	int more = 0, result = 0;
	int i1 = length1 - 1, i2 = length2 - 1;
	while (i1 >= 0 && i2 >= 0) {
		if (!comparer(array1[i1], array2[i2])) {
			more++; i1--;
		}
		else {
			result += more; i2--;
		}
	}
	while (i2 >= 0) {
		result += more; i2--;
	}
	return result;
}

template <typename T>
int Inversion(T* array, int begin, int end, bool (*comparer)(T, T)) {
	if (begin < end) {
		int medium = (begin + end) / 2;
		int count1 = Inversion(array, begin, medium, comparer);
		int count2 = Inversion(array, medium + 1, end, comparer);
		int count3 = InversionMerge(array, begin, end, medium, comparer);
		return count1 + count2 + count3;
	}
	return 0;
}
