#!/bin/bash

# bash <(curl -fsSL https://raw.githubusercontent.com/liuyunbin/note/master/vps.sh)

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

DOMAIN=yunbinliu.com            # 域名
USER=yunbinliu                  # 用户名
PASS=lyb2636196546              # 密码
PORT=442                        # gost 端口号
SERVICE=https                   # 更新域名使用的服务
mail=yunbinliu@outlook.com      # 邮箱

log_info "1. 更新系统"
apt -y update     # 更新软件源
apt -y upgrade    # 更新软件
apt -y autoremove # 卸载没用的软件

log_info "2. 安装软件"
apt -y install certbot firewalld cron man-db g++ vim lrzsz man-db git icdiff # 安装常用软件
which -s docker || bash <(curl -fsSL https://get.docker.com)                 # 安装 docker
echo y  | unminimize                                                             # 解压 man-db

log_info "3. 配置 Git"
log_info "3.1 配置用户名"
git config --global user.name "Yunbin Liu"

log_info "3.2 配置邮箱"
git config --global user.email yunbinliu@outlook.com

log_info "3.3 配置编辑器"
git config --global core.editor vim

log_info "3.4 配置日期格式"
git config --global log.date iso

log_info "3.5 配置简要命令"
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status

log_info "3.6 配置日志显示格式"
git config --global alias.lg "log --pretty=format:'%ad %h %s %d %C(bold)%an%Creset' --graph"

log_info "3.7 中文显示不乱码"
git config --global core.quotepath false

log_info "3.8 查看配置"
git config --global --list

log_info "3.9 生成秘钥"
[[ -f ~/.ssh/id_ed25519.pub ]] || ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N ""

log_info "3.10 复制公钥到 GitHub, 按回车继续..."
read

log_info "3.11 测试连接"
ssh -T git@github.com -o BatchMode=yes -o StrictHostKeyChecking=no

exit 0

















log_info "2. 申请证书..."
certbot certificates | grep $DOMAIN || certbot certonly --standalone --agree-tos -n -m $mail -d $DOMAIN # 申请证书

log_info "3. 处理 gost..."
systemctl enable docker                                   # 开机自动启动

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
        # 配置代理
fi

docker ps --format "{{.Names}}" | grep gost || docker start gost # 启动 gost

log_info "4. 处理防火墙..."
systemctl enable firewalld                                      # 开机自动启动
firewall-cmd --permanent --zone=public --add-port=442/tcp       # 代理的端口号
firewall-cmd --permanent --zone=public --add-service=${SERVICE} # 更新证书的端口号
firewall-cmd --reload                                           # 重新加载防火墙

log_info "5. 添加定时任务..."

cmd="certbot renew --force-renewal"
crontab -l | grep "$cmd" || echo "0 0 1 * * $cmd" >> /var/spool/cron/crontabs/root # 更新更新证书

cmd="docker restart gost"
crontab -l | grep "$cmd" || echo "5 0 1 * * $cmd" >> /var/spool/cron/crontabs/root # 重启 gost


log_info "8. 处理 vim..."
    cp ~/github/note/vimrc ~/.vimrc

log_info "9. 安装其他常用软件..."
    unminimize

log_info "完成"


#
#### 7. 初始化 note
#```
#mkdir -p ~/github
#cd ~/github
#git clone git@github.com:liuyunbin/note
#```
#
#### 8. 配置 vim bashrc
#```
#cp ~/github/note/vimrc ~/.vimrc             # 配置 vimrc
#echo ". ~/github/note/bashrc" >> ~/.bashrc  # 配置 bashrc
#. ~/.bashrc                                 # 使 bashrc 生效
#```
#

