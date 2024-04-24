#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

cmd=$(basename $0)

function usage() {
    log_info
    log_info "说明:"
    log_info "    测试命令行参数"
    log_info "使用例如:"
    log_info "    $cmd -h     # 帮助文档"
    log_info "    $cmd -a 123 # 测试"
    log_info
    exit 0
}

while getopts "ha:" arg; do
    case "$arg" in
    h)
        usage
        exit 0
        ;;
    a)
        log_info "a 的参数为 $OPTARG"
        ;;
    ?)
        exit -1
        ;;
    esac
done

shift $(($OPTIND - 1))

function test1() {
    v=456
    log_info "函数内: $v";
}

function test2() {
    local v=456
    log_info "函数内: $v";
}

function test_function() {
    log_info

    v=123
    log_info "测试函数内变量修改: "

    log_info "调用函数前: $v";
    test1
    log_info "调用函数后: $v";

    log_info

    v=123
    log_info "测试函数内局部变量修改: "
    log_info "调用函数前: $v";
    test2
    log_info "调用函数后: $v";
}

function test_array() {
    log_info
    v=(1 2 3)
    v+=(7 8 9)
    log_info "测试数组添加成员 ${v[@]}"
}

test_function
test_array

log_info

read lyb <<< "123 456"

echo $lyb


