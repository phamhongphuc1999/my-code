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

/// <summary>
/// Find the specified nth element in array
/// </summary>
/// <returns></returns>
template <typename T>
T QuickSelect(T* array, int begin, int end, int index, QUICK_SORT_TYPE type, bool(*comparer)(T, T)) {
	if (index < end - begin + 1) {
		int partition = 0;
		if (type == HEAD) partition = Partition(array, begin, end, begin, comparer);
		else if (type == TAIL) partition = Partition(array, begin, end, end, comparer);
		else partition = Partition(array, begin, end, (begin + end) / 2, comparer);
		if (partition < index + begin) return QuickSelect(array, partition + 1, end, index + begin - partition - 1, type, comparer);
		else if (partition > index + begin) return QuickSelect(array, begin, partition, index, type, comparer);
		else return array[partition];
	}
	throw "IndexOutOfRange";
}


