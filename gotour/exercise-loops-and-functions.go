package main

import (
	"fmt"
	"math"
)

func Sqrt(x float64) (z float64) {
	z = 1.0
	delta := (z*z - x) / (2*z)
	for math.Abs(delta) > 1e-12 {
		z -= delta
		delta = (z*z - x) / (2*z)
	}
	return
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(math.Sqrt(2))
}
