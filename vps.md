
## 安装 vps 后要处理的事情
### 1. 更新操作系统
```
apt -y update     # 更新软件源
apt -y upgrade    # 更新软件
apt -y autoremove # 卸载没用的软件
```

### 2. 设置变量
```
DOMAIN=yunbinliu.com
EMAIL=yunbinliu@outlook.com
USER=yunbinliu
PASS=lyb2636196546
PORT=442
```

### 3. 申请证书
```
apt -y install certbot                                            # 安装软件
certbot certonly --standalone --agree-tos -n -m $EMAIL -d $DOMAIN # 申请证书
```

### 4. 处理 gost
```
bash <(curl -fsSL https://get.docker.com) # 安装 docker
systemctl enable docker                   # 开机自动启动

BIND_IP=0.0.0.0
CERT_DIR=/etc/letsencrypt
CERT=${CERT_DIR}/live/${DOMAIN}/fullchain.pem
KEY=${CERT_DIR}/live/${DOMAIN}/privkey.pem

docker run -d \
    --name gost \
    -v ${CERT_DIR}:${CERT_DIR}:ro \
    --net=host \
    ginuerzh/gost -L "http2://${USER}:${PASS}@${BIND_IP}:${PORT}?cert=${CERT}&key=${KEY}&probe_resist=code:400&knock=www.google.com"

docker start gost # 启动 gost
```






### 2. 设置
#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

log_info "0. 安装软件"
sudo apt -y -qq install git icdiff &> /dev/null

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





log_info "4. 处理防火墙..."
apt -y -qq install firewalld &> /dev/null
systemctl enable firewalld -q
firewall-cmd -q --permanent --zone=public --add-port=$PORT/tcp
firewall-cmd -q --permanent --zone=public --add-service=http    # 更新证书需要
firewall-cmd -q --reload

log_info "5. 添加定时任务..."
apt -y -qq install cron &> /dev/null

cmd="$(which certbot) renew --force-renewal"
crontab -l | grep -q "$cmd" || echo "0 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

cmd="$(which docker) restart gost"
crontab -l | grep -q "$cmd" || echo "5 0 1 * * $cmd" >> /var/spool/cron/crontabs/root

log_info "6. 完成"

