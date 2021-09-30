#!/bin/bash
set -o nounset  # 使用未初始化的变量报错, 同 -u
set -o errexit  # 只要发生错误就退出 -e
set -o pipefail # 只要管道发生错误就退出
set -E          # 即使意外退出, 也会执行 trap 命令

#set -o xtrace   # 执行前打印命令 同 -x

function log_info() {
    # 白色
    echo -e "\033[37;1m[$(date +'%Y-%m-%d %H:%M:%S')]: $@\033[0m"
}

function log_warning() {
    # 蓝色
    echo -e "\033[34;1m[$(date +'%Y-%m-%d %H:%M:%S')]: $@\033[0m"
}

function log_error() {
    # 黄色
    echo -e "\033[33;1m[$(date +'%Y-%m-%d %H:%M:%S')]: $@\033[0m"
}

function log_fatal() {
    # 红色
    echo -e "\033[31;1m[$(date +'%Y-%m-%d %H:%M:%S')]: $@\033[0m"
    exit -1
}

function usage() {
    cat <<EOF
Usage:
    这是一个脚本模板
    使用例如:
EOF
    exit 0
}

(( $# >= 1 )) && [[ $1 == "-h" || $1 == "--help" ]] && usage

log_info info
log_warning warning
log_error error
log_fatal fatal

