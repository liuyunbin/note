
## 代理
```
# 临时使用
sudo apt update -o "Acquire::http::Proxy=socks5h://127.0.0.1:7890"

# 永久使用
在 /etc/apt/apt.conf.d/proxy.conf 内添加
     Acquire::http::Proxy "socks5h://127.0.0.1:7890";
    Acquire::https::Proxy "socks5h://127.0.0.1:7890";
      Acquire::ftp::Proxy "socks5h://127.0.0.1:7890";
```

## 常用命令
```
apt update     # 根据以下配置更新软件源 --- 修改目录 /var/lib/apt/lists
               #   * /etc/apt/sources.list
               #   * /etc/apt/sources.list.d/
apt upgrade    # 更新软件
apt install    # 安装软件
apt remove     # 卸载软件
apt purge      # 卸载软件 -- 包括配置文件
apt autoremove # 智能卸载
apt clean      # 删除以下目录下载的包
               #   * /var/cache/apt/archives/
               #   * /var/cache/apt/archives/partial/
apt autoremove # 智能删除


                # 格式:  包类别(deb-软件包 deb-src-源码包) url 发行版本号 分类
                # 更新软件源:
                #   1. 修改上述文件 或 add-apt-repository ... 或 add-apt-repository --remove ...
                #   2. apt update
apt show    vim # 列出软件包的信息

                   # dpkg 为 apt 的后端
dpkg -i ...        # 安装本地的包                                 -- 常用
dpkg -L vim        # 列出 vim 软件包安装的全部文件                -- 常用
dpkg --search /... # 查看该文件是哪个软件包安装的, 使用绝对路径
```

