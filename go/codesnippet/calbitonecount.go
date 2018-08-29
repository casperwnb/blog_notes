package main

var pc [256]byte

func init() {
	// 初始化0~255之间每个数对应的1的个数
	for i := range pc {
		pc[i] = pc[i/2] + byte(i&1)
	}
}

// 计算每8个位中1的个数
// 使用查表法计算1的个数
func PopCount(x uint64) int {
	return int(pc[byte(x>>(0*8))] +
		pc[byte(x>>(1*8))] +
		pc[byte(x>>(2*8))] +
		pc[byte(x>>(3*8))] +
		pc[byte(x>>(4*8))] +
		pc[byte(x>>(5*8))] +
		pc[byte(x>>(6*8))] +
		pc[byte(x>>(7*8))])
}

func PopCount2(x uint64) int {
	count := 0
	for x != 0 {
		x &= (x - 1)
		count++
	}
}
