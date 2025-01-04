
## 基本命令
```
curl www.google.com
curl www.google.com -o 1.html                   # 指定目标文件名称
curl www.google.com --silent                    # 不显示进度信息
curl www.google.com -C -                        # 断点续传
curl www.google.com --referer http://google.com # 指定跳转前的界面
curl www.google.com --cookie ...                # 指定 cookie
curl www.google.com --user-agent "Mozilla/5.0"  # 设置浏览器信息
curl www.google.com -H ...                      # 指定其他header
curl www.google.com --limit-rate 20k            # 限速
curl www.google.com --max-filesize 100M         # 设置最大大小
curl www.google.com -u user:pass                # 设置用户名和密码
curl www.google.com --head                      # 只打印响应头部
curl www.google.com -k                          # 忽略证书验证
curl 127.0.0.1/test -X POST -H "Content-Type: application/json" -d '{}' # 发送 POST 请求, 数据为 JSON
```

## 代理
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
# 3.1 socks5
curl -x socks5h://host-60:8001              http://www.google.com;
curl -x socks5h://admin:123456@host-60:8002 http://www.google.com;

curl -x socks5h://host-60:8001              https://www.google.com;
curl -x socks5h://admin:123456@host-60:8002 https://www.google.com;

# 3.2 http
curl -x http://host-60:8001              http://www.google.com;
curl -x http://admin:123456@host-60:8002 http://www.google.com;

curl -x http://host-60:8001              https://www.google.com;
curl -x http://admin:123456@host-60:8002 https://www.google.com;

# 3.3 https --- 貌似不支持
curl -x https://host-60:8003              http://www.google.com;
curl -x https://admin:123456@host-60:8003 http://www.google.com;

curl -x https://host-60:8004              https://www.google.com;
curl -x https://admin:123456@host-60:8004 https://www.google.com;

# 4. 在 host-60 上测试代理 -- ubuntu
结论同上
```

