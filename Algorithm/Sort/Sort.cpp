#include "Sort.h"
#ifndef _SORT_
#define _SORT_

template <typename T>
void SWAP(T* element1, T* element2) {
	T temp = *element1;
	*element1 = *element2;
	*element2 = temp;
}

template <typename T>
void BubbleSort(T* array, int length, bool (*comparer)(T, T)) {
	for (int i = 0; i < length - 1; i++)
		for (int j = i + 1; j < length; j++)
			if (!comparer(array[i], array[j]))
				SWAP<T>(&array[i], &array[j]);
}

template <typename T>
int PartitionHeader(T* array, int low, int hight, bool (*comparer)(T, T)) {
	int left = low + 1, right = hight, partition = array[low];
	while (true)
	{
		while (left <= hight && comparer(array[left], partition)) left++;
		while (right >= low && comparer(partition, array[right])) right--;
		if (left < right) {
			SWAP<T>(&array[left], &array[right]);
			left++; right--;
		}
		else break;
	}
	SWAP<T>(&array[right], &array[low]);
	return right;
}

template <typename T>
int PartitionEnd(T* array, int low, int hight, bool (*comparer)(T, T)) {
	int left = low, right = hight - 1, partition = array[hight];
	while (true)
	{
		while (left <= hight && comparer(array[left], partition)) left++;
		while (right >= low && comparer(partition, array[right])) right--;
		if (left < right) {
			SWAP<T>(&array[left], &array[right]);
			left++; right--;
		}
		else break;
	}
	SWAP<T>(&array[left], &array[hight]);
	return left;
}

template <typename T>
void QuickSort(T* array, int begin, int end, bool (*comparer)(T, T), TYPE_QUICK_SORT type) {
	if (end > begin) {
		int splip;
		if (type == HEAD) splip = PartitionHeader(array, begin, end, comparer);
		else splip = PartitionEnd(array, begin, end, comparer);
		QuickSort(array, begin, splip - 1, comparer, type);
		QuickSort(array, splip + 1, end, comparer, type);
	}
}

template <typename T>
void Merge(T* array, int begin, int end, int splip, bool (*comparer)(T, T)) {
	int len1 = splip - begin + 1;
	int len2 = end - splip;
	int* low = new int[len1];
	int* hight = new int[len2];
	for (int i = 0; i < len1; i++) low[i] = array[begin + i];
	for (int i = 0; i < len2; i++) hight[i] = array[splip + 1 + i];
	int count1 = 0, count2 = 0, count = begin;
	while (count < len1 && count < len2) {
		if (comparer(low[count1], hight[count2])) array[count++] = low[count1++];
		else array[count++] = hight[count2++];
	}
	while (count1 < len1) array[count++] = low[count1++];
	while (count2 < len2) array[count++] = hight[count2++];
}

template <typename T>
void MergeSort(T* array, int begin, int end, bool (*comparer)(T, T)) {
	if (begin < end) {
		int splip = (begin + end) / 2;
		MergeSort(array, begin, splip, comparer);
		MergeSort(array, splip + 1, end, comparer);
		Merge(array, begin, end, splip, comparer);
	}
}

template <typename T>
void heapify(T* array, int offset, int heap_size, bool (*comparer)(T, T)) {

}

template <typename T>
void CreateHeap(T* array, int length, bool (*comparer)(T, T)) {

}

template <typename T>
void HeapSort(T* aray, int length, bool (*comparer)(T, T)) {

}
#endif
