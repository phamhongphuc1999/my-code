package main

import (
	"math"
	"sort"
)

// problem 79
func _exist(board [][]byte, word string, locationRow int, locationColumn int, index int, check [][]int) bool {
	if index == len(word)-1 {
		return true
	}
	for _, dir := range DIRECTIONS {
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

// problem 419
func countBattleships(board [][]byte) int {
	counter := 0
	rows := len(board)
	cols := len(board[0])
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if board[i][j] == 'X' {
				board[i][j] = '.'
				counter++
				dx := 0
				dy := 0
				for _, dir := range DIRECTIONS {
					nx := i + dir[0]
					ny := j + dir[1]

					if nx >= 0 && nx < rows && ny >= 0 && ny < cols {
						if board[nx][ny] == 'X' {
							dx = dir[0]
							dy = dir[1]
							break
						}
					}
				}
				if dx != 0 || dy != 0 {
					nx := i + dx
					ny := j + dy
					for nx >= 0 && nx < rows && ny >= 0 && ny < cols {
						if board[nx][ny] == 'X' {
							board[nx][ny] = '.'
							nx = nx + dx
							ny = ny + dy
						} else {
							break
						}
					}
				}
			}
		}
	}
	return counter
}

func countSubIslands_dfs(grid1 [][]int, grid2 [][]int, x int, y int) int {
	result := 1
	if grid1[x][y] == 0 {
		result = 0
	}
	q := Queue[[2]int]{}
	grid2[x][y] = 0
	q.Push([2]int{x, y})
	rows := len(grid2)
	cols := len(grid2[0])
	for !q.Empty() {
		position := q.Pop()
		for _, direction := range DIRECTIONS {
			nx := position[0] + direction[0]
			ny := position[1] + direction[1]
			if nx >= 0 && nx < rows && ny >= 0 && ny < cols {
				if grid2[nx][ny] == 1 {
					if grid1[nx][ny] == 0 {
						result = 0
					}
					grid2[nx][ny] = 0
					q.Push([2]int{nx, ny})
				}
			}
		}
	}
	return result
}

func countSubIslands(grid1 [][]int, grid2 [][]int) int {
	rows := len(grid2)
	cols := len(grid2[0])
	result := 0
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if grid2[i][j] == 1 {
				result += countSubIslands_dfs(grid1, grid2, i, j)
			}
		}
	}
	return result
}

func findMaxFish_dfs(grid [][]int, x int, y int) int {
	q := Queue[[2]int]{}
	q.Push([2]int{x, y})
	result := grid[x][y]
	grid[x][y] = 0
	rows := len(grid)
	cols := len(grid[0])
	for !q.Empty() {
		position := q.Pop()
		for _, direction := range DIRECTIONS {
			nx := position[0] + direction[0]
			ny := position[1] + direction[1]
			if nx >= 0 && nx < rows && ny >= 0 && ny < cols {
				if grid[nx][ny] > 0 {
					result += grid[nx][ny]
					grid[nx][ny] = 0
					q.Push([2]int{nx, ny})
				}
			}
		}
	}
	return result
}

func findMaxFish(grid [][]int) int {
	rows := len(grid)
	cols := len(grid[0])
	result := 0
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if grid[i][j] > 0 {
				temp := findMaxFish_dfs(grid, i, j)
				if result < temp {
					result = temp
				}
			}
		}
	}
	return result
}

func countIslands_dfs(grid [][]int, x int, y int) int {
	q := Queue[[2]int]{}
	q.Push([2]int{x, y})
	result := grid[x][y]
	grid[x][y] = 0
	rows := len(grid)
	cols := len(grid[0])
	for !q.Empty() {
		position := q.Pop()
		for _, direction := range DIRECTIONS {
			nx := position[0] + direction[0]
			ny := position[1] + direction[1]
			if nx >= 0 && nx < rows && ny >= 0 && ny < cols {
				if grid[nx][ny] > 0 {
					result += grid[nx][ny]
					grid[nx][ny] = 0
					q.Push([2]int{nx, ny})
				}
			}
		}
	}
	return result
}

// problem 1905
func countIslands(grid [][]int, k int) int {
	rows := len(grid)
	cols := len(grid[0])
	result := 0
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if grid[i][j] > 0 {
				temp := countIslands_dfs(grid, i, j)
				if temp%k == 0 {
					result++
				}
			}
		}
	}
	return result
}

// problem 3070
func countSubmatrices(grid [][]int, k int) int {
	rows := len(grid)
	cols := len(grid[0])
	counter := 0
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if j > 0 {
				grid[i][j] = grid[i][j] + grid[i][j-1]
			}
			if i > 0 {
				grid[i][j] = grid[i][j] + grid[i-1][j]
			}
			if i > 0 && j > 0 {
				grid[i][j] = grid[i][j] - grid[i-1][j-1]
			}
			if grid[i][j] <= k {
				counter++
			} else {
				if j == 0 {
					return counter
				} else {
					break
				}
			}
		}
	}
	return counter
}

func totalNQueens(n int) int {
	cols := make([]bool, n)
	diag1 := make([]bool, 2*n)
	diag2 := make([]bool, 2*n)

	var dfs func(int) int

	dfs = func(row int) int {
		if row == n {
			return 1
		}

		count := 0

		for col := 0; col < n; col++ {

			if cols[col] || diag1[row+col] || diag2[row-col+n] {
				continue
			}

			cols[col] = true
			diag1[row+col] = true
			diag2[row-col+n] = true

			count += dfs(row + 1)

			cols[col] = false
			diag1[row+col] = false
			diag2[row-col+n] = false
		}

		return count
	}
	return dfs(0)
}

func isBalanced_dfs(node *TreeNode) float64 {
	if node == nil {
		return 0
	}
	left := isBalanced_dfs(node.Left)
	if left == -1 {
		return -1
	}
	right := isBalanced_dfs(node.Right)
	if right == -1 {
		return -1
	}
	if math.Abs(left-right) > 1 {
		return -1
	}
	return 1 + math.Max(left, right)
}

// problem 110
func isBalanced(root *TreeNode) bool {
	return isBalanced_dfs(root) != -1
}

// problem 104
func maxDepth(root *TreeNode) int {
	if root == nil {
		return 0
	}
	left := maxDepth(root.Left)
	right := maxDepth(root.Right)
	return max(left, right) + 1
}

// // problem 1376
// func numOfMinutes(n int, headID int, manager []int, informTime []int) int {
// 	root := TreeNode{}
// }
