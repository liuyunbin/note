
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

## 3. 在 host-20 上测试代理 -- centos
### 3.1 socks5 代理
```
curl -x socks5h://host-60:8001              http://www.google.com;
curl -x socks5h://admin:123456@host-60:8002 http://www.google.com;

curl -x socks5h://host-60:8001              https://www.google.com;
curl -x socks5h://admin:123456@host-60:8002 https://www.google.com;
```

### 3.2 http 代理
```
curl -x http://host-60:8001              http://www.google.com;
curl -x http://admin:123456@host-60:8002 http://www.google.com;

curl -x http://host-60:8001              https://www.google.com;
curl -x http://admin:123456@host-60:8002 https://www.google.com;
```

### 3.3 https --- 貌似不支持
```
curl -x https://host-60:8003              http://www.google.com;
curl -x https://admin:123456@host-60:8003 http://www.google.com;

curl -x https://host-60:8004              https://www.google.com;
curl -x https://admin:123456@host-60:8004 https://www.google.com;
```

## 4. 在 host-60 上测试代理 -- ubuntu
```
结论同上
```

