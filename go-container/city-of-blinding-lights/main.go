// https://www.hackerrank.com/challenges/floyd-city-of-blinding-lights/problem?isFullScreen=true
package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

const INF int32 = 1 << 30 // large enough; node ≤ 400, weight ≤ 350, so no overflow risk when summing

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 16*1024*1024)
	writer := bufio.NewWriterSize(os.Stdout, 16*1024*1024)
	defer writer.Flush()

	roadNodesEdges := strings.Split(readLine(reader), " ")

	roadNodes, err := strconv.ParseInt(roadNodesEdges[0], 10, 64)
	checkError(err)

	roadEdges, err := strconv.ParseInt(roadNodesEdges[1], 10, 64)
	checkError(err)

	n := int(roadNodes)

	// Distance matrix, vertices numbered 1..n
	dist := make([][]int32, n+1)
	for i := 0; i <= n; i++ {
		dist[i] = make([]int32, n+1)
		for j := 0; j <= n; j++ {
			if i == j {
				dist[i][j] = 0
			} else {
				dist[i][j] = INF
			}
		}
	}

	for i := 0; i < int(roadEdges); i++ {
		edgeFromToWeight := strings.Split(readLine(reader), " ")

		edgeFrom, err := strconv.ParseInt(edgeFromToWeight[0], 10, 64)
		checkError(err)

		edgeTo, err := strconv.ParseInt(edgeFromToWeight[1], 10, 64)
		checkError(err)

		edgeWeight, err := strconv.ParseInt(edgeFromToWeight[2], 10, 64)
		checkError(err)

		u := int(edgeFrom)
		v := int(edgeTo)
		w := int32(edgeWeight)

		// If there are duplicate u->v edges, the LAST one wins (overwrite, not min)
		dist[u][v] = w
	}

	// Floyd-Warshall O(n^3)
	for k := 1; k <= n; k++ {
		dk := dist[k]
		for i := 1; i <= n; i++ {
			dik := dist[i][k]
			if dik == INF {
				continue
			}
			di := dist[i]
			for j := 1; j <= n; j++ {
				if dk[j] == INF {
					continue
				}
				nd := dik + dk[j]
				if nd < di[j] {
					di[j] = nd
				}
			}
		}
	}

	qTemp, err := strconv.ParseInt(strings.TrimSpace(readLine(reader)), 10, 64)
	checkError(err)
	q := int(qTemp)

	for qItr := 0; qItr < q; qItr++ {
		firstMultipleInput := strings.Split(strings.TrimSpace(readLine(reader)), " ")

		xTemp, err := strconv.ParseInt(firstMultipleInput[0], 10, 64)
		checkError(err)
		x := int(xTemp)

		yTemp, err := strconv.ParseInt(firstMultipleInput[1], 10, 64)
		checkError(err)
		y := int(yTemp)

		d := dist[x][y]
		if d >= INF {
			fmt.Fprintln(writer, -1)
		} else {
			fmt.Fprintln(writer, d)
		}
	}
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