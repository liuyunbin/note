#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

function do_test_base() {
    argv=${2:+-x $2}
    if curl $argv $1 --connect-timeout 3 &> /dev/null; then
        log_info "测试 $1 成功"
    else
        log_info "测试 $1 失败"
    fi
}

function do_test() {
    log_info ""
    log_info "测试 $1"
    log_info "测试未设置代理:"
     http_proxy=
    https_proxy=
    do_test_base  http://www.google.com
    do_test_base https://www.google.com

    log_info "测试命令中使用代理:"
     http_proxy=
    https_proxy=
    do_test_base  http://www.google.com $1
    do_test_base https://www.google.com $1

    log_info "测试环境变量中使用代理:"
     http_proxy=$1
    https_proxy=
    do_test_base  http://www.google.com

     http_proxy=
    https_proxy=$1
    do_test_base https://www.google.com
}

do_test http://host-60:8001
do_test http://admin:123456@host-60:8002
do_test socks4://host-60:8003
do_test socks4a://host-60:8004
do_test socks5://host-60:8005
do_test socks5://admin:123456@host-60:8006
do_test socks5h://host-60:8005
do_test socks5h://admin:123456@host-60:8006
do_test https://yunbinliu.com:8007
do_test https://admin:123456@yunbinliu.com:8008

