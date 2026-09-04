#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

DOMAIN=yunbinliu.com
USER=admin
PASS=123456

log_info "1. 安装 gost..."
which gost &> /dev/null || sudo snap install core gost &> /dev/null

log_info "2. 处理防火墙..."
which firewall-cmd &> /dev/null || sudo apt install -y firewalld &> /dev/null
sudo firewall-cmd --add-port=8001-8008/tcp &> /dev/null

log_info "3. 启动代理..."
gost -L http://:8001                \
     -L http://$USER:$PASS@:8002    \
     -L socks4://:8003              \
     -L socks4a://:8004             \
     -L socks5://:8005              \
     -L socks5://$USER:$PASS@:8006  \
     -F https://$USER:$PASS@$DOMAIN:8008;

