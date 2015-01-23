package main

import (
	"log"
	"net/http"
	"fmt"
)

type String string

type Struct struct {
	Greeting string
	Punct string
	Who string
}

func (s String) ServeHTTP(res http.ResponseWriter, req *http.Request) {
	fmt.Fprintf(res, "%s", string(s))
}

func (s *Struct) ServeHTTP(res http.ResponseWriter, req *http.Request) {
	fmt.Fprintf(res, "%s%s %s", s.Greeting, s.Punct, s.Who)
}

func main() {
	http.Handle("/string", String("I'm a frayed knot."))
	http.Handle("/struct", &Struct{"Hello", ":", "Gophers!"})
	log.Fatal(http.ListenAndServe("localhost:4000", nil))
}
