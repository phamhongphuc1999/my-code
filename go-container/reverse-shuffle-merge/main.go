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

	// Count the total occurrences of each character in s
	var total [26]int
	for i := 0; i < n; i++ {
		total[s[i]-'a']++
	}

	// need[c]: number of times character c must appear in the answer A (= total/2)
	var need [26]int
	for c := 0; c < 26; c++ {
		need[c] = total[c] / 2
	}

	// remain[c]: occurrences of c left in the part NOT scanned yet (starts = total, decreases as we scan)
	remain := total

	// used[c]: number of times c has been pushed onto the stack (current candidate for A)
	var used [26]int

	// Stack holding the answer's characters (reading bottom to top is A itself, no need to reverse)
	stack := make([]byte, 0, n)

	// Scan from RIGHT to LEFT
	for i := n - 1; i >= 0; i-- {
		c := s[i]
		ci := c - 'a'

		remain[ci]-- // just "consumed" one occurrence of c at this position

		// If we already have enough c's for A, skip this character
		if used[ci] == need[ci] {
			continue
		}

		// While the stack top is greater than c, and there are still enough
		// of that character left unscanned to make up for it later, pop it
		// (this makes the result lexicographically smaller)
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

		// Push c onto the stack
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