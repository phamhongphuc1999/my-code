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
