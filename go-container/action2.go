package main

import (
	"sort"
)

var problem2Dirs [4][2]int = [4][2]int{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}

// problem 79
func _exist(board [][]byte, word string, locationRow int, locationColumn int, index int, check [][]int) bool {
	if index == len(word)-1 {
		return true
	}
	for _, dir := range problem2Dirs {
		row := locationRow + dir[0]
		column := locationColumn + dir[1]
		if row >= 0 && row < len(board) && column >= 0 && column < len(board[0]) && check[row][column] == 0 && word[index+1] == board[row][column] {
			check[row][column] = 1
			__check := _exist(board, word, row, column, index+1, check)
			if __check {
				return true
			} else {
				check[row][column] = 0
			}
		}
	}
	return false
}

func exist(board [][]byte, word string) bool {
	check := make([][]int, len(board))
	for i := 0; i < len(board); i++ {
		check[i] = make([]int, len(board[0]))
	}
	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board[0]); j++ {
			if word[0] == board[i][j] {
				check[i][j] = 1
				__check := _exist(board, word, i, j, 0, check)
				if __check {
					return true
				} else {
					check[i][j] = 0
				}
			}
		}
	}
	return false
}

// problem 1877
func minPairSum(nums []int) int {
	sort.Ints(nums)
	result := 0
	_len := len(nums)
	for i := 0; i < _len/2; i++ {
		temp := nums[i] + nums[_len-1-i]
		if temp > result {
			result = temp
		}
	}
	return result
}

// problem 1984
func minimumDifference(nums []int, k int) int {
	sort.Ints(nums)
	result := nums[k-1] - nums[0]
	for i := 1; i <= len(nums)-k; i++ {
		temp := nums[i+k-1] - nums[i]
		if temp < result {
			result = temp
		}
	}
	return result
}

// problem 1200
func minimumAbsDifference(arr []int) [][]int {
	sort.Ints(arr)
	minDistance := arr[1] - arr[0]
	for i := 2; i < len(arr); i++ {
		temp := arr[i] - arr[i-1]
		if temp < minDistance {
			minDistance = temp
		}
	}
	result := [][]int{}
	for i := 1; i < len(arr); i++ {
		if arr[i]-arr[i-1] == minDistance {
			result = append(result, []int{arr[i-1], arr[i]})
		}
	}
	return result
}

// problem 96
// If choose i as root,
// => all smaller number must be in the left
// => all bigger number must be in the right
// => The number of tree can be constructed if choose i as root is
// leftTree * rightTree, such as leftTree is the number of BST of i - 1 nodes and rightTree is the number of BST of n - i nodes.
func numTrees(n int) int {
	arr := make([]int, n+1)
	arr[0] = 1
	arr[1] = 1
	for i := 2; i <= n; i++ {
		total := 0
		for j := 1; j <= i; j++ {
			total += arr[j-1] * arr[i-j]
		}
		arr[i] = total
	}
	return arr[n]
}
