package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	var prettyJSON bytes.Buffer

	fp, err := os.Open(os.Args[1])
	errExit(err)
	defer fp.Close()

	b, err := ioutil.ReadAll(fp)
	errExit(err)

	err = json.Indent(&prettyJSON, b, "", "\t")
	errExit(err)

	fmt.Println(string(prettyJSON.Bytes()))
}

func errExit(err error) {
	if err != nil {
		fmt.Println(err.Error())
		os.Exit(-1)
	}
}
