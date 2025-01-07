
## 1. 测试环境
```
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

## 4. 测试
### 4.1 临时使用
#### 4.1.1 http 代理
```
sudo rm -r /var/lib/apt/lists/*                                # 清空缓存
sudo apt update -o Acquire::http::Proxy="http://host-60:8001"; # 测试

sudo rm -r /var/lib/apt/lists/*                                             # 清空缓存
sudo apt update -o Acquire::http::Proxy="http://admin:123456@host-60:8002"; # 测试
```

#### 4.1.2 socks4 代理
```
sudo rm -r /var/lib/apt/lists/*                                  # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks4://host-60:8001"; # 测试

sudo rm -r /var/lib/apt/lists/*                                               # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks4://admin:123456@host-60:8002"; # 测试
```

#### 4.1.1 socks5h
```
sudo apt clean;                                                   # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5h://host-60:8001"; # 测试

sudo apt clean;                                                                # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5h://admin:123456@host-60:8002"; # 测试
```


#### 3.1.3 https --- 不建议, 证书检验可能失败
```
sudo apt clean;                                                 # 清空缓存
sudo apt update -o Acquire::http::Proxy="https://host-60:8003"; # 测试

sudo apt clean;                                                              # 清空缓存
sudo apt update -o Acquire::http::Proxy="https://admin:123456@host-60:8004"; # 测试
```

### 3.2 永久使用
#### 3.2.1 socks5h
```
sudo apt clean;  # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "socks5h://host-60:8001";
    Acquire::https::Proxy "socks5h://host-60:8001";
sudo apt update; # 测试

sudo apt clean;  # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "socks5h://admin:123456@host-60:8002";
    Acquire::https::Proxy "socks5h://admin:123456@host-60:8002";
sudo apt update; # 测试
```

#### 3.2.2 http
```
sudo apt clean;  # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "http://host-60:8001";
    Acquire::https::Proxy "http://host-60:8001";
sudo apt update; # 测试

sudo apt clean;  # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "http://admin:123456@host-60:8002";
    Acquire::https::Proxy "http://admin:123456@host-60:8002";
sudo apt update; # 测试
```

#### 3.2.3 https --- 不建议, 证书检验可能失败
```
sudo apt clean;  # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "https://host-60:8003";
    Acquire::https::Proxy "https://host-60:8003";
sudo apt update; # 测试

sudo apt clean;  # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "https://admin:123456@host-60:8004";
    Acquire::https::Proxy "https://admin:123456@host-60:8004";
sudo apt update; # 测试
```


## 4. 在 host-10 上测试代理 -- centos
### 4.1 http 代理
```
curl -x http://host-60:8001              http://www.google.com;
curl -x http://admin:123456@host-60:8002 http://www.google.com;

curl -x http://host-60:8001              https://www.google.com;
curl -x http://admin:123456@host-60:8002 https://www.google.com;
```

### 4.2 socks4 代理 --- 不行, 域名解析在本地
```
curl -x socks4://host-60:8003              http://www.google.com;
curl -x socks4://admin:123456@host-60:8004 http://www.google.com;

curl -x socks4://host-60:8003              https://www.google.com;
curl -x socks4://admin:123456@host-60:8004 https://www.google.com;
```

### 4.3 socks4a 代理
```
curl -x socks4a://host-60:8005              http://www.google.com;
curl -x socks4a://admin:123456@host-60:8006 http://www.google.com;

curl -x socks4a://host-60:8005              https://www.google.com;
curl -x socks4a://admin:123456@host-60:8006 https://www.google.com;
```

### 4.4 socks5 代理 --- 不行, 域名解析在本地
```
curl -x socks5://host-60:8007              http://www.google.com;
curl -x socks5://admin:123456@host-60:8008 http://www.google.com;

curl -x socks5://host-60:8007              https://www.google.com;
curl -x socks5://admin:123456@host-60:8008 https://www.google.com;
```

### 4.5 socks5h 代理
```
curl -x socks5h://host-60:8007              http://www.google.com;
curl -x socks5h://admin:123456@host-60:8008 http://www.google.com;

curl -x socks5h://host-60:8007              https://www.google.com;
curl -x socks5h://admin:123456@host-60:8008 https://www.google.com;
```

### 4.6 https 代理 --- 貌似不支持
```
curl -x https://yunbinliu.com:8009              http://www.google.com;
curl -x https://admin:123456@yunbinliu.com:8010 http://www.google.com;

curl -x https://yunbinliu.com:8009              https://www.google.com;
curl -x https://admin:123456@yunbinliu.com:8010 https://www.google.com;
```

## 5. 在 host-60 上测试代理 -- ubuntu
```
结论同上
```

