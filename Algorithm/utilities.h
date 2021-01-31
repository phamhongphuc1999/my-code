#pragma once
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
void SWAP(T* element1, T* element2) {
	T temp = *element1;
	*element1 = *element2;
	*element2 = temp;
}
