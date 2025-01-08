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
    if curl $@ --connect-timeout 5 &> /dev/null; then
        log_info "测试 curl $@ 成功"
    else
        log_info "测试 curl $@ 失败"
    fi
}

function test_proxy_protocol_help() {
    test_proxy_base  http://www.google.com -x $@
    test_proxy_base https://www.google.com -x $@
}

function test_proxy_protocol() {
    test_proxy_protocol_help http://host-60:8001
    test_proxy_protocol_help http://admin:123456@host-60:8002
    test_proxy_protocol_help socks4://host-60:8003
    test_proxy_protocol_help socks4a://host-60:8004
    test_proxy_protocol_help socks5://host-60:8005
    test_proxy_protocol_help socks5://admin:123456@host-60:8006
    test_proxy_protocol_help socks5h://host-60:8005
    test_proxy_protocol_help socks5h://admin:123456@host-60:8006
    test_proxy_protocol_help https://yunbinliu.com:8007
    test_proxy_protocol_help https://admin:123456@yunbinliu.com:8008
    log_info ""
}

function test_no_proxy() {
    set_proxy_env_empty
    test_proxy_base  http://www.google.com
    test_proxy_base https://www.google.com
    log_info ""
}


function test_proxy_use_env_help() {
    log_info "测试 $1=http://host-60:8001"
    set_proxy_env_empty
    export $1=http://host-60:8001
    test_proxy_base $@
}

function test_proxy_use_env() {
    test_proxy_use_env_help  http_proxy  http://www.google.com
    test_proxy_use_env_help https_proxy https://www.google.com
    test_proxy_use_env_help   all_proxy  http://www.google.com https://www.google.com
    test_proxy_use_env_help  HTTP_PROXY  http://www.google.com
    test_proxy_use_env_help HTTPS_PROXY https://www.google.com
    test_proxy_use_env_help   ALL_PROXY  http://www.google.com https://www.google.com
}

log_info "测试未设置代理:"
test_no_proxy

log_info ""
log_info "测试支持的代理协议:"
test_proxy_protocol

log_info ""
log_info "测试环境变量使用代理:"
test_proxy_use_env

