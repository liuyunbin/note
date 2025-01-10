
## 1. 前置知识
```
# 1. 代理协议
http ------ 有用户认证 --- 远程域名解析
socks4 ---- 无用户认证 --- 本地域名解析
socks4a --- 无用户认证 --- 远程或本地域名解析 --- 兼容 socks4
socks5 ---- 有用户认证 --- 远程或本地域名解析
socks5h --- 有用户认证 --- 远程域名解析 --------- 使用的还是 socks5
https ----- 有用户认证 --- 远程域名解析 --------- 一般命令不支持

# 2. 环境变量
http_proxy ---- HTTP_PROXY ---- http 请求的代理
https_proxy --- HTTPS_PROXY --- https 请求的代理
all_proxy ----- ALL_PROXY ----- http 和 https 请求的代理
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

## 4. 测试
### 4.1 curl
```
            测试: ./test_proxy_curl.sh
      支持的协议: http socks4 socks4a socks5 socks5h https(ubuntu 24.04)
    不支持的协议: https(centos7)
      建议的协议: http   socks5h
    不建议的协议: socks4 socks5
  支持的环境变量: http_proxy https_proxy all_proxy HTTPS_PROXY ALL_PROXY
不支持的环境变量: HTTP_PROXY
```

### 4.2 wget
```
            测试: ./test_proxy_wget.sh
      支持的协议: http
    不支持的协议: socks4 socks4a socks5 socks5h https
      建议的协议: http
    不建议的协议:
  支持的环境变量: http_proxy https_proxy
不支持的环境变量:  all_proxy HTTP_PROXY HTTPS_PROXY ALL_PROXY
```

### 4.3 nc
```
# 1. 在 vps 上 开启服务
nc -lkv 8000;                          # 开启服务

# 2. 测试 centos7
            测试: ./test_proxy_nc_centos.sh
      支持的协议: http socks4 socks4a socks5
    不支持的协议: https
      建议的协议: http   socks5
    不建议的协议: socks4
  支持的环境变量:
不支持的环境变量: http_proxy https_proxy all_proxy HTTP_PROXY HTTPS_PROXY ALL_PROXY

# 3. 测试 ubuntu 24.04
            测试: ./test_proxy_nc_ubuntu.sh
      支持的协议: http(认证时需要输入密码) socks4 socks4a socks5(不支持认证)
    不支持的协议: https
      建议的协议: http   socks5
    不建议的协议: socks4
  支持的环境变量:
不支持的环境变量: http_proxy https_proxy all_proxy HTTP_PROXY HTTPS_PROXY ALL_PROXY
```

### 4.4 git
```
# 1. 测试 http 协议
            测试: ./test_proxy_git_http.sh
      支持的协议: http socks4 socks4a socks5 https
    不支持的协议:
      建议的协议: http   socks5 https
    不建议的协议:
  支持的环境变量: https_proxy
不支持的环境变量: http_proxy all_proxy HTTP_PROXY HTTPS_PROXY ALL_PROXY

# 2. 测试 ssh 协议
# 2.1 测试 centos7
            测试: ./test_proxy_git_http.sh
      支持的协议: http socks4 socks4a socks5
    不支持的协议: https
      建议的协议: http   socks5
    不建议的协议:
  支持的环境变量:
不支持的环境变量: http_proxy https_proxy all_proxy HTTP_PROXY HTTPS_PROXY ALL_PROXY
# 2.2 测试 ubuntu 24.04
# 2.3 测试 windows
```

