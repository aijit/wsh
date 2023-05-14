#!/bin/bash

SedReplace() {
    local dir=$1
    local filePattern=$2
    local sedExp=$3
    local fileList=
    fileList=$(find $dir -type f -regex "$filePattern" 2>/dev/null)
    [ ! -z "$fileList" ] || return 0
    sed -i -r -E "$sedExp" $fileList
}

SedReplace v01 ".*\.[hc]" 's/(.*include.*)varargs(\.h.*)/\1stdarg\2/g'