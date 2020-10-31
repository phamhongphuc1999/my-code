#include <iostream>
#include "FindMax/FindMax.h"
using namespace std;

bool AAA(int a, int b) {
	return a < b;
}

int main() {
	int N;
	cin >> N;
	int** matric = new int* [N];
	for (int i = 0; i < N; i++) {
		matric[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> matric[i][j];
	}
	cout << FindMostOne(matric, N);
}
