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

# 1. 安装常用软件
log_info "1. 安装常用软件"


sudo apt -y update                       # 更新软件源
sudo apt -y upgrade                      # 更新软件
sudo apt -y install git vim lrzsz icdiff # 安装常用软件
sudo apt -y autoremove                   # 卸载多余的软件

# 2. 安装 certbot, 签证书
log_info "2. 安装 certbot, 签证书"
sudo apt -y install certbot
certbot certificates | grep "$DOMAIN" || sudo certbot certonly --standalone -d "$DOMAIN"

# 3. 安装 docker
log_info "3. 安装 docker"
which docker || sudo bash <(curl -fsSL https://get.docker.com)
sudo systemctl enable docker

# 4. 安装 gost
log_info "4. 安装 gost"
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

docker ps --format "{{.Names}}" | grep gost || docker start gost

# 5. 处理防火墙
log_info "5. 处理防火墙"
apt -y install   firewalld
systemctl enable firewalld
firewall-cmd --add-service=${SERVICE} --permanent --zone=public
firewall-cmd --reload

# 6. 添加定时任务
log_info "6. 添加定时任务"
apt -y install  cron

cmd="certbot renew --force-renewal"
crontab -l | grep "$cmd" || echo "0 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

cmd="docker restart gost"
crontab -l | grep "$cmd" || echo "5 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

# 7. 安装 man 文档
log_info "7. 安装 man 文档"
apt -y install man-db
#unminimize

log_info "完成"

