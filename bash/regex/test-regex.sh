#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

log_info
log_info "查找合法的IP: "
v='\d|[1-9]\d|1\d{2}|2[0-4]\d|25[0-5]'
grep -P -o "^\s*(($v)\.){3}($v)\s*\$" 1.txt

log_info
log_info "查找合法的IP: "

v='[0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]'
grep -E -o "^\s*(($v)\.){3}($v)\s*\$" 1.txt

log_info
log_info "测试合法的固定电话: "
grep -P -o '^\s*((\()?0\d{1,3}(?(2)\)|-))?\d{7}\s*$' 2.txt

log_info
log_info "测试合法的固定电话: "
grep -P -o '^\s*(0\d{1,3}-|\(0\d{1,3}\))\d{7}\s*$' 2.txt

