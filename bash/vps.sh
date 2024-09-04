#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

# 一般没人看到吧
DOMAIN=yunbinliu.com
USER=yunbinliu
PASS=lyb2636196546
PORT=443
SERVICE=https

function handle_certbot() {
    log_info "安装 certbot..."
    if ! which certbot &> /dev/null; then
        apt install snapd &> /dev/null
        snap install --classic certbot &> /dev/null
        ln -s /snap/bin/certbot /usr/bin/certbot
    fi
#    log_info "签证书: $DOMAIN"
    if ! certbot certificates 2> /dev/null | grep "$DOMAIN" &> /dev/null;then
        certbot certonly --standalone -d "$DOMAIN" &> /dev/null
    fi
}

function handle_docker() {
    log_info "安装 docker..."
    if ! which docker &> /dev/null; then
        curl -fsSL https://get.docker.com -o get-docker.sh &> /dev/null
        sh get-docker.sh &> /dev/null
        rm -rf get-docker.sh
    fi
    systemctl start  docker &> /dev/null || true
    systemctl enable docker &> /dev/null
}

function handle_gost() {
    log_info "安装 gost..."
    if ! docker ps -a --format "{{.Names}}" | grep gost &> /dev/null; then
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

    log_info "启动 gost..."
    if ! docker ps --format "{{.Names}}" | grep gost &> /dev/null; then
        docker start gost &> /dev/null
    fi
}

function handle_firewalld() {
    log_info "处理防火墙..."
    apt install -y   firewalld &> /dev/null
    systemctl start  firewalld &> /dev/null || true
    systemctl enable firewalld &> /dev/null
    firewall-cmd --add-service=${SERVICE} --permanent --zone=public &> /dev/null
    firewall-cmd --reload > /dev/null
}

function handle_crontab() {
    log_info "添加定时任务: 更新证书..."
    cmd="certbot renew --force-renewal"
    if ! crontab -l 2> /dev/null | grep "$cmd" &>/dev/null; then
        echo "0 0 1 * * $cmd" >> /var/spool/cron/crontabs/root
    fi

    log_info "添加定时任务: 重启 gost..."
    cmd="docker restart gost"
    if ! crontab -l 2> /dev/null | grep "$cmd" &>/dev/null; then
        echo "5 0 1 * * $cmd" >> /var/spool/cron/crontabs/root
    fi
}

log_info "更新系统..."
apt -y update  &> /dev/null
apt -y upgrade &> /dev/null
log_info "安装常用软件..."
apt install -y git vim python3-pip lrzsz icdiff &> /dev/null

handle_certbot
handle_docker
handle_gost
handle_firewalld
handle_crontab

#    apt install -y man-db
#    unminimize -y
log_info "完成"

