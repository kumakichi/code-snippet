#!/bin/bash

# referenced: http://stackoverflow.com/questions/59895/can-a-bash-script-tell-what-directory-its-stored-in
SCRIPT_PATH=${BASH_SOURCE[0]}
if [ -L "${SCRIPT_PATH}" ]
then
    SCRIPT_PATH=$(readlink $SCRIPT_PATH)
fi
SCRIPT_DIR="$( cd "$( dirname "${SCRIPT_PATH}" )" && pwd )"
echo $SCRIPT_DIR
