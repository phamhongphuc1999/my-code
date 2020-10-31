#include "FindMax.h"

int FindMostOne(int** matric, int N) {
	int row = 0, column = 0, result = 0;
	while (column < N && row < N) {
		if (matric[row][column] == 1) {
			result = row;
			column++;
		}
		else row++;
	}
	return result;
}