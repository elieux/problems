package main

import (
	"code.google.com/p/go-tour/pic"
	"image"
	"image/color"
)

type Image struct {
	data [][]uint8
}

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

func (p Image) ColorModel() color.Model {
	return color.RGBAModel
}

func (p Image) Bounds() image.Rectangle {
	return image.Rect(0, 0, len(p.data), len(p.data[0]))
}

func (p Image) At(x, y int) color.Color {
	return color.RGBA{p.data[y][x], p.data[y][x], 255, 255}
}

func main() {
	m := Image{data: Pic(128, 128)}
	pic.ShowImage(m)
}
