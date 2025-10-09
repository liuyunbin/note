
## 代理
```
wget www.google.com -e http_proxy=http://127.0.0.1:7890
```

## 常用命令
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

