package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
)

func main() {
	fmt.Println("Read html page with JavaScript required(without liteide)")
	url := "https://vk.com/kaf33"
	fmt.Printf("Target URL is %s\n", url)
	response, err := http.Get(url)
	
	if err != nil {
		panic(err)
	}
	
	defer response.Body.Close()

	html, err := ioutil.ReadAll(response.Body)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Body:\n%s\n", html)


}
