#!/bin/bash

# bash <(curl -fsSL https://raw.githubusercontent.com/liuyunbin/note/master/vps.sh)

set -ueo pipefail # 使用未初始化的变量, 命令报错, 管道报错, 直接退出

exec &>/dev/null  # 禁止命令输出

function log() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; }

DOMAIN=yunbinliu.com       # 域名
USER=yunbinliu             # 用户名
PASS=lyb2636196546         # 密码
PORT=442                   # gost 端口号
SERVICE=https              # 更新域名使用的服务
MAIL=yunbinliu@outlook.com # 邮箱

log "01. 更新系统"
apt -y update     # 更新软件源
apt -y upgrade    # 更新软件
apt -y autoremove # 卸载没用的软件

log "02. 安装常用软件"
apt -y install certbot cron firewalld g++ vim lrzsz man-db git icdiff

log "03. 安装 docker"
which docker || bash <(curl -fsSL https://get.docker.com)

log "04. 设置开机自动启动"
systemctl enable docker firewalld

log "05. 处理证书"
certbot certificates | grep $DOMAIN || certbot certonly --standalone --agree-tos -n -m $MAIL -d $DOMAIN

log "06. 处理 gost"
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

docker ps --format "{{.Names}}" | grep gost || docker start gost # 启动代理

log "07. 添加定时任务"
cmd="$(which certbot) renew --force-renewal"
crontab -l | grep "$cmd" || echo "0 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

cmd="$(which docker) restart gost"
crontab -l | grep "$cmd" || echo "5 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

log "08. 处理防火墙"
firewall-cmd --permanent --zone=public --add-port=${PORT}/tcp   # 代理
firewall-cmd --permanent --zone=public --add-service=${SERVICE} # 更新证书
firewall-cmd --reload

log "09. 处理 man 文档"
echo y | unminimize

log "10. 处理 git"
git config --global user.name "Yunbin Liu"           # 配置用户名
git config --global user.email yunbinliu@outlook.com # 配置邮箱
git config --global core.editor vim                  # 配置编辑器
git config --global log.date iso                     # 配置日期格式
git config --global alias.co checkout                # 配置简要命令
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status
git config --global alias.lg "log --pretty=format:'%ad %h %s %d %C(bold)%an%Creset' --graph"
                                                     # 配置日志显示格式
git config --global core.quotepath false             # 配置中文显示不乱码
git config --global --list                           # 查看配置
[[ -f ~/.ssh/id_ed25519.pub ]] || ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N "" # 生成秘钥

log "复制公钥到 GitHub, 按回车继续..."
cat ~/.ssh/id_ed25519.pub > /dev/tty
read < /dev/tty

log "测试连接"
ssh -T git@github.com -o BatchMode=yes -o StrictHostKeyChecking=no &> /dev/tty || true

log "11. 处理仓库 note"
mkdir -p ~/github
cd ~/github
[[ -d note ]] || git clone git@github.com:liuyunbin/note

log "12. 配置 vim"
cp ~/github/note/vimrc ~/.vimrc

log "13. 配置 bashrc"
grep github/note/bashrc ~/.bashrc || echo ". ~/github/note/bashrc" >> ~/.bashrc

#log "14. 新建用户"
#useradd -m -s /bin/bash lyb || true # 添加用户
#echo lyb:654321 | chpasswd          # 设置密码
#
#chmod +w /etc/sudoers
#grep lyb /etc/sudoers || echo "lyb ALL=(ALL:ALL) ALL" >> /etc/sudoers # 赋予 sudo 权限
#chmod -w /etc/sudoers
#
#grep lyb /etc/ssh/sshd_config || echo "DenyUsers lyb" >> /etc/ssh/sshd_config # 禁止使用 ssh 登录
#systemctl restart ssh

log "15. 完成"

