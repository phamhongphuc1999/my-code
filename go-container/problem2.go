package main

var problem2Dirs [4][2]int = [4][2]int{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}

// problem 79
func _exist(board [][]byte, word string, locationRow int, locationColumn int, index int, check [][]int) bool {
	if index == len(word) - 1 {
		return true
	}
	for _, dir := range problem2Dirs {
		row := locationRow + dir[0]
		column := locationColumn + dir[1]
		if row >= 0 && row < len(board) && column >= 0 && column < len(board[0]) && check[row][column] == 0 && word[index + 1] == board[row][column] {
			check[row][column] = 1
			__check := _exist(board, word, row, column, index + 1, check)
			if (__check) {
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
				if (__check) {
					return true
				} else {
					check[i][j] = 0
				}
			}
		}
	}
	return false
}

// problem 52
func totalNQueens(n int) int {
    
}
