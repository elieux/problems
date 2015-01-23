package main

import (
	"fmt"
	"sync"
)

type Fetcher interface {
	// Fetch returns the body of URL and
	// a slice of URLs found on that page.
	Fetch(url string) (body string, urls []string, err error)
}

type Crawler struct {
	fetched map[string]bool
	checking chan int
	fetcher Fetcher
	w sync.WaitGroup
}

func NewCrawler(fetcher Fetcher) (c Crawler) {
	c.fetcher = fetcher
	c.fetched = make(map[string]bool)
	c.checking = make(chan int, 1)
	c.checking <- 0
	return
}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
func (c Crawler) Crawl(url string, depth int) {
	if depth <= 0 {
		return
	}

	<-c.checking
	defer func() {
		c.checking <- 0
	}()

	if c.fetched[url] {
		fmt.Printf("skipping: %s\n", url)
		return
	}
	c.fetched[url] = true
	c.w.Add(1)
	go func() {
		defer c.w.Done()
		body, urls, err := c.fetcher.Fetch(url)
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Printf("found: %s %q\n", url, body)
		for _, u := range urls {
			c.Crawl(u, depth - 1)
		}
		return
	}()
	return
}

func main() {
	c := NewCrawler(fetcher)
	c.Crawl("http://golang.org/", 4)
	c.w.Wait()
}

// fakeFetcher is Fetcher that returns canned results.
type fakeFetcher map[string]*fakeResult

type fakeResult struct {
	body string
	urls []string
}

func (f fakeFetcher) Fetch(url string) (string, []string, error) {
	if res, ok := f[url]; ok {
		return res.body, res.urls, nil
	}
	return "", nil, fmt.Errorf("not found: %s", url)
}

// fetcher is a populated fakeFetcher.
var fetcher = fakeFetcher{
	"http://golang.org/": &fakeResult{
		"The Go Programming Language",
		[]string{
			"http://golang.org/pkg/",
			"http://golang.org/cmd/",
		},
	},
	"http://golang.org/pkg/": &fakeResult{
		"Packages",
		[]string{
			"http://golang.org/",
			"http://golang.org/cmd/",
			"http://golang.org/pkg/fmt/",
			"http://golang.org/pkg/os/",
		},
	},
	"http://golang.org/pkg/fmt/": &fakeResult{
		"Package fmt",
		[]string{
			"http://golang.org/",
			"http://golang.org/pkg/",
		},
	},
	"http://golang.org/pkg/os/": &fakeResult{
		"Package os",
		[]string{
			"http://golang.org/",
			"http://golang.org/pkg/",
		},
	},
}
