
## 1. 测试环境
```
192.168.198.20 -- 以下简称 host-20 -- centos 7
192.168.198.60 -- 以下简称 host-60 -- ubuntu 22.04
```

## 2. 在 host-60 上 启动代理
```
sudo snap install core;                            # 安装 gost
sudo snap install gost;
sudo firewall-cmd --list-all;                      # 查看开启的服务
sudo firewall-cmd --permanent --add-port=8001/tcp; # 添加防火墙端口号
sudo firewall-cmd --permanent --add-port=8002/tcp;
sudo firewall-cmd --permanent --add-port=8003/tcp;
sudo firewall-cmd --permanent --add-port=8004/tcp;
sudo firewall-cmd --reload;                        # 重新加载防火墙
sudo firewall-cmd --list-all;                      # 再次查看开启的服务
gost -L :8001 -L admin:123456@:8002 -L https://:8003 -L https://admin:123456@:8004 -F https://yunbinliu:lyb2636196546@yunbinliu.com:443;
                                                   # 启动代理
```

## 3. 测试
### 3.1 临时使用
#### 3.1.1 socks5h
```
sudo apt clean;                                                   # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5h://host-60:8001"; # 测试

sudo apt clean;                                                                # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5h://admin:123456@host-60:8002"; # 测试
```

#### 3.1.2 http
```
sudo apt clean;                                                # 清空缓存
sudo apt update -o Acquire::http::Proxy="http://host-60:8001"; # 测试

sudo apt clean;                                                             # 清空缓存
sudo apt update -o Acquire::http::Proxy="http://admin:123456@host-60:8002"; # 测试
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

