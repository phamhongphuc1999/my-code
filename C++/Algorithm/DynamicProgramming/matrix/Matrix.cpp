int RecursiveMatrix(int* p, int i, int j) {
	if (i == j) return 0;
	else {
		int min = RecursiveMatrix(p, i + 1, j) + p[i - 1] * p[i] * p[j];
		for (int k = i + 1; k < j; k++) {
			int mik = RecursiveMatrix(p, i, k);
			int mkj = RecursiveMatrix(p, k + 1, j);
			int result = mik + mkj + p[i - 1] * p[k] * p[j];
			if (min > result) min = result;
		}
		return min;
	}
}

int DynamicMatrix(int* p, int i, int j) {
	int** m = new int* [j];
	for (int k = 0; k < j; k++) m[k] = new int[j];
	for (int k = 0; k < j; k++) m[k][k] = 0;
	for (int sum = 1; sum < j; sum++)
		for (int k = 0; k + sum < j; k++) {
			m[k][k + sum] = m[k + 1][k + sum] + p[k] * p[k + 1] * p[k + sum + 1];
			for (int k1 = k + 1; k1 < k + sum; k1++)
			{
				int result = m[k][k1] + m[k1 + 1][k + sum] + p[k] * p[k1 + 1] * p[k + sum + 1];
				if (result < m[k][k + sum]) m[k][k + sum] = result;
			}
		}
	return m[i - 1][j - 1];
}

int** memo;

int RecursiveMemoMatrix(int* p, int i, int j) {
	if (i == j)
	{
		memo[i, i] = 0;
		return 0;
	}
	else {
		if (memo[i + 1][j] < 0) memo[i + 1][j] = RecursiveMemoMatrix(p, i + 1, j);
		int min = memo[i + 1][j] + p[i] * p[i + 1] * p[j + 1];
		for (int k = i + 1; k < j; k++)
		{
			if (memo[i][k] < 0) memo[i][k] = RecursiveMemoMatrix(p, i, k);
			if (memo[k + 1][j] < 0) memo[k + 1][j] = RecursiveMemoMatrix(p, k + 1, j);
			int mik = memo[i][k];
			int mkj = memo[k + 1][j];
			int result = mik + mkj + p[i] * p[k + 1] * p[j + 1];
			if (min > result) min = result;
		}
		return min;
	}
}

int MemoizedMatrix(int* p, int i, int j) {
	memo = new int* [j];
	for (int k = 0; k < j; k++) {
		memo[k] = new int[j];
		for (int t = 0; t < j; t++) memo[k][t] = -1;
	}
	return RecursiveMemoMatrix(p, i - 1, j - 1);
}