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
    if git clone https://github.com/liuyunbin/liuyunbin &> /dev/null; then
        log_info "git --- $@ --- 成功"
    else
        log_info "git --- $@ --- 失败"
    fi
    rm -rf liuyunbin
}

function test_proxy_protocol_help() {
    git config --global http.proxy $@
    test_proxy_base $@
    git config --global --unset http.proxy
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
    test_proxy_base
    log_info ""
}


function test_proxy_use_env_help() {
    log_info "测试 export $1=$@"
    set_proxy_env_empty
    export $1=$2
    test_proxy_base
}

function test_proxy_use_env() {
    test_proxy_use_env_help  http_proxy  http://host-60:8001
    test_proxy_use_env_help https_proxy  http://admin:123456@host-60:8002
    test_proxy_use_env_help   all_proxy  socks4://host-60:8003
    test_proxy_use_env_help  HTTP_PROXY  socks4a://host-60:8004
    test_proxy_use_env_help HTTPS_PROXY  socks5://host-60:8005
    test_proxy_use_env_help   ALL_PROXY  socks5://admin:123456@host-60:8006
    log_info ""
}

log_info "测试未设置代理:"
test_no_proxy

log_info "测试支持的代理协议:"
test_proxy_protocol

log_info "测试使用环境变量来代理:"
test_proxy_use_env

