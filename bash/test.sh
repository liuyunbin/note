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

function test_if() {
    log_info
    v=./readme.md
    msg="测试 if 语句: "
    if [[ -d $v ]]; then
        msg=$msg" $v 是一个目录"
    elif [[ -f $v ]]; then
        msg=$msg" $v 是一个普通文件"
    else
        msg=$msg" $v 是一个其他文件"
    fi
    log_info "$msg"
}

function test_while() {
    log_info
    i=0
    msg="测试 while 语句: "
    while (( i < 5 )); do
        msg=$msg" $i"
        ((++i))
    done
    log_info "$msg"
}

function test_for() {
    log_info
    msg="测试 for 语句: "
    for (( i = 0; i < 5; ++i)); do
        msg=$msg" $i"
    done
    log_info "$msg"

    msg="测试 for 语句: "
    for i in {0..5}; do
        msg=$msg" $i"
    done
    log_info "$msg"

    msg="测试 for 语句: "
    for i in ./t*.sh; do
        msg=$msg" $i"
    done
    log_info "$msg"
}

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

test_if
test_while
test_for
test_function
test_array

log_info

read lyb <<< "123 456"

echo $lyb


