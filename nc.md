
## 常用命令
```
nc -lkv 1234                            # 服务端: 监听 1234 端口, 允许多个连接, 显示连接信息
nc      127.0.0.1 1234                  # 客户端
nc -lk            8080 | pv > /dev/null # 测速-服务端, 注意重定向, 否则会受限于终端的写速率
nc      127.0.0.1 8080      < /dev/zero # 测试-客户端
```

## 代理
```
# 1. 测试环境
192.168.198.10 -- 以下简称 host-10 -- centos 7
192.168.198.20 -- 以下简称 host-20 -- centos 7
192.168.198.60 -- 以下简称 host-60 -- ubuntu 22.04

# 2. 在 host-10 上, 开启防火墙端口号并启动服务
sudo firewall-cmd --add-port=8000/tcp;
nc -lkv 8000;

# 3. 在 host-60 上安装 gost
sudo snap install core;
sudo snap install gost;

# 4. 在 host-60 上, 开启防火墙端口号并启动代理服务
sudo firewall-cmd --add-port=8001/tcp;
sudo firewall-cmd --add-port=8002/tcp;
sudo firewall-cmd --add-port=8003/tcp;
sudo firewall-cmd --add-port=8004/tcp;
gost -L :8001 -L admin:123456@:8002 -L https://:8003 -L https://admin:123456@:8004;

# 5. 在 host-20 上测试代理 -- centos
# 5.1 socks5
nc --proxy host-60:8001 --proxy-type socks5                           host-10 8000
nc --proxy host-60:8002 --proxy-type socks5 --proxy-auth admin:123456 host-10 8000

# 5.2 http
nc --proxy host-60:8001 --proxy-type http                           host-10 8000
nc --proxy host-60:8002 --proxy-type http --proxy-auth admin:123456 host-10 8000

# 5.3 https --- 貌似不支持
nc --proxy host-60:8003 --proxy-type http                           host-10 8000
nc --proxy host-60:8004 --proxy-type http --proxy-auth admin:123456 host-10 8000

# 6. 在 host-60 上测试代理 -- ubuntu
# 6.1 socks5
nc -X 5       -x host-60:8001          host-10 8000
nc -X 5       -x host-60:8002 -P admin host-10 8000 --- 貌似不支持

# 6.2 http
nc -X connect -x host-60:8001          host-10 8000
nc -X connect -x host-60:8002 -P admin host-10 8000

# 6.3 https --- 貌似不支持
nc -X connect -x host-60:8003          host-10 8000
nc -X connect -x host-60:8004 -P admin host-10 8000
```

