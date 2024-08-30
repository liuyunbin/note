#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

cd /usr/local/openresty/nginx/conf

log_info "备份 nginx ..."
mv nginx.conf nginx.conf-back

function reset() {
    log_info "恢复 nginx ..."
    mv nginx.conf-back nginx.conf
    log_info "重启 nginx ..."
    openresty -s reload
}

trap reset EXIT

cat <<'EOF' > nginx.conf
events {}

http {
    limit_conn_zone $binary_remote_addr zone=addr:10m;
    limit_conn addr 1;
    server {
        listen  80;
        location / {
            content_by_lua_block {
                ngx.sleep(1);
                ngx.say("成功返回");
            }
        }
    }
}
EOF

log_info "重启 nginx ..."
openresty -s reload

sleep 1

log_info "测试 nginx ..."

curl  http://127.0.0.1 &
curl  http://127.0.0.1 &

sleep 3
