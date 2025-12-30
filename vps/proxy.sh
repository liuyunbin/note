#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

DOMAIN=yunbinliu.com
USER=yunbinliu
PASS=lyb2636196546
PORT=442

log_info "1. 更新系统..."
apt -y -qq update     &> /dev/null # 更新软件源
apt -y -qq upgrade    &> /dev/null # 更新软件
apt -y -qq autoremove &> /dev/null # 卸载没用的软件

log_info "2. 申请证书..."
apt -y -qq install certbot &> /dev/null
certbot certificates 2> /dev/null | grep -q "$DOMAIN" || certbot certonly --standalone -d "$DOMAIN" # 申请证书

log_info "3. 处理 gost..."
which docker &> /dev/null || bash <(curl -fsSL https://get.docker.com) # 安装 docker
systemctl enable docker -q                                             # 开机自动启动

if ! docker ps -a --format "{{.Names}}" | grep -q gost; then
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

docker ps --format "{{.Names}}" | grep -q gost || docker start gost # 启动 gost

log_info "4. 处理防火墙..."
apt -y -qq install firewalld &> /dev/null
systemctl enable firewalld -q
firewall-cmd -q --permanent --zone=public --add-port=$PORT/tcp
firewall-cmd -q --permanent --zone=public --add-service=http    # 更新证书需要
firewall-cmd -q --reload

log_info "5. 添加定时任务..."
apt -y -qq install cron &> /dev/null

# TODO 建立可选择的版本, 使用绝对路径
# 更新证书 80 端口必须开启
cmd="$(which certbot) renew --force-renewal"
crontab -l | grep -q "$cmd" || echo "0 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

cmd="$(which docker) restart gost"
crontab -l | grep -q "$cmd" || echo "5 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

log_info "6. 完成"

