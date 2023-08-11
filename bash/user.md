
## 常用命令
```
chsh -s ... # 修改默认的 shell
chsh -l     # 列出所有支持的 shell

chage            # 修改密码相关信息
chage -d ... lyb # 设置上次密码修改的日期
chage -d 0   lyb # 下次登录必须修改密码 ------------ 常用
chage -E ... lyb # 设置密码过期的日期 -------------- 常用
chage -I ... lyb # 设置密码过期到账户被锁的天数
chage -m ... lyb # 设置密码修改的最小间隔
chage -M ... lyb # 设置密码修改的最大间隔
chage -W ... lyb # 设置密码过期前的警告的天数
chage -l     lyb # 列出密码相关信息 ---------------- 常用

last      # 列出最近保存的登录的信息
lastb     # 列出最近保存的登录的信息, 包括失败情况

lastlog           # 列出最近一次的登录信息
lastlog -b 10     # 最近一次的登录在 10 天前的信息
lastlog -t 10     # 最近一次的登录在 10 天内的信息
lastlog -C -u lyb # 清除 lyb 最近一次的登录信息
lastlog -S -u lyb # 设置 lyb 最近一次的登录信息
lastlog    -u lyb # 查看 lyb 最近一次的登录信息

su        # 切到 root
su -      # 切到 root, 更新主目录, 环境变量等, 相当于重新登录 -- 常用
su -  lyb # 切到 lyb                                          -- 常用

sudo                                          # 权限管理文件: /etc/sudoers, 使用 visudo 编辑
sudo -u USERNAME COMMAND                      # 指定用户执行命令
sudo -S date -s "20210722 10:10:10" <<< "123" # 脚本中免密码使用  -- 常用

users             # 列出所有登陆用户

useradd           # 添加用户或修改默认配置
useradd -c ...    #   指定关于用户的一段描述
useradd -e ...    #   指定用户过期日期, YYYY-MM-DD
useradd -f ...    #   指定用户密码过期到账户临时不可用的天数
useradd -g ...    #   指定主组, 主组必须存在
useradd -G ...    #   指定附属组, 附属组必须存在, 可以多个, 以逗号分割
useradd -k ...    #   指定主目录模板, 如果主目录由 useradd 创建, 模板目录中的文件将拷贝到新的主目录中
useradd -K ...    #   修改默认参数
useradd -s ...    #   指定shell
useradd -D        #   查看默认配置
useradd -D ...    #   修改默认配置
useradd    -b ... #   指明主目录的父目录, 父目录必须存在
useradd -m -b ... #   指明主目录的父目录, 父目录不必存在, 会自动新建
useradd    -d ... #   指明主目录, 主目录可以不存在, 不存在的话不会新建
useradd -m -d ... #   指明主目录, 主目录可以不存在, 不存在的话会自动新建 -- 常用
useradd -m ...    #   用户主目录不存在的话自动新建
useradd -M ...    #   用户主目录不会新建 ---------------------------------- 常用
useradd -N ...    #   不创建和用户同名的组
useradd -o ...    #   允许 UID 重复
useradd -r ...    #   创建系统用户
useradd -u ...    #   指定 UID 的值
useradd -U ...    #   创建和用户同名的组

userdel    ...    # 删除用户
userdel -r ...    #   删除用户及其主目录

usermod           # 修改用户
usermod -a -G ... #   添加附属组
usermod -m ...    #   移动主目录
usermod -l ...    #   修改登录名
usermod -L ...    #   锁定用户
usermod -U ...    #   解锁用户
                  #   其他选项同 useradd

w      # 列出谁登录, 以及目前在干什么 -- 常用
who    # 列出谁登录 -------------------- 常用
who -m # 列出当前终端登录的用户
whoami # 列出当前终端的有效用户
```

