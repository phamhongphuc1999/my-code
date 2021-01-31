#include <iostream>
#include "Sort/Sort.h"
using namespace std;

bool ABC(int a, int b) {
	return a < b;
}

int main() {
	int* a = new int[10]{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	InsertSort(a, 10, ABC);
	for (int i = 0; i < 10; i++)
		cout << a[i] << " ";
}
