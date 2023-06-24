# Description: This script is used to configure the build system.
wshroot=$(cd $(dirname $0)/..; pwd)
CMakeConfig(){
    local build_dir=$1
    local build_type=Debug
    [ -z $2 ] || build_type=$2
    local apply="cmake -G Ninja \
        -S ${wshroot} \
        -B ${build_dir} \
        -DCMAKE_BUILD_TYPE=${build_type}"
    echo $apply
    $apply
}
CMakeConfig ${wshroot}/build $1