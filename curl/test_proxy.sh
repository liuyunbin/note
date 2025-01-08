#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

function do_test() {
    log_info "测试: $1..."

    curl -x $1 --silent -o 1.html  http://www.google.com || log_info "失败"
    curl -x $1 --silent -o 1.html https://www.google.com || log_info "失败"
    rm -rf 1.html
}

do_test http://host-60:8001



