package main

func displayBinary(a int) string {
	if a == 0 {
		return "0"
	}
	temp := a
	sign := ""
	if a < 0 {
		temp = -a
		sign = "-"
	}
	result := ""
	for temp > 0 {
		if temp%2 == 0 {
			result = "0" + result
		} else {
			result = "1" + result
		}
		temp = temp / 2
	}
	return sign + result
}

func and(a int, b int) int {
	return a & b
}

func or(a int, b int) int {
	return a | b
}

func xor(a int, b int) int {
	return a ^ b
}

func not(a int) int {
	return ^a
}

func leftShift(a int, n int) int {
	return a << n
}

func rightShift(a int, n int) int {
	return a >> n
}

func checkKIndexBit(a int, k int) int {
	if a&(1<<k) != 0 {
		return 1
	}
	return 0
}

func turnOnKIndexBit(a int, k int) int {
	return a | (1 << k)
}

func turnOffKIndexBit(a int, k int) int {
	return a & ^(1 << k)
}

func toggleKIndexBit(a int, k int) int {
	return a ^ (1 << k)
}

func countBits(x int) int {
	count := 0
	for x > 0 {
		x = x & (x - 1)
		count++
	}
	return count
}
