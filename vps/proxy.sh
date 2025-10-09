#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

DOMAIN=yunbinliu.com
USER=yunbinliu
PASS=lyb2636196546
PORT=442

function update_os() {
    apt -y -qq update     &> /dev/null # 更新软件源
    apt -y -qq upgrade    &> /dev/null # 更新软件
    apt -y -qq autoremove &> /dev/null # 卸载没用的软件
}

function handle_cerbot() {
    apt -y -qq install certbot
    certbot certificates | grep "$DOMAIN" || certbot certonly --standalone -d "$DOMAIN" # 申请证书
}

function handle_gost() {
    which docker || bash <(curl -fsSL https://get.docker.com) # 安装 docker
    systemctl enable docker                                   # 开机自动启动

    if ! docker ps -a --format "{{.Names}}" | grep gost; then
        BIND_IP=0.0.0.0
        CERT_DIR=/etc/letsencrypt
        CERT=${CERT_DIR}/live/${DOMAIN}/fullchain.pem
        KEY=${CERT_DIR}/live/${DOMAIN}/privkey.pem

        docker run -d \
            --name gost \
            -v ${CERT_DIR}:${CERT_DIR}:ro \
            --net=host \
            ginuerzh/gost -L "http2://${USER}:${PASS}@${BIND_IP}:${PORT}?cert=${CERT}&key=${KEY}&probe_resist=code:400&knock=www.google.com"
    fi

    docker ps --format "{{.Names}}" | grep gost || docker start gost # 启动 gost
}

function handle_firewall() {
    apt -y -qq install firewalld
    systemctl enable firewalld
    firewall-cmd --permanent --zone=public --add-port=$PORT/tcp --zone=public
    firewall-cmd --reload
}

function handle_cron() {
    apt -y -qq install cron

    cmd="certbot renew --force-renewal"
    crontab -l | grep "$cmd" || echo "0 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

    cmd="docker restart gost"
    crontab -l | grep "$cmd" || echo "5 0 1 * * $cmd" >> /var/spool/cron/crontabs/root
}



log_info "1. 更新系统..."
update_os

log_info "2. 申请证书..."
handle_cerbot

log_info "3. 处理 gost..."
handle_gost

log_info "4. 处理防火墙..."
handle_firewall

log_info "5. 添加定时任务..."
handle_cron

log_info "完成"

