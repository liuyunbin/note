
## 1. 代理协议
```
http
    * 有用户认证
    * 远程域名解析
socks4
    * 无用户认证
    * 本地域名解析
socks4a
    * 无用户认证
    * 远程或本地域名解析
    * 兼容 socks4
socks5
    * 有用户认证
    * 远程或本地域名解析
socks5h
    * 有用户认证
    * 远程域名解析
    * 使用的还是 socks5 协议
socks
    * 上述四个socks 协议之一
https
    * 有用户认证
    * 远程域名解析
    * 一般命令不支持
```

## 2. 测试环境
```
host-10 ----------- 本地虚拟机 centos 7
host-60 ----------- 本地虚拟机 ubuntu 22.04
yunbinliu.com ----- 远程机器 VPS
windows ----------- windows 10
```

## 3. 设置代理
#### 3.1 在 vps 上启动 https 代理
```
sudo apt install -y certbot;                           # 1. 安装证书, 注意修改域名
certbot certonly --standalone -d yunbinliu.com;        #
curl -fsSL https://test.docker.com -o test-docker.sh   # 2. 安装 docker
sudo sh test-docker.sh;                                #
rm test-docker.sh;                                     #
sudo firewall-cmd --add-port=8007-8008/tcp;            # 3. 处理防火墙端口
DOMAIN=yunbinliu.com                                   # 4. 启动代理, 注意修改域名
CERT_DIR=/etc/letsencrypt
CERT=${CERT_DIR}/live/${DOMAIN}/fullchain.pem
KEY=${CERT_DIR}/live/${DOMAIN}/privkey.pem
docker run -d --name test -v ${CERT_DIR}:${CERT_DIR}:ro --net=host ginuerzh/gost -L "https://:8007?cert=${CERT}&key=${KEY}" -L "https://admin:123456@:8008?cert=${CERT}&key=${KEY}"
```

#### 3.2 在 host-60 上 启动代理
```
sudo snap install core;                            # 1. 安装 gost
sudo snap install gost;
sudo firewall-cmd --add-port=8001-8008/tcp;        # 2. 处理防火墙端口
                                                   # 3. 启动代理, 注意修改域名
gost -L http://:8001 -L http://admin:123456@:8002 -L socks4://:8003 -L socks4a://:8004 -L socks5://:8005 -L socks5://admin:123456@:8006 -F https://admin:123456@yunbinliu.com:8008;
```

