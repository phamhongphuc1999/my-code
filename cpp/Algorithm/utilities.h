#pragma once
template <typename T>
void SWAP(T* element1, T* element2) {
	T temp = *element1;
	*element1 = *element2;
	*element2 = temp;
}
