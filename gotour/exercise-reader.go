package main

import "code.google.com/p/go-tour/reader"

type MyReader struct{}

func (MyReader) Read(buf []byte) (int, error) {
	for i := range buf {
		buf[i] = 'A'
	}
	return len(buf), nil
}

func main() {
	reader.Validate(MyReader{})
}
