## 1. http 访问使用代理
#### 1.1 http 代理
```
git config --global http.proxy http://host-60:8001
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy http://admin:123456@host-60:8002
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

#### 1.2 socks4 代理
```
git config --global http.proxy socks4://host-60:8003
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

#### 1.3 socks4a 代理
```
git config --global http.proxy socks4a://host-60:8004
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

#### 1.4 socks5 代理
```
git config --global http.proxy socks5://host-60:8005
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy socks5://admin:123456@host-60:8006
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

#### 1.5 socks5h 代理
```
git config --global http.proxy socks5h://host-60:8005
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy socks5h://admin:123456@host-60:8006
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

#### 1.6 https 代理 --- 貌似不支持
```
git config --global http.proxy https://yunbinliu.com:8007
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

git config --global http.proxy https://admin:123456@yunbinliu.com:8008
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy
```

## 2. ssh 访问使用代理 --- centos 7
#### 2.1 http 代理
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

#### 2.2 socks4 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks4 --proxy host-60:8003 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

#### 2.3 socks4a 代理 --- 兼容 socks4
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks4 --proxy host-60:8004 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

#### 2.4 socks5 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8006 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

#### 2.5 socks5h 代理 --- 使用的其实是 socks5
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type socks5 --proxy host-60:8006 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

#### 2.6 https --- 貌似不支持
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type http --proxy yunbinliu.com:8007 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc --proxy-type http --proxy yunbinliu.com:8008 --proxy-auth admin:123456 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

## 3. ssh 访问使用代理 --- ubuntu 24.04
#### 3.1 http 代理
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

#### 3.2 socks4 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 4 -x host-60:8003 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

#### 3.3 socks4a 代理 --- 兼容 socks4
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 4 -x host-60:8004 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

#### 3.4 socks5 代理
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8006 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 不支持
```

#### 3.5 socks5h 代理 --- 使用的其实是 socks5
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8005 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X 5 -x host-60:8006 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试 --- 不支持
```

#### 3.6 https --- 貌似不支持
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X connect -x yunbinliu.com:8007 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand nc -X connect -x yunbinliu.com:8008 -P admin %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

## 4. ssh 访问使用代理 --- windows
#### 4.1 http 代理
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

#### 4.2 socks4 代理 --- 有问题
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S host-60:8003 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

#### 4.3 socks4a 代理 --- 有问题
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -S host-60:8004 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

#### 4.4 socks5 代理
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

#### 4.5 socks5h 代理 -- 实际使用的是 socks5
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

# 4.6 https 代理 --- 貌似不支持
```
在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -H yunbinliu.com:8007 %h %p
git clone git@github.com:liuyunbin/note; # 测试

在 ~/.ssh/config 里添加如下配置
    Host github.com
    ProxyCommand connect -H admin@yunbinliu.com:8008 %h %p
git clone git@github.com:liuyunbin/note; # 测试
```

