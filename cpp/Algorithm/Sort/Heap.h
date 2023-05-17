#pragma once
#include "../utilities.h"

int PARENT(int i) {
	return i / 2;
}

int RIGHT(int i) {
	return 2 * i + 2;
}

int LEFT(int i) {
	return 2 * i + 1;
}

template <typename T>
void Heapify(T* heap, int index, int length, bool (*comparer)(T, T)) {
	int left = LEFT(index);
	int right = RIGHT(index);
	int largest = index;
	if (left < length && !comparer(heap[index], heap[left])) largest = left;
	if (right < length && !comparer(heap[largest], heap[right])) largest = right;
	if (largest != index) {
		SWAP(&heap[index], &heap[largest]);
		Heapify(heap, largest, length, comparer);
	}
}

template <typename T>
void BuildHeap(T* array, int length, bool (*comparer)(T, T)) {
	int value = length / 2;
	for (int i = value; i >= 0; i--)
		Heapify(array, i, length, comparer);
}

template <typename T>
void HeapSort(T* array, int length, bool (*comparer)(T, T)) {
	BuildHeap(array, length, comparer);
	for (int i = length - 1; i >= 1; i--) {
		SWAP(&array[0], &array[i]);
		Heapify(array, 0, i, comparer);
	}
}
