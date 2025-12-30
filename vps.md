
## 安装 vps 后要处理的事情
### 1. 更新操作系统
```
apt -y update     # 更新软件源
apt -y upgrade    # 更新软件
apt -y autoremove # 卸载没用的软件
```

### 2. 申请证书
```
apt -y install certbot                                                                 # 安装软件
certbot certonly --standalone --agree-tos -n -m yunbinliu@outlook.com -d yunbinliu.com # 申请证书
```

### 3. 处理 gost
```
DOMAIN=yunbinliu.com                          # 域名
USER=yunbinliu                                # 用户名
PASS=lyb2636196546                            # 密码
PORT=442                                      # 端口号

BIND_IP=0.0.0.0                               # 绑定的IP
CERT_DIR=/etc/letsencrypt                     # 证书的目录
CERT=${CERT_DIR}/live/${DOMAIN}/fullchain.pem # 证书的公钥
KEY=${CERT_DIR}/live/${DOMAIN}/privkey.pem    # 证书的私钥

bash <(curl -fsSL https://get.docker.com)     # 安装 docker
systemctl enable docker                       # 开机自动启动
docker run -d --name gost -v ${CERT_DIR}:${CERT_DIR}:ro --net=host ginuerzh/gost -L "http2://${USER}:${PASS}@${BIND_IP}:${PORT}?cert=${CERT}&key=${KEY}&probe_resist=code:400&knock=www.google.com"
                                              # 配置代理
docker start gost                             # 启动代理
```

### 4. 处理防火墙
```
apt -y install firewalld                                  # 安装防火墙
systemctl enable firewalld                                # 开机自动启动
firewall-cmd --permanent --zone=public --add-port=442/tcp # 开启代理的端口号
firewall-cmd --permanent --zone=public --add-service=http # 更新证书需要
firewall-cmd --reload                                     # 重新加载防火墙
```

### 5. 自动更新证书
```
apt -y install cron                                                                      # 安装软件
echo "0 0 1 * * $(which certbot) renew --force-renewal" >> /var/spool/cron/crontabs/root # 更新证书
echo "5 0 1 * * $(which docker) restart gost" >> /var/spool/cron/crontabs/root           # 重启 gost
```

### 6. 配置 git
```
apt -y install git icdiff vim                        # 0. 安装软件
git config --global user.name "Yunbin Liu"           # 1. 配置用户名
git config --global user.email yunbinliu@outlook.com # 2. 配置邮箱
git config --global core.editor vim                  # 3. 配置编辑器
git config --global log.date iso                     # 4. 配置日期格式
git config --global alias.co checkout                # 5. 配置简要命令
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status
git config --global alias.lg "log --pretty=format:'%ad %h %s %d %C(bold)%an%Creset' --graph"
git config --global core.quotepath false             # 6. 中文显示不乱码
git config --global --list                           # 7. 查看配置
ssh-keygen -t ed25519 -f ~/.ssh/id_ed25519 -N ""     # 8. 生成秘钥
                                                     # 9. 复制公钥到 GitHub
ssh -T git@github.com -o BatchMode=yes -o StrictHostKeyChecking=no
                                                     # 10. 测试连接
```

### 7. 初始化 note
```
mkdir -p ~/github
cd ~/github
git clone git@github.com:liuyunbin/note
```

### 8. 配置 vim bashrc
```
cp ~/github/note/vimrc ~/.vimrc             # 配置 vimrc
echo ". ~/github/note/bashrc" >> ~/.bashrc  # 配置 bashrc
. ~/.bashrc                                 # 使 bashrc 生效
```

### 9. 安装 man 文档
```
apt -y install man-db # 安装 man-db
yes | unminimize      # 解压 man-db
```

### 10. 安装其他常用命令
```
apt -y install g++
```

