// https://www.hackerrank.com/challenges/reverse-shuffle-merge/problem?isFullScreen=true
package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strings"
)

/*
 * Complete the 'reverseShuffleMerge' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

func reverseShuffleMerge(s string) string {
	n := len(s)

	var total [26]int
	for i := 0; i < n; i++ {
		total[s[i]-'a']++
	}

	var need [26]int
	for c := 0; c < 26; c++ {
		need[c] = total[c] / 2
	}

	remain := total
	var used [26]int
	stack := make([]byte, 0, n)

	for i := n - 1; i >= 0; i-- {
		c := s[i]
		ci := c - 'a'

		remain[ci]--
		if used[ci] == need[ci] {
			continue
		}
		for len(stack) > 0 {
			top := stack[len(stack)-1]
			ti := top - 'a'

			if top > c && remain[ti]+used[ti] > need[ti] {
				stack = stack[:len(stack)-1]
				used[ti]--
			} else {
				break
			}
		}
		stack = append(stack, c)
		used[ci]++
	}

	return string(stack)
}

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 16*1024*1024)

	stdout, err := os.Create(os.Getenv("OUTPUT_PATH"))
	checkError(err)

	defer stdout.Close()

	writer := bufio.NewWriterSize(stdout, 16*1024*1024)

	s := readLine(reader)

	result := reverseShuffleMerge(s)

	fmt.Fprintf(writer, "%s\n", result)

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