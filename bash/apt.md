
## 常用命令
```
apt update      # 更新软件源                          -- 常用
                # 软件源: /etc/apt/sources.list
                #         /etc/apt/sources.list.d/
                # 格式:  包类别(deb-软件包 deb-src-源码包) url 发行版本号 分类
                # 更新软件源:
                #   1. 修改上述文件 或 add-apt-repository ... 或 add-apt-repository --remove ...
                #   2. apt update
apt search  vim # 搜寻软件包
apt install vim # 安装软件包                          -- 常用
apt show    vim # 列出软件包的信息
apt upgrade     # 更新软件                            -- 常用
apt remove  vim # 卸载软件包                          -- 常用
apt purge   vim # 卸载软件包, 删除数据和配置文件
apt autoremove  # 自动卸载不需要的软件包              -- 常用

                   # dpkg 为 apt 的后端
dpkg -i ...        # 安装本地的包                                 -- 常用
dpkg -L vim        # 列出 vim 软件包安装的全部文件                -- 常用
dpkg --search /... # 查看该文件是哪个软件包安装的, 使用绝对路径

yum install epel-release # 安装软件源 epel -- 常用
yum check-update         # 更新软件源      -- 常用
                         # 软件源: /etc/yum.repos.d/
                         # * [...]           -- 源的名字
                         # * name=...        -- 源的描述
                         # * baseurl=file:// --	源的路径, file:// 表示本地仓库
                         # * enabled=...	 --	是否启用该仓库, 1-启用, 0-不启用
                         # * gpgcheck=...	 -- 是否不用校验软件包的签名, 0-不校验, 1-校验
                         # * gpgkey=...      -- 上个选项对应的 key 值
yum clean all            # 清空软件源缓存
yum makecache            # 新建软件源缓存
yum repolist             # 查看软件源(可达的)

yum search vim           # 搜寻软件包
yum install package_name # 安装软件, 也可以本地安装 -- 常用
yum localinstall ...     # 本地安装
yum update package_name  # 更新某个软件包           -- 常用
yum update               # 更新所有软件包           -- 常用
yum remove  package_name # 卸载软件                 -- 常用
yum erase   package_name # 卸载软件，删除数据和文件

yum list installed       # 列出已安装的软件
yum list vim             # 列出某软件包的详细信息
yum list updates         # 列出可用更新
yum provides vim         # 查看软件属于哪个软件包
yum provides /etc/vimrc  # 查看文件由哪个软件使用
```

