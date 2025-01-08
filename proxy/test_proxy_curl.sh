#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

function do_test_base() {
    argv=${2:+-x $2}
    if curl $argv $1 --connect-timeout 5 &> /dev/null; then
        log_info "测试 curl $argv $1 成功"
    else
        log_info "测试 curl $argv $1 失败"
    fi
}

function do_test() {
    do_test_base  http://www.google.com $1
    do_test_base https://www.google.com $1
}

function test_proxy_env() {
    export  http_proxy=
    export https_proxy=
    export   all_proxy=
    export  HTTP_PROXY=
    export HTTPS_PROXY=
    export   ALL_PROXY=
    if [[ $# != 0 ]]; then
        log_info ""
        log_info "测试 $1=http://host-60:8001"
        export $1=http://host-60:8001
        do_test_base $2
        [[ $# == 2 ]] || do_test_base $3
    else
        do_test_base  http://www.google.com
        do_test_base https://www.google.com
    fi
}

function test_proxy_command() {
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
}

log_info ""
log_info "测试未设置代理:"
test_proxy_env

log_info ""
log_info "测试命令行中设置代理:"
test_proxy_command

log_info ""
log_info "测试环境变量使用代理:"
test_proxy_env http_proxy    http://www.google.com
test_proxy_env https_proxy  https://www.google.com
test_proxy_env all_proxy     http://www.google.com https://www.google.com
test_proxy_env HTTP_PROXY    http://www.google.com
test_proxy_env HTTPS_PROXY  https://www.google.com
test_proxy_env ALL_PROXY     http://www.google.com https://www.google.com

