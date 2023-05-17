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

#SedReplace bash_src ".*\.[hc]" 's/(.*include.*)varargs(\.h.*)/\1stdarg\2/g'

IncludeGuard() {
    local dir=$1
    local filePattern=$2
    local header=$3
    local guard=$4
    local fileList=
    fileList=$(find $dir -type f -regex "$filePattern" 2>/dev/null)
    [ ! -z "$fileList" ] || return 0
    for file in $fileList; do
        awk -v header="$header" -v guard="$guard" '
            {
                if(match($0, "#include [\"<]"header)) {
                    if(!match(prev, guard)){
                        needUpdate=1
                        print "#ifdef " guard
                        print $0
                        print "#endif"
                        next
                    }
                }
                print $0
                prev = $0
            } END {
                exit needUpdate
            }' $file > $file.tmp && rm $file.tmp || mv $file.tmp $file
    done
}

IncludeGuard bash_src ".*\.[hc]" config.h HAVE_CONFIG_H