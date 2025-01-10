
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

