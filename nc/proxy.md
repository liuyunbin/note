
## 1. 测试环境
```
host-10 ----------- 本地虚拟机 centos 7
host-60 ----------- 本地虚拟机 ubuntu 22.04
yunbinliu.com ----- 远程机器 VPS
```

## 2. 在 vps 上开启 https 代理
```
sudo apt install -y certbot;                           # 1. 安装证书, 注意修改域名
certbot certonly --standalone -d yunbinliu.com;        #
curl -fsSL https://test.docker.com -o test-docker.sh   # 2. 安装 docker
sudo sh test-docker.sh;                                #
rm test-docker.sh;                                     #
sudo firewall-cmd --add-port=8009-8010/tcp;            # 3. 处理防火墙端口
DOMAIN=yunbinliu.com                                   # 4. 启动代理, 注意修改域名
CERT_DIR=/etc/letsencrypt
CERT=${CERT_DIR}/live/${DOMAIN}/fullchain.pem
KEY=${CERT_DIR}/live/${DOMAIN}/privkey.pem
docker run -d --name test -v ${CERT_DIR}:${CERT_DIR}:ro --net=host ginuerzh/gost -L "https://:8009?cert=${CERT}&key=${KEY}" -L "https://admin:1234563@:8010?cert=${CERT}&key=${KEY}"
```

## 3. 在 host-60 上 启动代理
```
sudo snap install core;                            # 1. 安装 gost
sudo snap install gost;
sudo firewall-cmd --add-port=8001-8008/tcp;        # 2. 处理防火墙端口
                                                   # 3. 启动代理, 注意修改域名
gost -L http://:8001 -L http://admin:123456@:8002 -L socks4://:8003 -L socks4://admin:123456@:8004 -L socks4a://:8005 -L socks4a://admin:123456@:8006 -L socks5://:8007 -L socks5://admin:123456@:8008 -F https://admin:123456@yunbinliu.com:8010;
```

## 4. 在 vps 上 开启服务
```
sudo firewall-cmd --add-port=8000/tcp; # 添加防火墙端口号
nc -lkv 8000;                          # 开启服务
```

## 5. 在 host-10 上测试代理 -- centos
### 5.1 http 代理
```
nc --proxy host-60:8001 --proxy-type http                           yunbinliu.com 8000;
nc --proxy host-60:8002 --proxy-type http --proxy-auth admin:123456 yunbinliu.com 8000;
```

### 5.2 socks4 代理
```
nc --proxy host-60:8003 --proxy-type socks4                           yunbinliu.com 8000;
nc --proxy host-60:8004 --proxy-type socks4 --proxy-auth admin:123456 yunbinliu.com 8000;
```

### 5.3 socks4a 代理
```
nc --proxy host-60:8005 --proxy-type socks4                           yunbinliu.com 8000;
nc --proxy host-60:8006 --proxy-type socks4 --proxy-auth admin:123456 yunbinliu.com 8000;
```

### 5.4 socks5 代理
```
nc --proxy host-60:8007 --proxy-type socks5                           yunbinliu.com 8000;
nc --proxy host-60:8008 --proxy-type socks5 --proxy-auth admin:123456 yunbinliu.com 8000;
```

### 5.5 https 代理 --- 貌似不支持
```
nc --proxy yunbinliu.com:8009 --proxy-type http                           yunbinliu.com 8000;
nc --proxy yunbinliu.com:8010 --proxy-type http --proxy-auth admin:123456 yunbinliu.com 8000;
```

## 6. 在 host-60 上测试代理 -- ubuntu
### 6.1 http 代理
```
nc -X connect -x host-60:8001          yunbinliu.com 8000;
nc -X connect -x host-60:8002 -P admin yunbinliu.com 8000; --- 需要输入密码
```

### 6.2 socks4 代理
```
nc -X 4       -x host-60:8003          yunbinliu.com 8000;
nc -X 4       -x host-60:8004 -P admin yunbinliu.com 8000; --- 貌似不需要输入密码
```

### 6.3 socks4a 代理
```
nc -X 4       -x host-60:8005          yunbinliu.com 8000;
nc -X 4       -x host-60:8006 -P admin yunbinliu.com 8000; --- 貌似不需要输入密码
```

### 6.4 socks5 代理
```
nc -X 5       -x host-60:8007          yunbinliu.com 8000;
nc -X 5       -x host-60:8008 -P admin yunbinliu.com 8000; --- 貌似不支持
```

### 6.5 https 代理 --- 貌似不支持
```
nc -X connect -x yunbinliu.com:8009          yunbinliu.com 8000;
nc -X connect -x yunbinliu.com:8010 -P admin yunbinliu.com 8000;
```

