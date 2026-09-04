#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

function set_proxy_env_empty() {
    export  http_proxy=
    export https_proxy=
    export   all_proxy=
    export  HTTP_PROXY=
    export HTTPS_PROXY=
    export   ALL_PROXY=
}

function test_proxy_base() {
    if nc -w 5 -z $@ yunbinliu.com 8000; then
        log_info "nc $@ yunbinliu.com 8000 --- 成功"
    else
        log_info "nc $@ yunbinliu.com 8000 --- 失败"
    fi
}

function test_proxy_protocol_help() {
    if [[ $# == 2 ]]; then
    	test_proxy_base --proxy-type $1 --proxy $2
    else
    	test_proxy_base --proxy-type $1 --proxy $2 --proxy-auth $3
    fi
}

function test_proxy_protocol() {
    test_proxy_protocol_help http   host-60:8001
    test_proxy_protocol_help http   host-60:8002       admin:123456
    test_proxy_protocol_help socks4 host-60:8003
    test_proxy_protocol_help socks4 host-60:8004
    test_proxy_protocol_help socks5 host-60:8005
    test_proxy_protocol_help socks5 host-60:8006       admin:123456
    test_proxy_protocol_help http   yunbinliu.com:8007
    test_proxy_protocol_help http   yunbinliu.com:8008
    log_info ""
}

function test_no_proxy() {
    set_proxy_env_empty
    test_proxy_base
    log_info ""
}


function test_proxy_use_env_help() {
    log_info "测试 export $1=http://host-60:8001"
    set_proxy_env_empty
    export $1=http://host-60:8001
    test_proxy_base
}

function test_proxy_use_env() {
    test_proxy_use_env_help  http_proxy
    test_proxy_use_env_help https_proxy
    test_proxy_use_env_help   all_proxy
    test_proxy_use_env_help  HTTP_PROXY
    test_proxy_use_env_help HTTPS_PROXY
    test_proxy_use_env_help   ALL_PROXY
    log_info ""
}

log_info "测试未设置代理:"
test_no_proxy

log_info "测试支持的代理协议:"
test_proxy_protocol

log_info "测试使用环境变量来代理:"
test_proxy_use_env

