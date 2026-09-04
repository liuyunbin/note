#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

test1_data=/usr/local/openresty/nginx/html/test1.data
test2_data=/usr/local/openresty/nginx/html/test2.data
dd if=/dev/zero of=$test1_data bs=1K count=50 &> /dev/null
dd if=/dev/zero of=$test2_data bs=1K count=50 &> /dev/null

cd /usr/local/openresty/nginx/conf

log_info "备份 nginx ..."
mv nginx.conf nginx.conf-back

function reset() {
    log_info "恢复 nginx ..."
    mv nginx.conf-back nginx.conf
    rm $test1_data $test2_data
    log_info "重启 nginx ..."
    openresty -s reload
}

trap reset EXIT

cat <<'EOF' > nginx.conf
events {}

http {
    server {
        listen  80;
        location /test1.data {
            limit_rate 10k;
        }
        location /test2.data {
        }
    }
}
EOF

log_info "重启 nginx ..."
openresty -s reload

sleep 1

log_info "测试 nginx 限速..."
curl  http://127.0.0.1/test1.data | pv

log_info "测试 nginx 不限速..."
curl  http://127.0.0.1/test2.data | pv

