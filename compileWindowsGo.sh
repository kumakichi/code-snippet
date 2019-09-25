#!/bin/bash

# MSGOROOT=~/fordocker/go1.10-windows-386/ ./compileWindowsGo.sh ~/Downloads/bkmk_v2.go

msGOROOT=""
msGOPATH=""
msDrive="Z"
outBatName="c.bat"
wineloaderPath="/Applications/CrossOver.app/Contents/SharedSupport/CrossOver/bin/wineloader"

if [ $# -ne 1 ]
then
	echo "Usage: $0 go-source-file"
	exit
fi

srcPath="$1"

function abspath { # https://stackoverflow.com/questions/7126580/expand-a-possible-relative-path-in-bash
    if [[ -d "$1" ]]
    then
        pushd "$1" >/dev/null
        pwd
        popd >/dev/null
    elif [[ -e $1 ]]
    then
        pushd "$(dirname "$1")" >/dev/null
        echo "$(pwd)/$(basename "$1")"
        popd >/dev/null
    else
        echo "$1" does not exist! >&2
        return 127
    fi
}

if [ "$MSGOROOT" != "" ]
then
	msGOROOT="$MSGOROOT"
else
	msGOROOT="$GOROOT"
fi

if [ "$MSGOPATH" != "" ]
then
	msGOPATH="$MSGOPATH"
else
	msGOPATH="$GOPATH"
fi

msGOROOT="${msDrive}:$(echo "$msGOROOT" | tr '/' '\\')"
msGOPATH="${msDrive}:$(echo "$msGOPATH" | tr '/' '\\')"
srcExpandedPath=$(abspath "$srcPath")
srcMSPath="${msDrive}:$(echo "$srcExpandedPath" | tr '/' '\\')"
outMSPath=$(echo "$srcMSPath" | sed 's@.go$@.exe@g')

cat>"$outBatName"<<EOF
set GOROOT=${msGOROOT}
set GOPATH=${msGOPATH}
set path=%path%;%GOROOT%\bin;%GOPATH%\bin
go build -ldflags="-s" -o "$outMSPath" "$srcMSPath"
EOF

#echo "do the following steps:"
#echo "1. ${wineloaderPath} cmd"
#echo "2. ${msDrive}:$(abspath ${PWD} | tr '/' '\\')\\$outBatName"
#echo "3. get generated exe file : $(echo ${srcExpandedPath} | sed 's@.go$@.exe@g')"
#echo "4. rm $(abspath $outBatName)"

eval "${wineloaderPath} cmd /k $outBatName"
echo "get generated exe file : $(echo ${srcExpandedPath} | sed 's@.go$@.exe@g')"
rm $outBatName
