package main

import (
	"fmt"
	"io/ioutil"
	"net/http"

	. "github.com/k4s/phantomgo"
)

func main() {

	fmt.Println("github.com/k4s/phantomgo package test(pure go project)")

	p := &Param{
		Method:       "POST",
		Url:          "http://google.com",
		Header:       http.Header{"Cookie": []string{"your cookies"}},
		UsePhantomJS: true,
		PostBody:     "aaa=111",
	}

	brower := NewPhantom()
	resp, err := brower.Download(p)
	if err != nil {
		panic(err)
	}
	body, err := ioutil.ReadAll(resp.Body)
	fmt.Println(string(body))
}
