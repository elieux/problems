package main

import (
	"io"
	"os"
	"strings"
)

type rot13Reader struct {
	r io.Reader
}

func (r rot13Reader) Read(buf []byte) (n int, err error) {
	n, err = r.r.Read(buf)
	for i := 0; i < n; i++ {
		switch {
		case 'A' <= buf[i] && buf[i] <= 'Z':
			buf[i] = (buf[i] - 'A' + 13) % ('Z' - 'A' + 1) + 'A'
		case 'a' <= buf[i] && buf[i] <= 'z':
			buf[i] = (buf[i] - 'a' + 13) % ('z' - 'a' + 1) + 'a'
		}
	}
	return
}

func main() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	io.Copy(os.Stdout, &r)
}
