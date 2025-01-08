#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

DOMAIN=yunbinliu.com
USER=admin
PASS=123456

log_info "1. 安装证书..."
which -s certbot || sudo apt install -y certbot  &> /dev/null

log_info "2. 签证书..."
certbot certificates | grep -q "$DOMAIN" || certbot certonly --standalone -d "$DOMAIN"

log_info "3. 安装 docker..."
which -s docker || sudo bash <(curl -fsSL https://get.docker.com)  &> /dev/null
sudo systemctl -q enable docker

log_info "4. 安装 gost"
if ! docker ps -a --format "{{.Names}}" | grep -q '^gost-test$'; then
    CERT_DIR=/etc/letsencrypt
    CERT=${CERT_DIR}/live/${DOMAIN}/fullchain.pem
    KEY=${CERT_DIR}/live/${DOMAIN}/privkey.pem

    docker run -d                                                \
        --name gost-test                                         \
        -v ${CERT_DIR}:${CERT_DIR}:ro                            \
        --net=host                                               \
        ginuerzh/gost -L "https://:8007?cert=${CERT}&key=${KEY}" \
                      -L "https://${USER}:${PASS}@:8008?cert=${CERT}&key=${KEY}"
fi

docker ps --format "{{.Names}}" | grep -q '^gost-test$' || docker start gost-test

log_info "5. 处理防火墙..."
which -s firewall-cmd || sudo apt install -y firewalld
sudo firewall-cmd -q --add-port=8007-8008/tcp

log_info "6. 完成"

