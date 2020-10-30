#include <iostream>
#include "Sort.h";
using namespace std;

bool AAA(int a, int b) {
	return a < b;
}

int main() {
	int* i = new int[] {1, 10, 2, 9, 3, 8};
	QuickSort<int>(i, 0, 5, AAA, END);
	for (int j = 0; j < 6; j++)
		cout << i[j] << endl;
}
