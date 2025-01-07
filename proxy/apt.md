## 1. 临时使用
#### 1.1 http 代理
```
sudo rm -r /var/lib/apt/lists/*                                # 清空缓存
sudo apt update -o Acquire::http::Proxy="http://host-60:8001"; # 测试

sudo rm -r /var/lib/apt/lists/*                                             # 清空缓存
sudo apt update -o Acquire::http::Proxy="http://admin:123456@host-60:8002"; # 测试
```

#### 1.2 socks4 代理 --- 不支持
```
sudo rm -r /var/lib/apt/lists/*                                  # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks4://host-60:8003"; # 测试
```

#### 1.3 socks4a 代理 --- 不支持
```
sudo rm -r /var/lib/apt/lists/*                                  # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks4a://host-60:8004"; # 测试
```

#### 1.4 socks5 代理 --- 不支持
```
sudo rm -r /var/lib/apt/lists/*                                  # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5://host-60:8005"; # 测试

sudo rm -r /var/lib/apt/lists/*                                               # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5://admin:123456@host-60:8006"; # 测试
```

#### 1.5 socks5h 代理
```
sudo rm -r /var/lib/apt/lists/*                                   # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5h://host-60:8005"; # 测试

sudo rm -r /var/lib/apt/lists/*                                                # 清空缓存
sudo apt update -o Acquire::http::Proxy="socks5h://admin:123456@host-60:8006"; # 测试
```

#### 1.6 https 代理
```
sudo rm -r /var/lib/apt/lists/*                                       # 清空缓存
sudo apt update -o Acquire::http::Proxy="https://yunbinliu.com:8007"; # 测试

sudo rm -r /var/lib/apt/lists/*                                                    # 清空缓存
sudo apt update -o Acquire::http::Proxy="https://admin:123456@yunbinliu.com:8008"; # 测试
```

## 2. 永久使用
#### 2.1 http 代理
```
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
```

#### 2.2 socks4 代理 --- 不支持
```
sudo rm -r /var/lib/apt/lists/* # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "socks4://host-60:8003";
    Acquire::https::Proxy "socks4://host-60:8003";
sudo apt update; # 测试
```

#### 2.3 socks4a 代理 --- 不支持
```
sudo rm -r /var/lib/apt/lists/* # 清空缓存
/etc/apt/apt.conf.d/proxy.conf 内添加
    Acquire::http::Proxy  "socks4a://host-60:8004";
    Acquire::https::Proxy "socks4a://host-60:8004";
sudo apt update; # 测试
```

#### 2.4 socks5 代理 --- 不支持
```
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
```

#### 2.5 socks5h 代理
```
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
```

#### 2.6 https 代理
```
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

