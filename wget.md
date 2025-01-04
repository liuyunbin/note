
## wget
```
wget www.google.com
wget www.google.com -O 1.html                 # 指定目标文件名称
wget www.google.com -o 1.log                  # 指定日志文件
wget www.google.com -c                        # 断点续传
wget www.google.com -t 3                      # 指定重试的次数, 0 不停的尝试
wget www.google.com --limit-rate 10k          # 限速
wget www.google.com --quota 100M              # 限制最大下载量
wget www.google.com --mirror --convert-links  # 镜像下载, 递归, 并转换为本地 url
wget www.google.com --user ... --password ... # 指定用户名和密码
```

## 使用代理
```
# 1. 测试环境
192.168.198.20 -- 以下简称 host-20 -- centos 7
192.168.198.60 -- 以下简称 host-60 -- ubuntu 22.04

# 2. 在 host-60 上 启动代理
sudo snap install core;                            # 安装 gost
sudo snap install gost;
sudo firewall-cmd --list-all;                      # 查看开启的服务
sudo firewall-cmd --permanent --add-port=8001/tcp; # 添加防火墙端口号
sudo firewall-cmd --permanent --add-port=8002/tcp;
sudo firewall-cmd --permanent --add-port=8003/tcp;
sudo firewall-cmd --permanent --add-port=8004/tcp;
sudo firewall-cmd --reload;                        # 重新加载防火墙
sudo firewall-cmd --list-all;                      # 再次查看开启的服务
gost -L :8001 -L admin:123456@:8002 -L https://:8003 -L https://admin:123456@:8004 -F https://yunbinliu:lyb2636196546@yunbinliu.com:443;                                 # 启动代理

# 3. 在 host-20 上测试代理 -- centos
# 3.1 socks5 --- 貌似不支持
wget http://www.google.com -e http_proxy=socks5://host-60:8001
wget http://www.google.com -e http_proxy=socks5://host-60:8002 --proxy-user=admin --proxy-password=123456

wget https://www.google.com -e https_proxy=socks5://host-60:8001
wget https://www.google.com -e https_proxy=socks5://host-60:8002 --proxy-user=admin --proxy-password=123456

# 3.2 http
wget http://www.google.com -e http_proxy=http://host-60:8001
wget http://www.google.com -e http_proxy=http://host-60:8002 --proxy-user=admin --proxy-password=123456

wget https://www.google.com -e https_proxy=http://host-60:8001
wget https://www.google.com -e https_proxy=http://host-60:8002 --proxy-user=admin --proxy-password=123456

# 3.3 https --- 貌似不支持
wget http://www.google.com -e http_proxy=https://host-60:8003
wget http://www.google.com -e http_proxy=https://host-60:8004 --proxy-user=admin --proxy-password=123456

wget https://www.google.com -e https_proxy=https://host-60:8003
wget https://www.google.com -e https_proxy=https://host-60:8004 --proxy-user=admin --proxy-password=123456

# 4. 在 host-60 上测试代理 -- ubuntu
结论同上
```

