package main

var DIRECTIONS = [4][2]int{
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1},
}

func reverse[T any](a []T) {
	for i, j := 0, len(a)-1; i < j; i, j = i+1, j-1 {
		a[i], a[j] = a[j], a[i]
	}
}
