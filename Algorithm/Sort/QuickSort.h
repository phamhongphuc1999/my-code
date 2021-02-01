#pragma once
#include "../utilities.h"

enum QUICK_SORT_TYPE {
	HEAD, TAIL, MEDIUM
};

template <typename T>
int Partition(T* array, int begin, int end, int pivot, bool (*comparer)(T, T)) {
	int low = begin, hight = end;
	int value = array[pivot];
	while (low < hight) {
		while (comparer(array[low], value)) low++;
		while (comparer(value, array[hight])) hight--;
		SWAP(&array[low], &array[hight]);
	}
	SWAP(&array[low], &array[hight]);
	return hight;
}

template <typename T>
int PartitionRandom(T* array, int begin, int end, bool (*comparer)(T, T)) {
	int pivot = rand() / (end - begin + 1) + begin;
	return Partition(array, begin, end, pivot, comparer);
}

template <typename T>
void QuickSort(T* array, int begin, int end, QUICK_SORT_TYPE type, bool (*comparer)(T, T)) {
	if (begin < end) {
		int partition = 0;
		if (type == HEAD) partition = Partition(array, begin, end, begin, comparer);
		else if (type == TAIL) partition = Partition(array, begin, end, end, comparer);
		else partition = Partition(array, begin, end, (begin + end) / 2, comparer);
		QuickSort(array, begin, partition, type, comparer);
		QuickSort(array, partition + 1, end, type, comparer);
	}
}

template <typename T>
void QuickSortRandom(T* array, int begin, int end, bool (*comparer)(T, T)) {
	if (begin < end) {
		int partition = PartitionRandom(array, begin, end, comparer);
		QuickSortRandom(array, begin, partition, comparer);
		QuickSortRandom(array, partition + 1, end, comparer);
	}
}
