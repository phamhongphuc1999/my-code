// https://www.hackerrank.com/challenges/gena/problem?isFullScreen=true
package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

/*
 * Complete the 'hanoi' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY posts as parameter.
 */

func hanoi(posts []int32) int32 {
	n := len(posts)

	pow4 := 1
	for i := 0; i < n; i++ {
		pow4 *= 4
	}

	encode := func(rods []int8) int {
		code := 0
		for i := n - 1; i >= 0; i-- {
			code = code*4 + int(rods[i])
		}
		return code
	}

	decode := func(code int) []int8 {
		rods := make([]int8, n)
		for i := 0; i < n; i++ {
			rods[i] = int8(code % 4)
			code /= 4
		}
		return rods
	}

	startRods := make([]int8, n)
	for i := 0; i < n; i++ {
		startRods[i] = int8(posts[i] - 1) 
	}
	startCode := encode(startRods)
	goalCode := 0 

	if startCode == goalCode {
		return 0
	}

	dist := make([]int32, pow4)
	for i := range dist {
		dist[i] = -1
	}
	dist[startCode] = 0

	queue := make([]int, 0, pow4)
	queue = append(queue, startCode)

	for head := 0; head < len(queue); head++ {
		code := queue[head]
		d := dist[code]
		rods := decode(code)

		top := [4]int{-1, -1, -1, -1}
		for i := 0; i < n; i++ {
			r := rods[i]
			if top[r] == -1 {
				top[r] = i
			}
		}

		for r := 0; r < 4; r++ {
			di := top[r] 
			if di == -1 {
				continue
			}
			for r2 := 0; r2 < 4; r2++ {
				if r2 == r {
					continue
				}
				if top[r2] == -1 || top[r2] > di {
					newRods := make([]int8, n)
					copy(newRods, rods)
					newRods[di] = int8(r2)
					newCode := encode(newRods)

					if dist[newCode] == -1 {
						dist[newCode] = d + 1
						if newCode == goalCode {
							return dist[newCode]
						}
						queue = append(queue, newCode)
					}
				}
			}
		}
	}

	return -1 
}

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 16*1024*1024)

	stdout, err := os.Create(os.Getenv("OUTPUT_PATH"))
	checkError(err)

	defer stdout.Close()

	writer := bufio.NewWriterSize(stdout, 16*1024*1024)

	nTemp, err := strconv.ParseInt(strings.TrimSpace(readLine(reader)), 10, 64)
	checkError(err)
	n := int32(nTemp)

	locTemp := strings.Split(strings.TrimSpace(readLine(reader)), " ")

	var loc []int32

	for i := 0; i < int(n); i++ {
		locItemTemp, err := strconv.ParseInt(locTemp[i], 10, 64)
		checkError(err)
		locItem := int32(locItemTemp)
		loc = append(loc, locItem)
	}

	res := hanoi(loc)

	fmt.Fprintf(writer, "%d\n", res)

	writer.Flush()
}

func readLine(reader *bufio.Reader) string {
	str, _, err := reader.ReadLine()
	if err == io.EOF {
		return ""
	}

	return strings.TrimRight(string(str), "\r\n")
}

func checkError(err error) {
	if err != nil {
		panic(err)
	}
}