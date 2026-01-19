package main

// problem 3453
func separateSquares(squares [][]int) float64 {
    precision := 0.00001
    len := len(squares)
    var _start int = squares[0][1]
    var _end int = squares[0][1] + squares[0][2]
    for i := 1; i < len; i++ {
        if _start > squares[i][1] {
            _start = squares[i][1]
        }
        if _end < squares[i][1] + squares[i][2] {
            _end = squares[i][1] + squares[i][2]
        }
    }
    var start = float64(_start)
    var end = float64(_end)
    for end - start > precision {
        var line float64 = (start + end) / 2
        var above float64 = 0
        var below float64 = 0
        for i := 0; i < len; i++ {
            var yi float64 = float64(squares[i][1])
            var li float64 = float64(squares[i][2])
            var _square float64 = li*li
            if yi >= line {
                above += _square
            } else if yi + li <= line {
                below += _square
            } else {
                _below := line - yi
                _above := yi + li - line
                below += _square * _below / (_below + _above)
                above += _square * _above / (_below + _above)
            }
        }
        if below < above {
            start = line
        } else {
            end = line
        }
    }
    return start
}

// problem 55
func canJump(nums []int) bool {
    currentFarthest := 0
    for i := 0; i <= len(nums) - 2; i++ {
        if i > currentFarthest {
            return false
        }
        if i + nums[i] > currentFarthest {
            currentFarthest = i + nums[i]
        }
    }
    return currentFarthest >= len(nums) - 1
}

// problem 45
func jump(nums []int) int {
    len := len(nums)
    var arr = make([]int, len)
    for i := len - 2; i >= 0; i-- {
        if nums[i] == 0 {
            arr[i] = 10000
        } else {
            _min := 10000
            _max := len - 1
            if i + nums[i] < len - 1 {
                _max = i + nums[i]
            }
            for j := i + 1; j <= _max; j++ {
                if arr[j] < _min {
                    _min = arr[j]
                }
            }
            arr[i] = _min + 1
        }
    }
    return arr[0]
}

// When reaching the current end, must jump
func jump45_v2(nums []int) int {
    result := 0
    currentEnd := 0
    currentFarthest := 0
    for i := 0; i < len(nums) - 1; i++ {
        if i + nums[i] > currentFarthest {
            currentFarthest = i + nums[i]
        }
        if i == currentEnd {
            currentEnd = currentFarthest
            result++
        }
    }
    return result
}

// problem 62
func uniquePaths(m int, n int) int {
    saves := make([][]int, m)
    for i := 0; i < m; i++ {
        saves[i] = make([]int, n)
    }
    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            if i == 0 || j == 0 {
                saves[i][j] = 1
            } else {
                saves[i][j] = saves[i - 1][j] + saves[i][j - 1]
            }
        }
    }
    return saves[m - 1][n - 1]
}

// problem 63
func uniquePathsWithObstacles(obstacleGrid [][]int) int {
    m, n := len(obstacleGrid), len(obstacleGrid[0])
    saves := make([][]int, m)
    for i := 0; i < m; i++ {
        saves[i] = make([]int, n)
    }
    isObstacleExist := false
    for i := 0; i < n; i++ {
        if obstacleGrid[0][i] == 1 {
            isObstacleExist = true
        }
        if !isObstacleExist {
            saves[0][i] = 1
        }
    }
    isObstacleExist = false
    for i := 0; i < m; i++ {
        if obstacleGrid[i][0] == 1 {
            isObstacleExist = true
        }
        if !isObstacleExist {
            saves[i][0] = 1
        }
    }
    for i := 1; i < m; i++ {
        for j := 1; j < n; j++ {
            if obstacleGrid[i][j] == 0 {
                if obstacleGrid[i - 1][j] == 0 {
                saves[i][j] += saves[i - 1][j]
                }
                if obstacleGrid[i][j - 1] == 0 {
                    saves[i][j] += saves[i][j - 1]
                }
            }
        }
    }
    return saves[m - 1][n - 1]
}

// problem 64
func minPathSum(grid [][]int) int {
    m, n := len(grid), len(grid[0])
    saves := make([][]int, m)
    for i := 0; i < m; i++ {
        saves[i] = make([]int, n)
    }
    saves[0][0] = grid[0][0]
    for i := 1; i < n; i++ {
        saves[0][i] = saves[0][i - 1] + grid[0][i]
    }
    for i := 1; i < m; i++ {
        saves[i][0] = saves[i - 1][0] + grid[i][0]
    }
    for i := 1; i < m; i++ {
        for j := 1; j < n; j++ {
            if saves[i - 1][j] < saves[i][j - 1] {
                saves[i][j] = saves[i - 1][j] + grid[i][j]
            } else {
                saves[i][j] = saves[i][j - 1] + grid[i][j]
            }
        }
    }
    return saves[m - 1][n - 1]
}

func maxSubArray(nums []int) int {
    endMax := nums[0]
    result := endMax
    for i := 1; i < len(nums); i++ {
        if endMax + nums[i] < nums[i] {
            endMax = nums[i]
        } else {
            endMax = endMax + nums[i]
        }
        if result < endMax {
            result = endMax
        }
    }
    return result
}

func maxEndSubArray(nums []int, startIndex int, endIndex int) int {
    result := nums[startIndex]
    for i := startIndex + 1; i <= endIndex; i++ {
        if result + nums[i] < nums[i] {
            result = nums[i]
        } else {
            result += nums[i]
        }
    }
    return result
}

func maxBeginSubArray(nums []int, startIndex int, endIndex int) int {
    result := nums[endIndex]
    for i := endIndex - 1; i >= startIndex; i-- {
        if result + nums[i] < nums[i] {
            result = nums[i]
        } else {
            result += nums[i]
        }
    }
    return result
}

func _maxSubArray(nums []int, startIndex int, endIndex int) int {
    if startIndex == endIndex {
        return nums[startIndex]
    }
    middle := (startIndex + endIndex) / 2
    beginPartMax := maxBeginSubArray(nums, middle + 1, endIndex)
    endPartMax := maxEndSubArray(nums, startIndex, middle)
    beginMax := _maxSubArray(nums, startIndex, middle)
    endMax := _maxSubArray(nums, middle + 1, endIndex)
    result := beginPartMax + endPartMax
    if result < beginMax {
        result = beginMax
    }
    if result < endMax {
        result = endMax
    }
    return result
}

func maxSubArrayDivideAndConquer(nums []int) int {
    return _maxSubArray(nums, 0, len(nums) - 1)
}

// problem 91
func numDecodings(s string) int {
    if s[0] == '0' {
        return  0
    }
    result := make([]int, len(s))
    result[0] = 1
    for i:= 1; i < len(s); i++ {
        if (s[i] == '0') {
            if (s[i - 1] != '1' && s[i - 1] != '2') {
                return  0
            }
            if (i == 1) {
                result[i] = 1
            } else {
                result[i] = result[i - 2]
            }
        } else if (s[i] >= '1' && s[i] <= '6') {
            if (s[i - 1] != '1' && s[i - 1] != '2') {
                result[i] = result[i - 1]
            } else {
                if (i == 1) {
                    result[i] = 1 + result[i - 1]
                } else {
                    result[i] = result[i - 2] + result[i - 1]
                }
            }
        } else {
            if (s[i - 1] != '1') {
                result[i] = result[i - 1]
            } else {
                if (i == 1) {
                    result[i] = 1 + result[i - 1]
                } else {
                    result[i] = result[i - 2] + result[i - 1]
                }
            }
        }
    }
    return result[len(s) - 1]
}

// problem 72
func minDistance(word1 string, word2 string) int {
    len1, len2 := len(word1), len(word2)
    result := make([][]int, len1 + 1)
    for i := 0; i <= len1; i++ {
        result[i] = make([]int, len2 + 1)
        result[i][0] = i
    }
    for i := 0; i <= len2; i++ {
        result[0][i] = i
    }
    for i := 1; i <= len1; i++ {
        for j := 1; j <= len2; j++ {
            if word1[i - 1] == word2[j - 1] {
                result[i][j] = result[i - 1][j - 1]
            } else {
                result[i][j] = min(result[i - 1][j], result[i][j - 1], result[i - 1][j - 1]) + 1
            }
        }
    }
    return result[len1][len2]
}

// problem 1292
func maxSideLength(mat [][]int, threshold int) int {
    rows := len(mat)
    columns := len(mat[0])

    // Build 0-based prefix sum
    pre := make([][]int, rows)
    for i := 0; i < rows; i++ {
        pre[i] = make([]int, columns)
    }

    pre[0][0] = mat[0][0]
    for j := 1; j < columns; j++ {
        pre[0][j] = pre[0][j-1] + mat[0][j]
    }
    for i := 1; i < rows; i++ {
        pre[i][0] = pre[i-1][0] + mat[i][0]
    }
    for i := 1; i < rows; i++ {
        for j := 1; j < columns; j++ {
            pre[i][j] = pre[i-1][j] + pre[i][j-1] + mat[i][j] - pre[i-1][j-1]
        }
    }

    start, end, result := 1, min(rows, columns), 0

    for start <= end {
        medium := (start + end) / 2
        isOk := false

        for i := 0; i <= rows-medium && !isOk; i++ {
            for j := 0; j <= columns-medium; j++ {
                tlRow, tlColumn := i, j
                brRow, brColumn := i+medium-1, j+medium-1

                // Correct submatrix sum
                sum := pre[brRow][brColumn]
                if tlRow > 0 {
                    sum -= pre[tlRow-1][brColumn]
                }
                if tlColumn > 0 {
                    sum -= pre[brRow][tlColumn-1]
                }
                if tlRow > 0 && tlColumn > 0 {
                    sum += pre[tlRow-1][tlColumn-1]
                }

                if sum <= threshold {
                    isOk = true
                    break
                }
            }
        }

        if isOk {
            result = medium
            start = medium + 1
        } else {
            end = medium - 1
        }
    }

    return result
}
