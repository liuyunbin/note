
## 1. 在 vps 上 开启服务
```
sudo firewall-cmd --add-port=8000/tcp; # 添加防火墙端口号
nc -lkv 8000;                          # 开启服务
```

## 2. 在 host-10 上测试代理 -- centos
#### 2.1 http 代理
```
nc --proxy host-60:8001 --proxy-type http                           yunbinliu.com 8000;
nc --proxy host-60:8002 --proxy-type http --proxy-auth admin:123456 yunbinliu.com 8000;
```

#### 2.2 socks4 代理
```
nc --proxy host-60:8003 --proxy-type socks4                           yunbinliu.com 8000;
```

#### 2.3 socks4a 代理 --- 兼容 socks4
```
nc --proxy host-60:8004 --proxy-type socks4                           yunbinliu.com 8000;
```

#### 2.4 socks5 代理
```
nc --proxy host-60:8005 --proxy-type socks5                           yunbinliu.com 8000;
nc --proxy host-60:8006 --proxy-type socks5 --proxy-auth admin:123456 yunbinliu.com 8000;
```

#### 2.5 socks5h 代理 --- 使用的还是 socks5
```
nc --proxy host-60:8005 --proxy-type socks5                           yunbinliu.com 8000;
nc --proxy host-60:8006 --proxy-type socks5 --proxy-auth admin:123456 yunbinliu.com 8000;
```

#### 2.6 https 代理 --- 貌似不支持
```
nc --proxy yunbinliu.com:8007 --proxy-type http                           yunbinliu.com 8000;
nc --proxy yunbinliu.com:8008 --proxy-type http --proxy-auth admin:123456 yunbinliu.com 8000;
```

## 3. 在 host-60 上测试代理 -- ubuntu
#### 3.1 http 代理
```
nc -X connect -x host-60:8001          yunbinliu.com 8000;
nc -X connect -x host-60:8002 -P admin yunbinliu.com 8000; --- 需要输入密码
```

#### 3.2 socks4 代理
```
nc -X 4       -x host-60:8003          yunbinliu.com 8000;
```

#### 3.3 socks4a 代理 --- 兼容 socks4
```
nc -X 4       -x host-60:8004          yunbinliu.com 8000;
```

#### 3.4 socks5 代理
```
nc -X 5       -x host-60:8005          yunbinliu.com 8000;
nc -X 5       -x host-60:8006 -P admin yunbinliu.com 8000; --- 貌似不支持
```

#### 3.5 socks5h 代理 --- 使用的还是 socks5
```
nc -X 5       -x host-60:8005          yunbinliu.com 8000;
nc -X 5       -x host-60:8006 -P admin yunbinliu.com 8000; --- 貌似不支持
```

#### 3.6 https 代理 --- 貌似不支持
```
nc -X connect -x yunbinliu.com:8009          yunbinliu.com 8000;
nc -X connect -x yunbinliu.com:8010 -P admin yunbinliu.com 8000;
```

