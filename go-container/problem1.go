package main

import (
	"fmt"
)

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


func main() {
    squares := [][]int{
        {0, 0, 1},
        {2, 2, 1},
    }
    result := separateSquares(squares)
    fmt.Printf("%f\n", result)
}
