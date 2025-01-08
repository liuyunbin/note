#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

log_info "1. 安装 gost..."
if which gost &> /dev/null; then
    log_info "gost 已安装, 跳过"
else
    sudo snap install core;
    sudo snap install gost;
    log_info "gost 安装完成"
fi

log_info "2. 处理防火墙端口"
if sudo firewall-cmd --query-port=8001-8008/tcp &> /dev/null; then
    log_info "防火墙端口已开启, 跳过"
else
    sudo firewall-cmd --add-port=8001-8008/tcp;
    log_info "防火墙端口开启完成"
fi

log_info "3. 启动代理, 注意修改域名..."
DOMAIN=yunbinliu.com
USER=admin
PASS=123456

gost -L http://:8001                \
     -L http://$USER:$PASS@:8002    \
     -L socks4://:8003              \
     -L socks4a://:8004             \
     -L socks5://:8005              \
     -L socks5://$USER:$PASS@:8006  \
     -F https://$USER:$PASS@$DOMAIN:8008;

