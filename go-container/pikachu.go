package main

var dirs [4][2]int = [4][2]int{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}

func buildPath(parents [][][][3]int, piece [2]int, dir int, sourcePiece [2]int) [][2]int {
	result := [][2]int{}
	selectedItem := [3]int {piece[0], piece[1], dir}
	for selectedItem[0] != sourcePiece[0] || selectedItem[1] != sourcePiece[1] {
		result = append(result, [2]int {selectedItem[0], selectedItem[1]})
		selectedItem = parents[selectedItem[0]][selectedItem[1]][selectedItem[2]]
		if selectedItem[0] < 0 || selectedItem[1] < 0 {
			break
		}
	}
	result = append(result, sourcePiece)
	reverse(result)
	return result
}

func findPikachuPath(board [][]int, piece1 [2]int, piece2 [2]int, numberOfLines int) [][2]int {
	rows := len(board)
	columns := len(board[0])
	qu := &Queue[[4]int]{}
	visited := make([][][]bool, rows)
	for i := 0; i < rows; i++ {
			visited[i] = make([][]bool, columns)
			for j := 0; j < columns; j++ {
					visited[i][j] = make([]bool, 4)
			}
	}
	parents := make([][][][3]int, rows)
	for i:= 0; i < rows; i++ {
		parents[i] = make([][][3]int, columns)
		for j := 0; j < columns; j++ {
			parents[i][j] = make([][3]int, 4)
			for d := 0; d < 4; d++ {
            parents[i][j][d] = [3]int{-1, -1, -1}
        }
		}
	}
	for index := range dirs {
		qu.Push([4]int{piece1[0], piece1[1], index, 0})
		visited[piece1[0]][piece1[1]][index] = true
	}
	for !qu.Empty() {
		selectedItem := qu.Pop()
		println(selectedItem[0], ", ", selectedItem[1], ", ", selectedItem[2], ", ", selectedItem[3])
		if selectedItem[3] <= numberOfLines {
			for index, dir := range dirs {
				x := selectedItem[0] + dir[0]
				y := selectedItem[1] + dir[1]
				if x >= 0 && x < rows && y >= 0 && y < columns && !visited[x][y][index] {
					if x == piece2[0] && y == piece2[1] {
						return buildPath(parents, [2]int {x, y}, index, piece1)
					}
					if board[x][y] == 0 {
						turnBias := 0
						if index != selectedItem[2] {
							turnBias = 1
						}
						visited[x][y][index] = true
						qu.Push([4]int{x, y, index, selectedItem[3] + turnBias})
						parents[x][y][index] = [3]int {selectedItem[0], selectedItem[1], selectedItem[2]}
					}
				}
			}
		}
	}
	return [][2]int{}
}

func testPikachu() {
	board := [][]int {
		{0, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 0},
		{0, 1, 1, 0, 0, 0},
		{0, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0},
	}
	result := findPikachuPath(board, [2]int {1, 1}, [2]int {3, 1}, 2)
	for _, item := range result {
		println(item[0], ", ", item[1])
	}
}
