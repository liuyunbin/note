#!/bin/bash

# bash <(curl -fsSL https://raw.githubusercontent.com/liuyunbin/note/master/vps.sh)

set -ueo pipefail # 使用未初始化的变量, 命令报错, 管道报错, 直接退出

exec &>/dev/null  # 禁止命令输出

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

DOMAIN=yunbinliu.com       # 域名
USER=yunbinliu             # 用户名
PASS=lyb2636196546         # 密码
PORT=442                   # gost 端口号
SERVICE=https              # 更新域名使用的服务
MAIL=yunbinliu@outlook.com # 邮箱

log_info "1. 更新系统"
log_info "1.1 更新软件源"
apt -y update

log_info "1.2 更新软件"
apt -y upgrade

log_info "1.3 自动卸载没用的软件"
apt -y autoremove

log_info "2. 安装软件"
log_info "2.1 安装常用软件"
apt -y install certbot firewalld cron man-db g++ vim lrzsz man-db git icdiff

log_info "2.2 安装 docker"
which docker || bash <(curl -fsSL https://get.docker.com)

log_info "2.3 解压 man-db"
echo y | unminimize

log_info "3. 设置 docker firewalld 开机自动启动"
systemctl enable docker firewalld

log_info "4. 处理防火墙"
log_info "4.1 开启端口号 ${PORT} 和 服务 ${SERVICE}"
firewall-cmd --permanent --zone=public --add-port=${PORT}/tcp   # 代理
firewall-cmd --permanent --zone=public --add-service=${SERVICE} # 更新证书

log_info "4.2 重新加载防火墙"
firewall-cmd --reload

log_info "5. 初始化 Git"
log_info "5.1 配置用户名"
git config --global user.name "Yunbin Liu"

log_info "5.2 配置邮箱"
git config --global user.email yunbinliu@outlook.com

log_info "5.3 配置编辑器"
git config --global core.editor vim

log_info "5.4 配置日期格式"
git config --global log.date iso

log_info "5.5 配置简要命令"
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status

log_info "5.6 配置日志显示格式"
git config --global alias.lg "log --pretty=format:'%ad %h %s %d %C(bold)%an%Creset' --graph"

log_info "5.7 中文显示不乱码"
git config --global core.quotepath false

log_info "5.8 查看配置"
git config --global --list

log_info "5.9 生成秘钥"
[[ -f ~/.ssh/id_ed25519.pub ]] || ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N ""

log_info "5.10 复制公钥到 GitHub, 按回车继续..."
read

log_info "5.11 测试连接"
ssh -T git@github.com -o BatchMode=yes -o StrictHostKeyChecking=no &> /dev/tty || true

log_info "6. 克隆仓库 note"
mkdir -p ~/github
cd ~/github
[[ -d note ]] || git clone git@github.com:liuyunbin/note

log_info "7. 配置 vim"
cp ~/github/note/vimrc ~/.vimrc

log_info "8. 配置 bashrc"
log_info "8.1 配置"
echo ". ~/github/note/bashrc" >> ~/.bashrc
log_info "8.2 请执行: . ~/.bashrc"

log_info "9. 申请证书"
certbot certificates | grep $DOMAIN || certbot certonly --standalone --agree-tos -n -m $MAIL -d $DOMAIN

log_info "10. 处理 gost"
log_info "10.1 配置代理"
if ! docker ps -a --format "{{.Names}}" | grep gost; then
    BIND_IP=0.0.0.0                                # 绑定的IP
    CERT_DIR=/etc/letsencrypt                      # 证书的目录
    CERT=${CERT_DIR}/live/${DOMAIN}/fullchain.pem  # 证书的公钥
    KEY=${CERT_DIR}/live/${DOMAIN}/privkey.pem     # 证书的私钥

    docker run -d \
        --name gost \
        -v ${CERT_DIR}:${CERT_DIR}:ro \
        --net=host \
        ginuerzh/gost -L "http2://${USER}:${PASS}@${BIND_IP}:${PORT}?cert=${CERT}&key=${KEY}&probe_resist=code:400&knock=www.google.com"
fi

log_info "10.2 启动代理"
docker ps --format "{{.Names}}" | grep gost || docker start gost

log_info "11. 添加定时任务"
log_info "11.1 添加任务: 更新证书, 注意, 更新证书时, 端口号不能被占用"
cmd="$(which certbot) renew --force-renewal"
crontab -l | grep "$cmd" || echo "0 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

log_info "11.2 添加任务: 重启 gost"
cmd="$(which docker) restart gost"
crontab -l | grep "$cmd" || echo "5 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

log_info "12. 完成"

