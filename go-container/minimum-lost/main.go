// https://www.hackerrank.com/challenges/minimum-loss/problem?isFullScreen=true
package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"sort"
	"strconv"
	"strings"
)

/*
 * Complete the 'minimumLoss' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts LONG_INTEGER_ARRAY price as parameter.
 */

func minimumLoss(price []int64) int64 {
	n := len(price)

	idx := make([]int, n)
	for i := range idx {
		idx[i] = i
	}

	sort.Slice(idx, func(a, b int) bool {
		return price[idx[a]] > price[idx[b]]
	})

	var minLoss int64 = -1

	for k := 0; k < n-1; k++ {
		buyIdx := idx[k]     
		sellIdx := idx[k+1]  

		if buyIdx < sellIdx {
			loss := price[buyIdx] - price[sellIdx]
			if minLoss == -1 || loss < minLoss {
				minLoss = loss
			}
		}
	}

	return minLoss
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

	priceTemp := strings.Split(strings.TrimSpace(readLine(reader)), " ")

	var price []int64

	for i := 0; i < int(n); i++ {
		priceItem, err := strconv.ParseInt(priceTemp[i], 10, 64)
		checkError(err)
		price = append(price, priceItem)
	}

	result := minimumLoss(price)

	fmt.Fprintf(writer, "%d\n", result)

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