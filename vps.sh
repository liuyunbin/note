#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

DOMAIN=yunbinliu.com
USER=yunbinliu
PASS=lyb2636196546
PORT=443
SERVICE=https

function update_os() {
    apt -y -qq update     # 更新软件源
    apt -y -qq upgrade    # 更新软件
    apt -y -qq autoremove # 卸载没用的软件
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
    firewall-cmd --add-service=${SERVICE} --permanent --zone=public
    firewall-cmd --reload
}

function handle_cron() {
    apt -y -qq cron

    cmd="certbot renew --force-renewal"
    crontab -l | grep "$cmd" || echo "0 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

    cmd="docker restart gost"
    crontab -l | grep "$cmd" || echo "5 0 1 * * $cmd" >> /var/spool/cron/crontabs/root
}

function handle_user() {
    sudo useradd -m -s /bin/bash lyb || true  # 添加用户
    echo "lyb:654321" | sudo chpasswd         # 设置密码

    chmod +w /etc/sudoers
    grep -q lyb /etc/sudoers || echo "lyb	ALL=(ALL:ALL) ALL" >> /etc/sudoers # 赋予 sudo 权限
    chmod -w /etc/sudoers

    grep -q lyb /etc/ssh/sshd_config || echo "DenyUsers lyb" >> /etc/ssh/sshd_config # 禁止用户使用 ssh 登录
    systemctl restart ssh

    su - lyb
}

function handle_git() {
    apt -y -qq install git icdiff

    log_info "1. 配置用户名"
    git config --global user.name "Yunbin Liu"

    log_info "2. 配置邮箱"
    git config --global user.email yunbinliu@outlook.com

    log_info "3. 配置编辑器"
    git config --global core.editor vim

    log_info "4. 配置日期格式"
    git config --global log.date iso

    log_info "5. 配置简要命令"
    git config --global alias.co checkout
    git config --global alias.br branch
    git config --global alias.ci commit
    git config --global alias.st status

    log_info "6. 配置日志显示格式"
    git config --global alias.lg "log --pretty=format:'%ad %h %s %d %C(bold)%an%Creset' --graph"

    log_info "7. 中文显示不乱码"
    git config --global core.quotepath false

    log_info "8. 查看配置"
    git config --global --list

    log_info "9. 生成秘钥"
    [[ -f ~/.ssh/id_ed25519.pub ]] || ssh-keygen -t ed25519

    log_info "10. 复制公钥到 GitHub, 按回车继续..."
    read

    log_info "11. 测试连接"
    ssh -T git@github.com

    log_info "12. 初始化仓库"
    cd && mkdir -p github && cd github
    git clone git@github.com:liuyunbin/note
}

function handle_vim() {
    apt -y -qq install vim
    cp ~/github/note/vimrc ~/.vimrc
}

function handle_other_soft() {
    apt -y -qq install lrzsz man-db
    unminimize
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

log_info "6. 处理用户..."
handle_user

log_info "7. 处理 git..."
handle_git

log_info "8. 处理 vim..."
handle_vim

log_info "9. 安装其他常用软件..."
handle_other_soft

log_info "完成"

