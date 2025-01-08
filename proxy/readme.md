
## 1. 代理协议
```
http ------ 有用户认证 --- 远程域名解析
socks4 ---- 无用户认证 --- 本地域名解析
socks4a --- 无用户认证 --- 远程或本地域名解析 --- 兼容 socks4
socks5 ---- 有用户认证 --- 远程或本地域名解析
socks5h --- 有用户认证 --- 远程域名解析 --- 使用的还是 socks5
https ----- 有用户认证 --- 远程域名解析 --- 一般命令不支持
```

## 2. 测试环境
```
host-10 ----------- 本地虚拟机 centos 7
host-60 ----------- 本地虚拟机 ubuntu 22.04
yunbinliu.com ----- 远程机器 VPS
windows ----------- windows 10
```

## 3. 设置代理
```
./set_proxy_vps.sh  # 在 vps     上启动代理
./set_proxy_host.sh # 在 host-60 上启动代理
```

