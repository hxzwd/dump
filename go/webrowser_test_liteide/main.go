package main

import (
	"fmt"
	"io/ioutil"
	"net/http"

	. "github.com/k4s/webrowser"
)

func main() {
	p := &Param{
		Method:       "GET",
		Url:          "http://weibo.com/kasli/home?wvr=5",
		Header:       http.Header{"Cookie": []string{"your cookie"}},
		UsePhantomJS: true,
	}
	brower := NewWebrowse()
	resp, err := brower.Download(p)
	if err != nil {
		fmt.Println(err)
	}
	body, err := ioutil.ReadAll(resp.Body)
	fmt.Println(string(body))
	fmt.Println(resp.Cookies())
}
