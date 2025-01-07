
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
* [git](./git.md)
* [apt](./apt.md)




yum clean all            # 清空软件源缓存
yum makecache            # 新建软件源缓存
