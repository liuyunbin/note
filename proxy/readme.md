
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
* [设置代理](./set_proxy.md)

## 4. 测试
* [curl](./curl.md)
* [wget](./wget.md)
* [nc](./nc.md)

### 4.4 git
```
# 1. http 访问使用代理
# 1.1 http 代理
git config --global http.proxy http://host-60:8001
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy http://admin:123456@host-60:8002
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

# 1.2 socks4 代理
git config --global http.proxy socks4://host-60:8003
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

# 1.3 socks4a 代理
git config --global http.proxy socks4a://host-60:8004
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

# 1.4 socks5 代理
git config --global http.proxy socks5://host-60:8005
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy socks5://admin:123456@host-60:8006
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

# 1.5 socks5h 代理
git config --global http.proxy socks5h://host-60:8005
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy socks5h://admin:123456@host-60:8006
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

# 1.6 https 代理 --- 貌似不支持
git config --global http.proxy https://yunbinliu.com:8007
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy https://admin:123456@yunbinliu.com:8008
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

# 2. ssh 访问使用代理 --- centos 7
# 2.1 http 代理
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type http --proxy host-60:8001 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type http --proxy host-60:8002 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 2.2 socks4 代理
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks4 --proxy host-60:8003 %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 2.3 socks4a 代理 --- 兼容 socks4
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks4 --proxy host-60:8004 %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 2.4 socks5 代理
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8006 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 2.5 socks5h 代理 --- 使用的其实是 socks5
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8006 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 2.6 https --- 貌似不支持
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type http --proxy yunbinliu.com:8007 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type http --proxy yunbinliu.com:8008 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 3. ssh 访问使用代理 --- ubuntu 24.04
# 3.1 http 代理
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X connect -x host-60:8001 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X connect -x host-60:8002 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 输入代理密码

# 3.2 socks4 代理
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 4 -x host-60:8003 %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 3.3 socks4a 代理 --- 兼容 socks4
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 4 -x host-60:8004 %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 3.4 socks5 代理
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8006 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 不支持

# 3.5 socks5h 代理 --- 使用的其实是 socks5
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8006 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 不支持

# 3.6 https --- 貌似不支持
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X connect -x yunbinliu.com:8007 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X connect -x yunbinliu.com:8008 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 4. ssh 访问使用代理 --- windows
# 4.1 http 代理
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -H host-60:8001 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -H admin@host-60:8002 %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 貌似有问题

# 4.2 socks4 代理 --- 有问题
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S host-60:8003 %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 4.3 socks4a 代理 --- 有问题
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S host-60:8004 %h %p
git clone git@github.com:liuyunbin/note; # 测试

# 4.4 socks5 代理
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S admin@host-60:8006 %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 貌似有问题

# 4.5 socks5h 代理 -- 实际使用的是 socks5
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S admin@host-60:8006 %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 貌似有问题

# 4.6 https 代理 --- 貌似不支持
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -H yunbinliu.com:8007 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -H admin@yunbinliu.com:8008 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

### 4.5 apt
```
# 1. 临时使用
# 1.1 http 代理
sudo rm -r /var/lib/apt/lists/*                                # 清空缓存
sudo apt update -o Acquire::http::Proxy="http://host-60:8001"; # 测试

sudo rm -r /var/lib/apt/lists/*                                             # 清空缓存
sudo apt update -o Acquire::http::Proxy="http://admin:123456@host-60:8002"; # 测试

# 1.2 socks4 代理 --- 不支持
sudo rm -r /var/lib/apt/lists/*                                  # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks4://host-60:8003"; # 测试

# 1.3 socks4a 代理 --- 不支持
sudo rm -r /var/lib/apt/lists/*                                  # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks4a://host-60:8004"; # 测试

# 1.4 socks5 代理 --- 不支持
sudo rm -r /var/lib/apt/lists/*                                  # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5://host-60:8005"; # 测试

sudo rm -r /var/lib/apt/lists/*                                               # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5://admin:123456@host-60:8006"; # 测试

# 1.5 socks5h 代理
sudo rm -r /var/lib/apt/lists/*                                   # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5h://host-60:8005"; # 测试

sudo rm -r /var/lib/apt/lists/*                                                # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5h://admin:123456@host-60:8006"; # 测试

# 1.6 https 代理
sudo rm -r /var/lib/apt/lists/*                                       # 清空缓存
sudo apt update -o Acquire::http::Proxy="https://yunbinliu.com:8007"; # 测试

sudo rm -r /var/lib/apt/lists/*                                                    # 清空缓存
sudo apt update -o Acquire::http::Proxy="https://admin:123456@yunbinliu.com:8008"; # 测试

# 2. 永久使用
# 2.1 http 代理
sudo rm -r /var/lib/apt/lists/*  # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "http://host-60:8001";
    Acquire::https::Proxy "http://host-60:8001";
sudo apt update; # 测试

sudo rm -r /var/lib/apt/lists/*  # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "http://admin:123456@host-60:8002";
    Acquire::https::Proxy "http://admin:123456@host-60:8002";
sudo apt update; # 测试

# 2.2 socks4 代理 --- 不支持
sudo rm -r /var/lib/apt/lists/* # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "socks4://host-60:8003";
    Acquire::https::Proxy "socks4://host-60:8003";
sudo apt update; # 测试

# 2.3 socks4a 代理 --- 不支持
sudo rm -r /var/lib/apt/lists/* # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "socks4a://host-60:8004";
    Acquire::https::Proxy "socks4a://host-60:8004";
sudo apt update; # 测试

# 2.4 socks5 代理 --- 不支持
sudo rm -r /var/lib/apt/lists/* # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "socks5://host-60:8005";
    Acquire::https::Proxy "socks5://host-60:8005";
sudo apt update; # 测试

sudo rm -r /var/lib/apt/lists/* # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "socks5://admin:123456@host-60:8006";
    Acquire::https::Proxy "socks5://admin:123456@host-60:8006";
sudo apt update; # 测试

# 2.5 socks5h 代理
sudo rm -r /var/lib/apt/lists/*  # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "socks5h://host-60:8005";
    Acquire::https::Proxy "socks5h://host-60:8005";
sudo apt update; # 测试

sudo rm -r /var/lib/apt/lists/* # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "socks5h://admin:123456@host-60:8006";
    Acquire::https::Proxy "socks5h://admin:123456@host-60:8006";
sudo apt update; # 测试

# 2.6 https 代理
sudo rm -r /var/lib/apt/lists/* # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "https://yunbinliu.com:8007";
    Acquire::https::Proxy "https://yunbinliu.com:8007";
sudo apt update; # 测试

sudo rm -r /var/lib/apt/lists/* # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "https://admin:123456@yunbinliu.com:8008";
    Acquire::https::Proxy "https://admin:123456@yunbinliu.com:8008";
sudo apt update; # 测试
```





yum clean all            # 清空软件源缓存
yum makecache            # 新建软件源缓存
