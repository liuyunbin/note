#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

data="
1
2


3
4
5

"

log_info "逆序输出文件的内容"
sed -n '1!G; h; $p'        <<< "$data"

log_info "输出最后的三行"
sed    ':start; $q; N; 4,$D; b start' <<< "$data"

log_info "删除连续的空行 -- 太绕了, 能看懂即可"
sed    '/./,/^$/!d'  <<< "$data"

log_info "删除文件末尾的空行 -- 能理解即可, 太绕了"
sed    ':start; /^\n*$/{$d; N; b start}' <<< "$data"

