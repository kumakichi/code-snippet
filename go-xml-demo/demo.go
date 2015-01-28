package main

import (
	"encoding/xml"
	"fmt"
	"io/ioutil"
	"os"
)

type Return struct {
	XMLName xml.Name `xml:"Return"`
	Version string   `xml:"Code,attr"`
	Result  result   `xml:"Result"`
}

type result struct {
	Title      string  `xml:Title`
	Creator    string  `xml:Creator`
	Publisher  string  `xml:Publisher`
	IssuedDate string  `xml:IssuedDate`
	Content    content `xml:Content`
}

type content struct {
	TotalNum       string   `xml:"TotalNum,attr"`
	Width          string   `xml:"Width,attr"`
	Height         string   `xml:"Height,attr"`
	IsStructureDoc string   `xml:"IsStructureDoc,attr"`
	Items          []string `xml:"item"`
}

func main() {
	content, err := ioutil.ReadFile("./demo.xml")
	checkErr(err)

	r := Return{}
	err = xml.Unmarshal(content, &r)
	checkErr(err)

	indented, err := xml.MarshalIndent(r, "", "\t")
	checkErr(err)

	fmt.Println(string(indented))
}

func checkErr(err error) {
	if err != nil {
		fmt.Println(err.Error())
		os.Exit(-1)
	}
}
