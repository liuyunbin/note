
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
```

## 3. 安装代理
### 3.1 在 vps 上开启 https 代理
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

### 3.2 在 host-60 上 启动代理
```
sudo snap install core;                            # 1. 安装 gost
sudo snap install gost;
sudo firewall-cmd --add-port=8001-8008/tcp;        # 2. 处理防火墙端口
                                                   # 3. 启动代理, 注意修改域名
gost -L http://:8001 -L http://admin:123456@:8002 -L socks4://:8003 -L socks4a://:8004 -L socks5://:8005 -L socks5://admin:123456@:8006 -F https://admin:123456@yunbinliu.com:8008;
```

## 4. 测试
### 4.1 curl
```
# 1. http 代理
curl -x http://host-60:8001              http://www.google.com;
curl -x http://admin:123456@host-60:8002 http://www.google.com;

curl -x http://host-60:8001              https://www.google.com;
curl -x http://admin:123456@host-60:8002 https://www.google.com;

# 2. socks4 代理 --- 不行, 域名解析在本地
curl -x socks4://host-60:8003  http://www.google.com;
curl -x socks4://host-60:8003 https://www.google.com;

# 3. socks4a 代理
curl -x socks4a://host-60:8004  http://www.google.com;
curl -x socks4a://host-60:8004 https://www.google.com;

# 4. socks5 代理 --- 不行, 域名解析在本地
curl -x socks5://host-60:8005              http://www.google.com;
curl -x socks5://admin:123456@host-60:8006 http://www.google.com;

curl -x socks5://host-60:8005              https://www.google.com;
curl -x socks5://admin:123456@host-60:8006 https://www.google.com;

# 5. socks5h 代理
curl -x socks5h://host-60:8005              http://www.google.com;
curl -x socks5h://admin:123456@host-60:8006 http://www.google.com;

curl -x socks5h://host-60:8005              https://www.google.com;
curl -x socks5h://admin:123456@host-60:8006 https://www.google.com;

# 6. https 代理 --- 貌似不支持
curl -x https://yunbinliu.com:8007              http://www.google.com;
curl -x https://admin:123456@yunbinliu.com:8008 http://www.google.com;

curl -x https://yunbinliu.com:8007              https://www.google.com;
curl -x https://admin:123456@yunbinliu.com:8008 https://www.google.com;
```

### 4.2 wget
```
# 1. http
wget http://www.google.com -e http_proxy=http://host-60:8001
wget http://www.google.com -e http_proxy=http://admin:123456@host-60:8002

wget https://www.google.com -e https_proxy=http://host-60:8001
wget https://www.google.com -e https_proxy=http://admin:123456@host-60:8002

# 2. socks4 代理 --- 不支持
wget  http://www.google.com -e  http_proxy=socks4://host-60:8003
wget https://www.google.com -e https_proxy=socks4://host-60:8003

# 3. socks4a 代理 --- 不支持
wget  http://www.google.com -e  http_proxy=socks4a://host-60:8004
wget https://www.google.com -e https_proxy=socks4a://host-60:8004

# 4. socks5 代理 --- 不支持
wget http://www.google.com -e http_proxy=socks5://host-60:8005
wget http://www.google.com -e http_proxy=socks5://admin:123456@host-60:8006

wget https://www.google.com -e https_proxy=socks5://host-60:8005
wget https://www.google.com -e https_proxy=socks5://admin:123456@host-60:8006

# 5. socks5h 代理 --- 不支持
wget http://www.google.com -e http_proxy=socks5h://host-60:8005
wget http://www.google.com -e http_proxy=socks5h://admin:123456@host-60:8006

wget https://www.google.com -e https_proxy=socks5h://host-60:8005
wget https://www.google.com -e https_proxy=socks5h://admin:123456@host-60:8006

# 6. https 代理 --- 貌似不支持
wget http://www.google.com -e http_proxy=https://yunbinliu.com:8007
wget http://www.google.com -e http_proxy=https://admin:123456@yunbinliu.com:8008

wget https://www.google.com -e https_proxy=https://yunbinliu.com:8007
wget https://www.google.com -e https_proxy=https://admin:123456@yunbinliu.com:8008
```

