
## 1. 测试环境
```
host-10 ----------- 本地虚拟机 centos 7
host-60 ----------- 本地虚拟机 ubuntu 22.04
yunbinliu.com ----- 远程机器 VPS
windows ----------- windows 10
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

## 4. http 访问使用代理
### 4.1 http 代理 --- 建议
```
git config --global http.proxy http://host-60:8001
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy http://admin:123456@host-60:8001
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

### 4.2 socks4 代理 --- 域名解析在本地 --- 不建议使用
```
git config --global http.proxy socks4://host-60:8003
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy socks4://admin:123456@host-60:8004
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

### 4.3 socks4a 代理 --- 建议
```
git config --global http.proxy socks4a://host-60:8005
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy socks4a://admin:123456@host-60:8006
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

### 4.4 socks5 代理 --- 域名解析在本地 --- 不建议使用
```
git config --global http.proxy socks5://host-60:8007
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy socks5://admin:123456@host-60:8008
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```
### 4.5 socks5h 代理 --- 建议
```
git config --global http.proxy socks5h://host-60:8007
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy socks5h://admin:123456@host-60:8008
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

### 4.6 https 代理 --- 貌似不支持
```
git config --global http.proxy https://yunbinliu.com:8009
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy https://admin:123456@yunbinliu.com:8010
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

## 5. ssh 访问使用代理 --- centos 7
### 5.1 http 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type http --proxy host-60:8001 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type http --proxy host-60:8002 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

### 5.2 socks4 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks4 --proxy host-60:8003 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks4 --proxy host-60:8004 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

### 5.3 socks4a 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks4 --proxy host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks4 --proxy host-60:8006 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

### 5.4 socks5 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8007 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8008 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

### 5.5 socks5h 代理 --- 使用的其实是 socks5
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8007 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8008 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

### 5.6 https --- 貌似不支持
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type http --proxy yunbinliu.com:8009 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type http --proxy yunbinliu.com:8010 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

## 6. ssh 访问使用代理 --- ubuntu 24.04
### 6.1 http 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X connect -x host-60:8001 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X connect -x host-60:8002 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 输入代理密码
```

### 6.2 socks4 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 4 -x host-60:8003 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 4 -x host-60:8004 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 不需要密码
```

### 6.3 socks4a 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 4 -x host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 4 -x host-60:8006 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 不需要密码
```

### 6.4 socks5 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8007 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8008 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 不支持
```

### 6.5 socks5h 代理 --- 使用的其实是 socks5
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8007 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8008 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 不支持
```

### 6.6 https --- 貌似不支持
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X connect -x yunbinliu.com:8009 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X connect -x yunbinliu.com:8010 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

## 7. ssh 访问使用代理 --- windows
### 7.1 http 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -H host-60:8001 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -H admin@host-60:8002 %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 貌似有问题
```

### 7.2 socks4 代理 --- 有问题
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S host-60:8003 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S admin@host-60:8004 %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 貌似有问题
```

### 7.3 socks4a 代理 --- 有问题
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S admin@host-60:8006 %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 貌似有问题
```

### 7.4 socks5 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S host-60:8001 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S admin@host-60:8002 %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 貌似有问题
```

### 7.5 socks5a 代理 -- 实际使用的是 socks5
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S host-60:8001 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S admin@host-60:8002 %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 貌似有问题
```

### 7.6 https 代理 --- 貌似不支持
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -H yunbinliu.com:8009 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -H admin@yunbinliu.com:8010 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

