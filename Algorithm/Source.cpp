#include <iostream>
#include "Sort/Sort.h"
#include "Inversion/inversion.h"
using namespace std;

bool ABC(int a, int b) {
	return a < b;
}

int main() {
	int* a = new int[10]{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int* b = new int[5]{ 3, 2, 8, 6, 1 };
	cout << Inversion(b, 5, ABC);
	/*MergeSort(b, 0, 4, ABC);
	for (int i = 0; i < 5; i++)
		cout << b[i] << " ";
	cout << "\n" << BinarySearch(a, 8, 0, 10, ABC);*/
}
