package main

import "code.google.com/p/go-tour/pic"

func Pic(dx, dy int) (pic [][]uint8) {
	pic = make([][]uint8, dy)
	for y := range pic {
		pic[y] = make([]uint8, dx)
		for x := range pic[y] {
			pic[y][x] = uint8(x + y)
		}
	}
	return
}

func main() {
	pic.Show(Pic)
}
