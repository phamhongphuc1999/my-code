#pragma once
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

}
