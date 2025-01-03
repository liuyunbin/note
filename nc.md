
## 常用命令
```
nc -lkv 1234                            # 服务端端: 监听 1234 端口, 允许多个连接, 显示连接信息
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
sudo firewall-cmd --add-port=1234/tcp;
nc -lkv 1234;

# 3. 在 host-60 上安装 gost
sudo snap install core;
sudo snap install gost;

# 4. 在 host-60 上, 开启防火墙端口号并启动代理服务
sudo firewall-cmd --add-port=4567/tcp;
sudo firewall-cmd --add-port=7890/tcp;
gost -L :4567 -L admin:123456@:7890;

# 5. 在 host-20 上测试代理 -- centos
nc --proxy host-60:4567 --proxy-type socks5 host-10 1234 # socks5 + 无认证
nc --proxy host-60:4567 --proxy-type http   host-10 1234 # http   + 无认证

nc --proxy host-60:4567 --proxy-type socks5 --proxy-auth admin:123456 host-10 1234 # socks5 + 认证
nc --proxy host-60:4567 --proxy-type http   --proxy-auth admin:123456 host-10 1234 # http   + 认证

# 6. 在 host-60 上测试代理 -- ubuntu
nc -X 5        -x host-60:4567  host-10 1234 # socks5 + 无认证
nc -X connect  -x host-60:4567  host-10 1234 # http   + 无认证

nc -X 5        -x host-60:7890 -P admin host-10 1234 # socks5 + 认证 -- 不支持
nc -X connect  -x host-60:7890 -P admin host-10 1234 # http   + 认证

# 7. 貌似不支持 https 代理 -- TODO

```

