#pragma once
#include "../Sort/QuickSort.h"

template <typename T>
int BinarySearch(T* array, int value, int begin, int end, bool(*comparer)(T, T)) {
	if (begin == end) {
		if (comparer(value, array[begin])) return begin;
		else return begin + 1;
	}
	else {
		int medium = (end + begin) / 2;
		if (comparer(value, array[medium])) return BinarySearch(array, value, begin, medium, comparer);
		else return BinarySearch(array, value, medium + 1, end, comparer);
	}
}

template <typename T>
int RandomizedSelect(T* array, int begin, int end, int index, bool (*comparer)(T, T)) {
	if (end - begin + 1 >= index) {
		int partition = PartitionRandom(array, begin, end, comparer);
		if (partition < index) return RandomizedSelect(array, partition + 1, end, index - partition, comparer);
		else if (partition > index) return RandomizedSelect(array, begin, partition, index, comparer);
		else return array[partition];
	}
	return -1;
}
