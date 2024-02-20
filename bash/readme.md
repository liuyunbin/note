
# 操作系统
## 守护进程 -- TODO
1. 产生子进程, 然后父进程退出, 保证子进程不是进程组的首进程
2. 新建会话, 保证子进程脱离终端的控制
3. 关闭所有的文件描述符, 避免受到父进程文件描述符的影响
4. 设置权限掩码, 避免受到父进程掩码的影响
5. 切换到根目录, 因为当前目录可能会被卸载或删除

# 计算机网络

## socket 选项
```
SO_BROADCAST -- 广播
SO_KEEPALIVE -- 保持连接
SO_LINGER ----- close() 之后的内核行为
SO_RCVBUF ----- 接收缓冲区
SO_SNDBUF ----- 发送缓冲区
SO_RCVLOWAT --- 接收低水位值
SO_SNDLOWAT --- 发送低水位值
SO_RCVTIMEO --- 接收超时
SO_SNDTIMEO --- 发送超时
SO_REUSEADDR
    * 通用 IP + 端口号 已绑定时, 不能再 bind() 其他的 IP + 此端口号
    * 端口号 已有连接时, 仍可以 bind()
    * 端口号处于 TIME_WAIT 仍可以 bind()
SO_REUSEPORT -- 允许使用完全相同的绑定, 内核实现负载均衡

TCP_MAXSEG ---- 最大分节大小
TCP_NODELAY --- 禁止 Nagle 算法

IP_TTL -------- TTL 大小
```

## 服务器
1. 迭代服务器
2. 每个客户生成一个进程
3. 每个客户生成一个线程
4. 非阻塞 IO + IO 复用
5. 进程池
6. 线程池

# 常见命令
```
bc <<< "scale=2; 10/2" # 使用两位小数,   输出: 5.00
bc <<< "ibase=2;  100" # 输入使用二进制, 输出: 4
bc <<< "obase=2;   10" # 输出使用二进制, 输出: 1010

column -t # 列对齐

curl 127.0.0.1/test -X POST -H "Content-Type: application/json" -d '{}" # 发送 POST 请求, 数据为 JSON

dd if=/dev/zero bs=1M count=1000 | nc 127.0.0.1 9999 # 测速-客户端

find . -name  lyb                     # 以文件名查找文件, 不包括路径, 可以使用通配符
find . -iname lyb                     # 同上, 忽略大小写
find . -path   "*/bash/*"             # 以全路径名查找文件, 可包括文件名, 可以使用通配符
find . -ipath  "*/bash/*"             # 同上, 忽略大小写
find . -regex ".*p+"                  # 同上, 使用正则表达式
find . -iregex ".*p+"                 # 同上, 忽略大小写
find . -maxdepth 5 –mindepth 2 -name lyb # 使用目录深度过滤
find . -L -name lyb                   # 是否跟着符号链接跳
find . -type  f                       # 以类型查找文件
find . -type f -atime -7              #     7天内访问过的文件
find . -type f -mtime  7              # 恰好7天前修改过的文件
find . -type f -ctime +7              #     7天前变化过的文件
find . -type f -newer file.txt        # 查找修改时间比 file.txt 新的文件
find . -type f -size +2G              # 以文件大小查找
find . -type f -perm 644              # 以权限查找
find . -type f -user lyb              # 以用户查找
find . -name '.git' -prune -o -type f # -prune 将前面匹配到的文件 或 目录 忽略掉
find . ! -type f -o   -name lyb       # ! 只否定最近的条件
find . \( -type f -and -name lyb \)   # 且, 多个条件必须同时成立
find . \( -type f -a   -name lyb \)   # 同上
find .    -type f      -name lyb      # 同上, 默认多个条件同时成立
find . \( -type f -or  -name lyb \)   # 或, 多个条件成立一个即可
find . \( -type f -o   -name lyb \)   # 同上
find . -empty                         # 查找空文件

iconv -f gbk -t utf-8 1.txt -o 1.txt

ln -s 1.cc 1.cc.link --- 创建符号链接

ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtu # 以 文件访问时间     排序, 不准确
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtc # 以 文件属性修改时间 排序
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrt  # 以 文件内容修改时间 排序
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtd # 以 文件内容修改时间 排序, 只列出目录本身
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrS  # 以 文件大小         排序
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrv  # 以 文件名为版本号   排序

ls -R ... 递归
ls -1 ... 每一行列出文件名
ls -L ... 符号链接所指向的文件, 而不是符号链接本身
ls -I ... 忽略文件, 使用通配符

paste # 按列合并文件

patch     1.txt diff.pathc  # 恢复文件
patch -p1 1.txt diff.pathc  # 恢复文件, 忽略 diff.pathc 的第一个路径

read name     # 读取, 如果参数值小于字段数, 多余的值放入最后一个字段

readlink -f 1.c.link  # 读取符号链接, 递归

split          # 分割文件
csplit         # 分割文件

uptime -s # 列出系统启动时间

lsof -t -i :22  # 查看指定 端口号 的进程ID

wget ... -c                        # 断点续传
wget ... -t ...                    # 指定重试的次数
wget ... -t 0                      # 不停重试
wget ... --mirror --convert-links  # 镜像下载, 递归, 并转换为本地 url
wget ... --user ... --password ... # 指定用户名和密码
wget ... --limit-rate ...          # 限制下载速度
wget ... --quota      ...          # 限制最大下载量

docker run ubuntu:15.10 -d --name "lyb"           # 启动 docker, 给起一个名字
docker run ubuntu:15.10 -d --net=host             # 主机和 docker 共享 IP 和 端口号
docker run ubuntu:15.10 -d -P                     # docke 内使用随机端口映射主机端口
docker run ubuntu:15.10 -d -p 2000:3000           # 本机:2000 绑定 docker:3000
docker run ubuntu:15.10 -d -v /home/123:/home/456 # 本机:/home/123 绑定 docker:/home/456

docker port     容器ID     # 查看端口号映射
docker ps                  # 列出当前运行的容器
docker ps -a               # 列出所有容器
docker start    容器ID     # 启动容器
docker stop     容器ID     # 停止容器
docker restart  容器ID     # 重新启动容器
docker rm -f    容器ID     # 删除容器
docker exec     容器ID ls  # 对于在后台运行的容器, 执行命令

redis flushdb # 清空数据
redis -c ...  # 集群时需要使用 -c 启动, 否则查不到数据

systemctl -a                 # 查看所有启动的服务
systemctl start      nginx   # 启动 nginx
systemctl stop       nginx   # 停止 nginx
systemctl restart    nginx   # 重启 nginx
systemctl status     nginx   # 查看 nginx 状态
systemctl enable     nginx   # 开机自动启动 nginx
systemctl disable    nginx   # 开机禁止启动 nginx
systemctl is-active  nginx   # 查看 nginx 是否启动成功
systemctl is-failed  nginx   # 查看 nginx 是否启动失败
systemctl is-enabled nginx   # 查看 nginx 是否开机启动

ntpdate -s time-b.nist.gov          # 使用时间服务器更新时间

                                        # 注意, 有不同版本的 nc, 参数不一定相同
nc -l             8080                  # 服务端(tcp), 接收单个连接
nc -lk            8080                  # 服务端(tcp), 接收多个连接
nc -lv            8080                  # 服务端(tcp), 显示连接信息
nc -lu            8080                  # 服务端(udp)
nc      127.0.0.1 8080                  # 客户端(tcp)
nc -n   127.0.0.1 8080                  # 客户端(tcp), 不进行域名解析, 节省时间
nc -N   127.0.0.1 8080                  # 客户端(tcp), 收到 EOF 后, 退出(有的版本不需要此参数, 会自动退出)
nc -w 3 127.0.0.1 8080                  # 客户端(tcp), 设置超时时间
nc -vz  127.0.0.1 8080                  # 客户端(tcp), 不发送信息, 只显示连接信息(测试单个端口)
nc -vz  127.0.0.1 8080-8090             # 客户端(tcp), 不发送信息, 只显示连接信息(测试多个端口)
nc -u   127.0.0.1 8080                  # 客户端(udp)
nc -lk            8080 | pv > /dev/null # 测速-服务端, 注意重定向, 否则会受限于终端的写速率
nc      127.0.0.1 8080      < /dev/zero # 测试-客户端

nmap             127.0.0.1 # 主机发现 -> 端口扫描, 默认扫描 1000 个端口
nmap -p  80      127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -p  80-85   127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -p  80,8080 127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -Pn         127.0.0.1 # 跳过主机发现, 直接端口扫描
nmap -sn         127.0.0.1 # 主机发现

                              # 使用 iperf 测试的时候需要关掉防火墙: sudo systemctl stop firewalld
iperf -s                      # 服务器(TCP), 端口号为 5001
iperf -s -p 8080              # 服务器(TCP), 端口号为 8080
iperf -s -f MB                # 服务器(TCP), 端口号为 5001, 设置输出的单位
iperf -s -i 10                # 服务器(TCP), 端口号为 5001, 设置报告的时间间隔为 10s
iperf -s -D                   # 服务器(TCP), 端口号为 5001, 服务器在后台启动
iperf -s -1                   # 服务器(TCP), 端口号为 5001, 只接受一个客户端
iperf -s -N                   # 服务器(TCP), 端口号为 5001, 使用 TCP nodelay 算法
iperf -s -u                   # 服务器(UDP), 端口号为 5001
iperf -c 127.0.0.1            # 客户端(TCP), 服务器端口号为 5001
iperf -c 127.0.0.1 -p 8080    # 客户端(TCP), 服务器端口号为 8080
iperf -c 127.0.0.1 -i 1       # 客户端(TCP), 服务器端口号为 5001, 设置报告的时间间隔为 1s
iperf -c 127.0.0.1 -t 10      # 客户端(TCP), 服务器端口号为 5001, 设置测试时间为 10s
iperf -c 127.0.0.1 -f MB      # 客户端(TCP), 服务器端口号为 5001, 设置输出的单位
iperf -c 127.0.0.1 -b 100M    # 客户端(TCP), 服务器端口号为 5001, 设置发送速率
iperf -c 127.0.0.1 -n 100M    # 客户端(TCP), 服务器端口号为 5001, 设置测试的数据的大小
iperf -c 127.0.0.1 -k 100M    # 客户端(TCP), 服务器端口号为 5001, 设置测试的数据包的数量
iperf -c 127.0.0.1 -R         # 客户端(TCP), 服务器端口号为 5001, 反向测试, 服务端连客户端
iperf -c 127.0.0.1         -d # 客户端(TCP), 客户端连服务端的同时, 服务端同时连客户端, 端口号为 5001
iperf -c 127.0.0.1 -L 9090 -d # 客户端(TCP), 客户端连服务端的同时, 服务端同时连客户端, 端口号为 9090
iperf -c 127.0.0.1         -r # 客户端(TCP), 客户端连服务端结束后, 服务端连回客户端,   端口号为 5001
iperf -c 127.0.0.1 -L 9090 -r # 客户端(TCP), 客户端连服务端结束后, 服务端连回客户端,   端口号为 9090
iperf -c 127.0.0.1 -P 30      # 客户端(TCP), 客户端线程数为 30
iperf -c 127.0.0.1 -u         # 客户端(UDP)

firewall-cmd --list-ports                      # 查看所有打开的端口
firewall-cmd --list-services                   # 查看所有打开的服务
firewall-cmd --get-services                    # 查看所有的服务
firewall-cmd --reload                          # 重新加载配置
firewall-cmd --complete-reload                 # 重启服务
firewall-cmd             --add-service=http    # 添加服务
firewall-cmd --permanent --add-service=http    # 添加服务, 永久生效, 需要重新加载配置
firewall-cmd             --remove-service=http # 移除服务
firewall-cmd             --add-port=80/tcp     # 添加端口
firewall-cmd --permanent --add-port=80/tcp     # 添加端口, 永久生效, 需要重新加载配置
firewall-cmd             --remove-port=80/tcp  # 移除端口
firewall-cmd             --query-masquerade    # 检查是否允许伪装IP
firewall-cmd               --add-masquerade    # 允许防火墙伪装IP
firewall-cmd --permanent   --add-masquerade    # 允许防火墙伪装IP, 永久生效, 需要重新加载配置
firewall-cmd            --remove-masquerade    # 禁止防火墙伪装IP
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080
                                               # 端口转发, 0.0.0.0:80 --> 192.168.0.1:8080
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080 --permanent
                                               # 端口转发, 永久生效, 需要重新加载配置
firewall-cmd --runtime-to-permanent            # 将当前防火墙的规则永久保存

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

\command # 忽略别名

bash -c "ls" # 执行字符串的内容

[[ "$FLOCKER" != "$0" ]] && exec env FLOCKER="$0" flock -en "$0" "$0" "$@" || : -- 常用
                # 脚本内使用, 保证脚本最多执行一次
                # 解释:
                #   1. 第一次进入脚本, 由于变量未设置, 会执行 exec
                #   2. 调用 exec, 使用 env 设置 变量名
                #   3. 执行 flock, 重新执行这个脚本, 执行完脚本后会退出, 不会执行之后的命令
                #        * 使用脚本名作为 文件锁, 脚本名使用绝对路径, 所以不会重复
                #   4. 第二次进入脚本, 由于变量已设置, 直接往下执行就可以了
                #   5. 在此期间, 如果, 有其他脚本进入, 文件锁获取失败, 就直接退出了

set -o nounset  # 使用未初始化的变量报错, 同 -u
set -o errexit  # 只要发生错误就退出, 同 -e
set -o pipefail # 只要管道发生错误就退出
set -o errtrace # 函数报错时, 也处理 trap ERR, 同 set -E
set -o  xtrace  # 执行前打印命令, 同 -x
                # 建议使用: set -ueo pipefail

trap ... EXIT # 脚本退出时, 执行某一命令或函数
trap --  EXIT # 取消信号处理

${v:-w}              # v 不为空, 返回 $v, 否则, 返回 w
${v:=w}              # v 不为空, 返回 $v, 否则, 令 v=w, 返回 w
${v:+w}              # v 不为空, 返回  w, 否则, 返回空
${v:?w}              # v 不为空, 返回 $v, 否则, 输出 w, 退出
${#val}              # 输出字符串的长度
${val:起始位置:长度} # 获取子串
lyb=123
lyb=$lyb+123         # 字符串连接, lyb 将变成 123+123
lyb=123.456.txt
lyb=${lyb%.*}        # 后缀非贪婪匹配, lyb 为 123.456
lyb=${lyb%%.*}       # 后缀  贪婪匹配, lyb 为 123
lyb=${lyb#*.}        # 前缀非贪婪匹配, lyb 为 456.txt
lyb=${lyb##*.}       # 前缀  贪婪匹配, lyb 为 txt
lyb=${lyb/*./str}    # 全文  贪婪匹配, lyb 为 strtxt, 匹配一次
lyb=${lyb//*./str}   # 全文  贪婪匹配, lyb 为 strtxt, 匹配多次
lyb=${lyb^^}         # 变为大写
lyb=${lyb,,}         # 变为小写

## 索引数组
* v=(1 2 3)  # 初始化数组, 以空字符分割多个元素
* ${v[1]}    # 数组中指定元素的值
* ${v[-1]}   # 数组中最后一个元素的值
* ${v[@]}    # 数组中所有元素的值, "1" "2" "3"
* ${#v[@]}   # 数组中元素的个数
* ${!v[@]}   # 获取所有的 key
* v+=(1 2 3) # 添加数组元素

## 关联数组
* declare -A v # 声明
* v[a]=a       # 赋值
* v[-1]=b      # 以 -1 作为 key

## 括号 -- 只列举常用的情况
* 命令替换使用 $() 而不是反引号
    * (ls)         # 子shell执行命令, 输出到屏幕上
    * lyb=$(ls)    # 子shell执行命令, 存入变量
* 整数运算
    * (())         # 整数运算, 变量不需要加 $
    * lyb=$((...)) # 将结果存储在变量中
* 使用 [[ ... ]] 测试
    * [[     -z "$lyb"   ]] # 判断是否空字符串
    * [[     -n "$lyb"   ]] # 判断是否不是空字符串
    * [[ !   -n "$lyb"   ]] # 非操作
    * [[ "111" =~ 1{1,3} ]] # 右侧使用 扩展的正则表达式匹配
    * [[ "111" == 1*     ]] # 右侧使用 通配符
    * [[     -a file     ]] # file 存在
    * [[     -e file     ]] # file 存在
    * [[     -f file     ]] # file 存在且普通文件
    * [[     -d file     ]] # file 存在且是目录
    * [[     -h file     ]] # file 存在且是符号链接
    * [[     -L file     ]] # file 存在且是符号链接
    * [[     -b file     ]] # file 存在且是  块文件
    * [[     -c file     ]] # file 存在且是字符文件
    * [[     -p file     ]] # file 存在且是一个命名管道
    * [[     -S file     ]] # file 存在且是一个网络 socket
    * [[     -s file     ]] # file 存在且其长度大于零, 可用于判断空文件
    * [[     -N file     ]] # file 存在且自上次读取后已被修改
    * [[     -r file     ]] # file 存在且可读
    * [[     -w file     ]] # file 存在且可写权
    * [[     -x file     ]] # file 存在且可执行
    * [[     -u file     ]] # file 存在且设置了 SUID
    * [[     -g file     ]] # file 存在且设置了 SGID
    * [[     -k file     ]] # file 存在且设置了 SBIT
    * [[     -O file     ]] # file 存在且属于有效的用户 ID
    * [[     -G file     ]] # file 存在且属于有效的组   ID
    * [[     -t fd       ]] # fd 是一个文件描述符，并且重定向到终端
    * [[ FILE1 -nt FILE2 ]] # FILE1 比 FILE2 的更新时间更近, 或者 FILE1 存在而 FILE2 不存在
    * [[ FILE1 -ot FILE2 ]] # FILE1 比 FILE2 的更新时间更旧, 或者 FILE2 存在而 FILE1 不存在
    * [[ FILE1 -ef FILE2 ]] # FILE1 和 FILE2 引用相同的设备和 inode 编号
* cat <(ls)                 # 将命令或函数的输出作为文件

## 脚本
$0 # 脚本名称
$1 # 第一个参数
$@ # 参数序列
$# # 参数个数

if for while

function

函数内建议使用 local 局部变量, 声明和使用放到不同的行

测试文件: [test.sh](./test.sh)

## 常用命令
!!    # 上一条命令
!l    # 执行最近使用的以 l 打头的命令
!l:p  # 输出最近使用的以 l 打头的命令
!num  # 执行历史命令列表的第 num 条命令
!$    # 上一条命令的最后一个参数
!*    # 上一条命令的所有参数
^1^2  # 将前一条命令中的 1 变成 2

## 常用快捷键
Ctrl+A      # 将光标移到行首
Ctrl+B      # 将光标向左移动一个字符
Ctrl+C      # 向前台进程组发送 SIGINT, 默认终止进程
Ctrl+D      # 删除光标前的字符 或 产生 EOF 或 退出终端
Ctrl+E      # 将光标移到行尾
Ctrl+F      # 将光标向右移动一个字符
Ctrl+G      # 响铃
Ctrl+H      # 删除光标前的一个字符
Ctrl+I      # 相当于TAB
Ctrl+J      # 相当于回车
Ctrl+K      # 删除光标处到行尾的字符
Ctrl+L      # 清屏
Ctrl+M      # 相当于回车
Ctrl+N      # 查看历史命令中的下一条命令
Ctrl+O      # 类似回车，但是会显示下一行历史
Ctrl+P      # 查看历史命令中的上一条命令
Ctrl+Q      # 解锁终端
Ctrl+R      # 历史命令反向搜索, 使用 Ctrl+G 退出搜索
Ctrl+S      # 锁定终端 -- TODO 历史命令正向搜索, 使用 Ctrl+G 退出搜索
Ctrl+T      # 交换前后两个字符
Ctrl+U      # 删除光标处到行首的字符
Ctrl+V      # 输入控制字符
Ctrl+W      # 删除光标左边的一个单词
Ctrl+X      #   TODO-列出可能的补全 ?
Ctrl+Y      # 粘贴被删除的字符
Ctrl+Z      # 前台运行的程序 --> 后台暂停
Ctrl+/      # 撤销之前的操作
Ctrl+\      # 产生 SIGQUIT, 默认杀死进程, 并生成 core 文件
Ctrl+xx     # 光标和行首来回切换

Esc+B              # 移动到当前单词的开头(左边)
Esc+F              # 移动到当前单词的结尾(右边)
Esc+.              # 获取上一条命令的最后的部分

Alt+B              # 向后（左边）移动一个单词
Alt+C              # 光标处字符转为大写
Alt+D              # 删除光标后（右边）一个单词
Alt+F              # 向前（右边）移动一个单词
Alt+L              # 光标处到行尾转为小写
Alt+R              # 取消变更
Alt+T              # 交换光标两侧的单词
Alt+U              # 光标处到行尾转为大写
Alt+BACKSPACE      # 删除光标前面一个单词，类似 Ctrl+W，但不影响剪贴板
Alt+.              # 使用上条命令的最后一个单词

Ctrl+X Ctrl+X      # 连续按两次 Ctrl+X，光标在当前位置和行首来回跳转
Ctrl+X Ctrl+E      # 用你指定的编辑器，编辑当前命令
Ctrl+insert        # 复制命令行内容
shift+insert       # 粘贴命令行内容

c++filt  a.out    # 可以解析动态库里的符号 -- 常用

g++ -0g main.cc
g++ -01 main.cc
g++ -02 main.cc
g++ -03 main.cc
g++ -g  main.cc   # 生成 gdb 的文件

g++ -fPIC -shared test.cc -o libtest.so

gdb [a.out] [pid]            # 启动 gdb               -- 常用
gdb> file a.out              # 设置可执行文件         -- 常用
gdb> set args	             # 设置程序启动命令行参数 -- 常用
gdb> show args	             # 查看设置的命令行参数
gdb> run [arguments]         # 运行程序(r)            -- 常用
gdb> attach pid              # gdb 正在运行的程序     -- 常用
gdb> info breakpoints        # 列出断点信息(i)        -- 常用
gdb> break file:line         # 在指定行设置断点(b)    -- 常用
gdb> break function          # 在制定函数设置断点(b)
gdb> break function if b==0  # 根据条件设置断点(b)
gdb> tbreak file:line        # 在指定行设置临时断点(tb)
gdb> disable breakpoints num # 禁用断点 num          -- 常用
gdb>  enable breakpoints num # 启用断点 num          -- 常用
gdb>  delete breakpoints num # 删除断点 num
gdb> clear   line            # 清除指定行的断点
gdb> continue [num]          # 继续运行到指定断点(c) -- 常用
gdb> until     line          # 运行到指定行(u)       -- 常用
gdb> jump      line          # 跳转到指定行(j), 和 until 的区别是跳过的代码不会执行
gdb> next     [num]          # 继续运行多次(n)       -- 常用
gdb> step                    # 进入函数(s)           -- 常用
gdb> finish                  # 退出函数(fin), 会执行完当前函数 -- 常用
gdb> return ...              # 退出函数, 并指定返回值, 和 finish 的区别是不会继续执行之后的代码, 直接返回
gdb> print v                 # 输出变量的值(p)       -- 常用
gdb> print v=123             # 修改变量的值(p)
gdb> p *pointer              # 输出指针指向的值
gdb> p arr[1]@3              # 输出数组 arr[1] 开始的3个元素
gdb> p/t var                 # 按  二进制格式显示变量
gdb> p/o var                 # 按  八进制格式显示变量
gdb> p/d var                 # 按  十进制格式显示变量
gdb> p/u var                 # 按  十进制格式显示无符号整型
gdb> p/x var                 # 按十六进制格式显示变量        -- 常用
gdb> p/a var                 # 按十六进制格式显示地址
gdb> p/c var                 # 按字符格式显示变量
gdb> p/f var                 # 按浮点数格式显示变量
gdb> p/s var                 # 字符串
gdb>         display v       # 和 p 类似, 但后续会自动输出变量的值
gdb> disable display num     # 暂时取消输出
gdb>  enable display num     # 恢复输出
gdb>  delete display num     # 删除自动输出变量的值的编号
gdb>       undisplay num     # 删除自动输出变量的值的编号
gdb> info    display         # 列出自动打印变量的值
gdb> x/8xb &v                # 输出 double 的二进制表示 -- 常用
gdb> x/nfu  v                # n 表示打印多少个内存单元
                             # f 打印格式, x d u o t a c f(默认8位)
                             # u 内存单元, b=1 h=2 w=4 g=8
                             # x 和 p 的区别
                             #   * p 的参数是变量的值, x 的参数是变量的地址
                             #   * p 打印的单位长度即是变量的长度, x 可以指定单位长度
                             #   * x 可以打印连续的多个单位长度(这个可以方便看 double 的每一个字节的内容)
gdb> list                    # 显示当前行之后的源程序(l) -- 常用
gdb> list -                  # 显示当前行之前的源程序
gdb> list 2,10               # 显示 2 - 10 行的源程序
gdb>  set listsize 20        # 设置列出源码的行数
gdb> show listsize           # 输出列出源码的行数
gdb> set  print elements 0   # 设置打印变量长度不受限制 -- 常用
gdb> show print elements
gdb> backtrace               # 显示堆栈信息(bt)        -- 常用
gdb> frame     n             # 查看指定层的堆栈信息(f) -- 常用
gdb> thread	                 # 切换到指定线程
gdb> watch	                 # 监视某一个变量的值是否发生变化

### 三个工作区域
* Git 仓库
* 暂存区域
* 工作目录

### 文件和目录的分类：
* 未跟踪的(untracked), 位于工作目录
* 已暂存的(staged), 属于暂存区域, 位于 Git 仓库目录
* 已提交的(committed), 位于 Git 仓库目录
* 已修改的(modified), 位于工作目录
* 已忽略的文件或目录, 位于工作目录

## 本地配置基础环境连接 GitHub
$ sudo apt install git                                 # 0. 安装 Git
$                                                      #
$ git config --global user.name  liuyunbin             # 1. 配置用户名
$ git config --global user.email yunbinliu@outlook.com # 2. 配置邮箱
$ git config --global core.editor vim                  # 3. 配置默认编辑器
$ git config --global log.date iso                     # 配置日志使用 年月日 时分秒 时区 的格式
$ git config --global alias.lg "log --pretty=format:'%ad %h %s %d %C(bold)%an%Creset' --graph"
$                                                      # 4. 添加别名, 优化日志的显示
$ git config --global core.quotepath false             # 5. 引用路径不使用八进制, 中文名不再乱码
$                                                      #
$ git config --list --global                           # 6. 查看当前用户的配置信息
$                                                      #
$ ssh-keygen -t rsa                                    # 7. 生成密钥
$                                                      # 8. 复制公钥到 GitHub
$                                                      #    将文件 `~/.ssh/id_rsa.pub` 里的公钥添加到
$                                                      #    https://github.com/settings/keys
$                                                      # 9. 到此可以免密码使用 GitHub
$ ssh -T git@github.com                                # 10. 测试是否成功

## 常用命令
git add README # 已修改 --> 已暂存
git add README # 合并时把有冲突的文件标记为已解决状态
git add -u     # 添加所有已修改的文件

git branch                                 # 列出所有的本地分支
git branch -v                              # 列出所有的本地分支, 以及最后一次提交
git branch -vv                             # 列出所有的本地分支, 以及最后一次提交, 跟踪的远程分支
git branch --merged                        # 列出已合并到 本分支  的本地分支
git branch --merged     develop            # 列出已合并到 develop 的本地分支
git branch --no-merged                     # 列出未合并到 本分支  的本地分支
git branch --no-merged  develop            # 列出未合并到 develop 的本地分支
git branch              test-branch        # 新建分支, 并不会切换分支
git branch -d           test-branch        #       删除分支, 如果该分支还未合并到当前分支,   会报错
git branch -D           test-branch        #   强制删除分支, 如果该分支还未合并到当前分支, 不会报错
git branch -m            new-branch        # 重命名当前分支, 如果新分支名已存在,   会报错
git branch -M            new-branch        # 重命名当前分支, 如果新分支名已存在, 不会报错
git branch -m old-branch new-branch        # 重命名指定分支, 如果新分支名已存在,   会报错
git branch -M old-branch new-branch        # 重命名指定分支, 如果新分支名已存在, 不会报错
git branch -r                              # 查看远程分支
git branch --set-upstream-to=orgin/develop # 本地分支和远程分支关联
git branch -u orgin/develop                # 本地分支和远程分支关联

git checkout    -- README                       # 使用暂存区的 README 替换当前目录的 README
git checkout HEAD~ README                       # 使用 HEAD~ 的 README 替换当前目录和暂存区域 的 README
git checkout    test-branch                     #       切换分支
git checkout -b test-branch                     # 新建并切换分支
git checkout --orphan test-branch               # 新建并切换到独立分支
git checkout -b      serverfix origin/serverfix # 新建并关联到远程分支
git checkout --track           origin/serverfix # 新建并关联到远程分支
git checkout         serverfix                  # 本地分支不存在, 且 远程分支存在, 新建并关联到远程分支

git clone                      https://github.com/liuyunbin/note # 克隆仓库
git clone --recurse-submodules https://github.com...             # 克隆包含子模块的项目
git clone git@github.com:liuyunbin/note     # ssh 协议
git clone git@github.com:liuyunbin/note.git # TODO: 和上一个有什么区别

git commit -a -m "message"   # 已修改 --> 已暂存 --> 已提交
git commit --amend           # 将要修改的内容合并到最后一次提交中, 并修改提交信息, 旧的提交将删除
                             # --amend 不影响作者提交的日期, 只影响提交者提交的日期
git commit --amend -m ...    # 将要修改的内容合并到最后一次提交中, 并修改提交信息, 旧的提交将删除
git commit --amend --no-edit # 同上, 但不需要修改提交信息

                                                     # --system  为整个系统中的项目配置
                                                     # --global  为某个用户下的项目配置
                                                     # --local   为单独的某个项目配置 -- 这个是默认行为
git config --global user.name  liuyunbin             # 配置用户名
git config --global user.email yunbinliu@outlook.com # 配置邮箱
git config --global core.editor vim                  # 配置默认编辑器
git config --global log.date iso                     # 日志使用 年月日 时分秒 时区 的格式
git config --global color.status      auto
git config --global color.diff        auto
git config --global color.branch      auto
git config --global color.interactive auto
git config --global --list                           # 检查配置信息
git config --global --list --show-origin             # 检查配置信息 以及 所属文件
git config --global               user.name          # 检查某一项配置
git config --global --show-origin user.name          # 检查某一项配置 及其 所属文件

git config --global core.eol     lf # 设置工作目录的换行符为   \n
git config --global core.eol   crlf # 设置工作目录的换行符为 \r\n
git config --global core.eol native # 设置工作目录的换行符为 native, 使用平台默认的换行符 == 默认值

git config --global core.autocrlf true  # 提交时: CRLF --> LF, 检出时: LF --> CRLF
git config --global core.autocrlf input # 提交时: CRLF --> LF, 检出时: 不转换
git config --global core.autocrlf false # 提交时: 不转换,      检出时: 不转换 == Linux 下的默认值

git config --global core.safecrlf true  # 拒绝提交包含混合换行符的文件
git config --global core.safecrlf false # 允许提交包含混合换行符的文件  == Linux 下的默认值
git config --global core.safecrlf warn  # 提交包含混合换行符的文件时给出警告

git config --global core.quotepath false # 引用路径不使用八进制, 中文名不再乱码

                     # 有参数比较 已修改 与 Git 仓库的区别吗? TODO
git diff             # 暂存区域 和 已修改   的差异
git diff --staged    # 暂存区域 和 Git 仓库 的差异
git diff --cached    # 暂存区域 和 Git 仓库 的差异
git diff --submodule # 获取子模块的修改

git fetch [remote-name] # 从远程仓库获取数据
                        # tag 对应的提交未推送时, 默认不会拉起该 tag
git fetch -a            # 从所有远程仓库获取数据
git fetch --tag         # 拉起所有的 tag

git for-each-ref --format='%(committerdate:iso) %(refname) %(authorname)'
                        # 查看所有远程分支最后一次的提交

git log
git log --stat              # 显示简略统计信息
git log --shortstat         # 只显示添加移除信息
git log  -p                 # 显示修改的内容
git log --patch
git log  -2                 # 显示近两次的提交
git log --oneline           # 每个提交一行, 相当于 --pretty=oneline --abbrev-commit
git log --pretty=oneline    # 每个提交一行
git log --pretty=short      # 只有作者, 没有日期
git log --pretty=full       # 显示作者和提交者
git log --pretty=fuller     # 显示作者 作者提交的日期和提交者 提交者提交的日期
git log --pretty=format:"." # 指定显示格式
git log --pretty=format:'%Cgreen%ad%Creset %h %s %C(yellow)%d%Creset %Cblue%an%Creset'
                            # %h 提交的简写哈希值
                            # %t 树的简写哈希值
                            # %p 父提交的简写哈希值
                            # %an 作者名字
                            # %ae 作者的邮箱
                            # %ad 作者提交的日期
                            # %cn 提交者的名字
                            # %ce 提交者的邮箱
                            # %cd 提交者提交的日期
                            # %d  ref名称 -- 包括tag等
                            # %s 提交说明
                            # %Cred	切换到红色
                            # %Cgreen 切换到绿色
                            # %Cblue  切换到蓝色
                            # %Creset 重设颜色
git log --graph             # 显示分支的合并
git log --name-only         # 显示修改的文件清单
git log --name-status       # 显示修改的文件信息, 增删改
git log --abbrev-commit     # 只显示提交hash的前几个字符
git log --after=2021-07-16
git log --since=2021-07-16
git log --before=2021-07-16
git log --until=2021-07-16
git log --author=liuyunbin            # 指定作者
git log --committer=54c7cd09          # 指定提交者
git log --grep=liuyunbin              # 搜索提交说明中包含该关键字的提交
git log --grep=A --grep=B             # 搜索提交说明中包含 A 或 B 的提交
git log --grep=A --grep=B --all-match # 搜索提交说明中包含 A 且 B 的提交
git log --no-merges                  # 不显示提交合并
git log a..b                         # 不在 a 中, 在 b 中的提交
git log ^a b                         # 不在 a 中, 在 b 中的提交
git log --not a b                    # 不在 a 中, 在 b 中的提交
git log a...b                        # 在 a 或 b 中, 但不同时在 a 且 b 中的提交
git log -L :main:main.cpp            # 查询某一函数的变更记录
git log -L :10:main.cpp              # 查询某一行的变更记录
git log -L 8,10:main.cpp             # 查询某几行的变更记录
git log -S main                      # 搜索字符串的增加 删除
git log -- ...                       # 指定路径
git log --decorate                   # 查看 HEAD 分支 tag 所属的提交

git ls-remote (remote)    # 查看远程分支

git merge test-branch # 将 test-branch 合并到 当前分支

git pull --rebase   # 从远程仓库获取数据, 然后合并, 自动 rebase

git push origin master                          # 推送提交到远程仓库
git push origin A:B                             # 推送本地分支A到远程分支B
git push origin --delete serverfix              # 删除远程分支
git push origin --set-upstream-to=orgin/develop # 本地分支和远程分支关联
git push origin -u orgin/develop                # 本地分支和远程分支关联
git push origin v1.0                            # 将指定 标签 推送到远程
git push origin --tags                          # 将所有 标签 推送到远程
git push origin --delete v1.0                   # 删除远程 标签
git push orign feature/test -f                  # 强推本地分支

git rebase master server-branch        # 将 server-branch 分支变基到 master
git rebase -i HEAD~6                   # 之后, 使用 f 取消掉不需要的内容, 合并提交
git rebase orign/develop               # 将 orign/develop 上的内容, 变基到 当前分支
git rebase --onto master server client # 将在 server 上存在, 不在 client 上的内容变基到 master

git remote                          # 查看远程仓库
git remote -v                       # 查看远程仓库
git remote add <shortname> <url>    # 添加远程仓库
git remote rm     origin            # 删除远程仓库
git remote remove origin            # 删除远程仓库
git remote rename origin new-origin # 重命名远程仓库
git remote show   origin            # 查看远程仓库的详细信息
git remote prune  origin            # 删除本地仓库中的远程分支(远程仓库里已删除)

git reset --soft  HEAD~           # 将 HEAD 指到 HEAD~, 暂存区和工作目录不变
                                  # 有可能会丢失 HEAD~ 之后的数据
                                  # 已提交 => 已暂存
git reset         HEAD~           #
git reset --mixed HEAD~           # 将 HEAD 指到 HEAD~, 使用 HEAD 指向的数据重置暂存区, 工作目录保持不变
                                  # 有可能会丢失 HEAD~ 之后的数据, 以及已暂存的数据
                                  # 已提交 => 已修改
git reset --hard  HEAD~           # 将 HEAD 指到 HEAD~, 使用 HEAD 指向的数据重置暂存区和工作目录 -- 常用
                                  # 会丢失 HEAD~ 之后的数据, 以及已暂存, 已修改的数据
                                  # 已提交 => 已删除
git reset --soft  HEAD~ -- README # 非法
git reset         HEAD~ -- README # 使用 HEAD~ 的 README 替换 暂存区 的 README, Git 仓库 和 工作目录保持不变
                                  # 有可能会丢失已暂存的数据, 有取消暂存的效果
git reset               -- README # 和 git reset HEAD~ -- README 等价
git reset --mixed HEAD~ -- README # 同上一个, 但已过时
git reset --hard  HEAD~ -- README # 非法

git revert      HEAD # 撤销普通提交
git revert -m 1 HEAD # 撤销合并提交, 指定保留的分支

git rm          README # 从 暂存区域 和 本地目录 中移除文件, 如果该文件已修改 或 已暂存,   会失败
git rm  -f      README # 从 暂存区域 和 本地目录 中移除文件, 如果该文件已修改 或 已暂存, 也会成功
git rm --cached README # 从 暂存区域 中移除文件, 本地目录保留

git show HEAD   # 展示指定提交
git show HEAD^  # 展示指定提交的第一父提交
git show HEAD^^ # 展示指定提交的第一父提交的第一父提交
git show HEAD^2 # 展示指定提交的第二父提交, 用于 merge
git show HEAD~  # 展示指定提交的第一父提交
git show HEAD~~ # 展示指定提交的第一父提交的第一父提交
git show HEAD~2 # 展示指定提交的第一父提交的第一父提交

git stash                     # 贮藏工作
git stash --keep-index        # 贮藏工作, 同时将暂存的内容存在索引内
git stash --include-untracked # 贮藏工作, 同时贮藏未跟踪的文件, 不包括忽略的文件
git stash  -u                 # 贮藏工作, 同时贮藏未跟踪的文件, 不包括忽略的文件
git stash --all               # 贮藏工作, 同时贮藏未跟踪的文件,   包括忽略的文件
git stash  -a                 # 贮藏工作, 同时贮藏未跟踪的文件,   包括忽略的文件
git stash list                # 列出已贮藏的工作
git stash apply               # 恢复已贮藏的工作
git stash apply --index       # 恢复已贮藏的工作, 同时恢复暂存区
git stash drop                # 丢弃贮藏区的工作
git stash pop                 # 恢复已贮藏的工作, 并丢弃贮藏区的工作

git submodule add https://github.com...      # 添加子模块
git submodule init                           # 初始化本地子模块的配置
git submodule update                         # 获取子模块远程数据, 相对于当前仓库中子模块的提交号
git submodule update --init                  # 等价于前两个命令
git submodule update --init --recursive      # 递归获取子模块的远程数据
git submodule update --remote DbConnector    # 在主目录更新子模块, 远程子模块仓库的最新数据
git submodule update --remote --merge        # 合并远程修改到本地
git submodule update --remote --rebase       # 变基远程修改到本地

git tag                       # 列出 标签
git tag -l "v*"               # 列出 标签
git tag v1.0                  # 创建 标签
git tag v1.0  提交号          # 在某次提交上, 创建 标签
git tag -d v1.0               # 删除本地 标签
git tag --contains 提交号     # 查看某个提交号在哪些 tag 中出现

# 参考资源: https://jqlang.github.io/jq/

# JSON 结构
# * 对象: 大括号包含的 key value 串, key 只能是字符串. 最好不要以数子开头, val 任意
# * 数组: 值任意
# * 字符串
# * 数字: 包括整数和浮点数
# * true
# * false
# * null
# * 最外层必须是对象或数组

# sudo apt install -y jq

json_obj='{"abc": "123", "defghi":"456"}'
json_arr='[{"abc": "123"}, {"def":"456"}, {"hij":"789"}]'

## 获取对象的值
echo -e "\n获取整个 JSON"
echo $json_obj | jq
echo $json_obj | jq .

echo -e "\n获取对象的某个 key 的值"
echo $json_obj | jq '.abc'

echo -e "\n获取对象的某个 key 的值, 并组合成数组"
echo $json_obj | jq '[.abc]'

echo -e "\n获取对象的某个 key 的值, 并组合成对象"
echo $json_obj | jq '{test: .abc}'

echo -e "\n获取对象的多个值"
echo $json_obj | jq '.abc,.def'

echo -e "\n获取对象的所有 key, 并组成数组"
echo $json_obj | jq keys

echo -e "\n获取对象的所有值"
echo $json_obj | jq .[]

echo -e "\n获取对象的所有值, 并将结果组合成数组"
echo $json_obj | jq '[.[]]'

## 获取数组的值
echo -e "\n获取数组的所有值"
echo $json_arr | jq .[]

echo -e "\n获取数组指定索引的值"
echo $json_arr | jq .[1]

echo -e "\n获取数组指定索引范围的值, 并组成数组, 左闭右开"
echo $json_arr | jq .[1:3]

echo -e "\n获取数组指的长度"
echo $json_arr | jq '.|length'

echo -e "\n获取数组指的长度"
echo $json_arr | jq '.|length'

## 获取字符串的长度
echo -e "\n获取字符串的长度"
echo $json_obj | jq '.abc|length'

## 组合结果
echo -e "\n组和数组"
echo $json_obj | jq '[.[]]'

## 其他高级特性
# map         对数组的每一项操作
# map_values  对对象的每一项操作
# select      过滤
# |           分割多次操作
# length      获取对象或数组或字符串的长度
# +           字符串拼接
# join        使用指定字符连接结果, 生成字符串
# split       字符串切割
# del         删除

# jq . -c                输出在一行
# jq . -S                排序
# jq . --tab --indent 4  使用 TAB 缩进, 指定缩进大小

ps -U RUID -G RGID           # 实际的用户和组
ps -u EUID -g EGID           # 有效的用户和组
ps -p PID                    # 进程ID, 多个进程可以重复使用 -p 或者参数以分号分割 -- 常用
ps -s SID                    # 会话ID
ps --ppid PPID               # 父进程ID
ps -t ...                    # 终端
ps -C vim                    # 进程名称, 全名称 或 前 15 位 -- 常用

ps -o ruid,ruser,rgid,rgroup # 实际的用户和组
ps -o euid,euser,egid,egroup # 有效的用户和组
ps -o suid,suser,sgid,sgroup # 保存的用户和组
ps -o fuid,fuser,fgid,fgroup # 文件的用户和组, 一般和有效的相同
ps -o supgid,supgrp          # 附属组ID
ps -o pid,ppid,pgid,sid      # 进程ID, 父进程ID, 进程组ID, 会话ID
ps -o ouid                   # 会话ID所属用户ID
ps -o tty                    # 终端
ps -o tpgid                  # 输出前台进程的ID
ps -o luid,lsession          # 终端登录的用户ID和会话ID
ps -o stat,state             # 进程状态
                             # R 正在运行
                             # S 正在休眠(可被打断)
                             # D 正在休眠(不可被打断)
                             # T 后台暂停的作业
                             # t debug 调试中
                             # Z 僵尸进程
ps -o pmem,rsz,vsz           # 内存百分比,内存,内存(含交换分区)
ps -o pcpu,c,bsdtime,cputime # cpu: 百分比,百分比整数,user+system,system
ps -o lstart,etime,etimes    # 启动时间,运行时间,运行时间(秒), 无法对 etimes 进行排序
ps -o nice,pri,psr,rtprio    # 优先级
ps -o wchan                  # 进程休眠, 返回当前使用的内核函数
                             # 进程运行, 返回 -
                             # 列出线程, 返回 *
ps -o cmd                    # 启动命令
ps -o comm                   # 进程名称
ps -o fname                  # 进程名称的前 8 位

ps -e           # 所有进程
ps -H           # 输出进程树
ps -ww          # 不限制输出宽度
ps --no-headers # 不输出列头部
ps --headers    #   输出列头部
ps --sort -pcpu # cpu 使用率逆序

ps -o lwp,nlwp # 线程ID, 线程数
ps -L          # 列每一个线程

pgrep         # 使用进程名称查找, 使用扩展的正则表达式
pgrep -f  ... # 使用启动命令匹配, 默认使用进程名称匹配(最多15位)
pgrep -c  ... # 输出匹配到的进程数目           -- 常用
pgrep -d，... # 设置输出的分割符，默认是换行符 -- 常用
pgrep -i  ... # 忽略大小写
pgrep -l  ... # 列出进程名称(最多15位)         -- 常用
pgrep -a  ... # 列出启动命令                   -- 常用
pgrep -n  ... # 仅列出最新的进程
pgrep -o  ... # 仅列出最旧的进程
pgrep -P  ... # 指定父进程ID
pgrep -s  ... # 指定会话ID
pgrep -t  ... # 指定终端
pgrep -u  ... # 指定有效用户ID
pgrep -U  ... # 指定实际用户ID
pgrep -v  ... # 反转结果
pgrep -x  ... # 精确匹配，默认不需要完全匹配
pgrep -w  ... # 列出线程ID

pwdx pid # 列出进程的当前工作目录

strace               # 追踪进程的系统调用和信号处理
strace cmd argv      # strace 和命令 同时启动
strace -p pid        # 追踪正在运行的程序, 多个进程, 指定 -p 多次
strace -c            # 统计系统调用的时间, 次数
strace -o ...        # 输出到指定的文件
strace -tt           # 显示调用时间 时分秒.毫秒
strace -T            # 显示系统调用的耗时
strace -f            # 跟踪子进程, 不包括 vfork
strace -F            # 跟踪 vfork
strace -e trace=...  # 跟踪指定信号调用
strace -s ...        # 参数是字符串时, 最大输出长度, 默认是32个字节
strace -e signal=... # 跟踪指定信号

top     # 第一行 系统时间 运行时间 用户数 平均负载
        # 第二行 进程总结
        # 第三行 CPU 总结
        # 第四行 物理内存总结
        # 第五行 虚拟内存总结
        # 交互命令
        #   空格 或 回车 刷新
        #   l 切换负载的显示
        #   t 切换任务的显示
        #   m 切换内存的显示
        #   f 选择展示的字段
        #   R 反向排序
        #   c 显示命令名称 或 完整命令行
        #   i 显示空闲任务
        #   u 显示特定用户的进程
        #   k 结束任务
        #   h 帮助
        #   L 搜索字符串
        #   H 显示线程
        #   0 不显示统计值为 0 的项
        #   1   显示所有的cpu信息
        #   < 排序字段左移
        #   > 排序字段右移
        #   M 内存排序   --- 常用
        #   P CPU 排序   --- 常用
        #   T 时间排序   --- 常用
top -n 1   # 刷新次数
top -b     # 方便写入文件
top -c     # 显示完整命令行
top -p ... # 指定 PID
top -u lyb # 指定用户

ulimit -a           # 列出资源的限制
ulimit -c unlimited # 允许 core 文件

## 建议
* 使用 etimes 可以方便计算出启动时间, 并格式化 年-月-日 时-分-秒 时区
* 一般使用进程的前 15 位即可

### 密钥登录
主目录权限不能是 777

### 常用命令
ssh -N -D A_PORT B_IP
            # 功能:
            #   动态端口转发
            #   将本地到 A_PORT 的请求转发到 B_IP
            #   使用 SOCKS5 协议
ssh -N -L A_PORT:C_IP:C_PORT B_IP
            # 功能:
            #   本地端口转发
            # 目标:
            #    A_IP:A_PORT --> C_IP:C_PORT
            # 现状:
            #    A_IP --> C_IP 失败
            #    B_IP --> C_IP 成功
            #    A_IP --> B_IP 成功
            #    B_IP --> A_IP 成功 或 失败都行
            # 实现:
            #   * 在 A_IP 机器上执行: ssh -N -L A_PORT:C_IP:C_PORT B_IP
            #   * 发往 A_IP 机器的端口号 A_PORT 的请求, 经由 B_IP 机器, 转发到 C_IP 机器的 C_PORT 端口
            #   * 即: A_IP:A_PORT --> B_IP --> C_IP:C_PORT
ssh -N -R A_PORT:C_IP:C_PORT A_IP
            # 功能:
            #   远程端口转发
            # 目标:
            #    A_IP:A_PORT --> C_IP:C_PORT
            # 现状:
            #    A_IP --> C_IP 失败
            #    B_IP --> C_IP 成功
            #    A_IP --> B_IP 成功 或 失败都行
            #    B_IP --> A_IP 成功
            # 实现:
            #   * 在 B_IP 机器上执行: ssh -N -R A_PORT:C_IP:C_PORT A_IP
            #   * 发往 A_IP 机器的端口号 A_PORT 的请求, 经由 B_IP 机器, 转发到 C_IP 机器的 C_PORT 端口
            #   * 即: A_IP:A_PORT --> B_IP --> C_IP:C_PORT
            #   * 如果要支持其他主机通过 A_IP 访问 C_IP, 需要在 A_IP 的 ssh 配置 GatewayPorts
ssh -N             # 不登录 shell, 只用于端口转发
ssh -p port        # 指定服务器端口号
ssh -f             # 在后台运行
ssh -t             # 开启交互式 shell
ssh -C             # 压缩数据
ssh -F             # 指定配置文件
ssh -q             # 不输出任何警告信息
ssh -l lyb 1.2.3.4
ssh        1.2.3.4
ssh    lyb@1.2.3.4
ssh -i ~/.ssh/id_rsa lyb # 指定私钥文件名

ssh-keygen -t rsa              # 指定密钥算法, 默认就是 rsa
ssh-keygen -b 1024             # 指定密钥的二进制位数
ssh-keygen -C username@host    # 指定注释
ssh-keygen -f lyb              # 指定密钥的文件
ssh-keygen -R username@host    # 将 username@host 的公钥移出 known_hosts 文件

ssh-copy-id -i ~/id_rsa username@host # 添加公钥到服务器中的 ~/.ssh/authorized_keys
                                      # -i 未指定时, 将使用 ~/.ssh/id_rsa.pub

#### ssh 客户端的常见配置: ~/.ssh/config, /etc/ssh/ssh_config, man ssh_config
Host *                          # 对所有机器都生效, 使用 通配符, 配置直到下一个 host
Host 123                        # 可以起一个别名
HostName 1.2.3.4                # 远程主机
Port 2222                       # 远程端口号
BindAddress 192.168.10.235      # 本地 IP
User lyb                        # 用户名
IdentityFile ~/.ssh/id.rsa      # 密钥文件
                                # 此时, 使用 ssh 123 相当于使用 ssh -p 2222 lyb@1.2.3.4 -i ~/.ssh/id.rsa
DynamicForward 1080             # 指定动态转发端口
LocalForward  1234 1.2.3.4:5678 # 指定本地端口转发
RemoteForward 1234 1.2.3.4:5678 # 指定远程端口转发

#### ssh 服务端的常见配置: /etc/ssh/sshd_config, man sshd_config
AllowTcpForwarding yes     # 是否允许端口转发, 默认允许
ListenAddress 1.2.3.4      # 监听地址
PasswordAuthentication     # 指定是否允许密码登录，默认值为 yes
Port 22                    # 监听端口号
GatewayPorts no            # 远程转发时, 是否允许其他主机使改端口号, 默认不允许

tar             acf 1.tgz                   ... # 打包并压缩, 根据后缀自动选择压缩类型
tar             acf 1.tgz -X 1.txt          ... # 打包并压缩, 跳过 1.txt 内的文件
tar             acf 1.tgz --exclude "..."   ... # 打包并压缩, 跳过文件或目录
tar              xf 1.tgz                       # 解压, 根据后缀自动选择压缩类型
tar             pxf 1.tgz                       # 解压, 完整还原权限, 比如, suid
tar              xf 1.tgz -C ...                # 解压, 指定解压目录
tar              xf 1.tgz            1.txt      # 解压部分文件或目录, 精确
tar              xf 1.tgz --exclude  1.txt      # 解压跳过部分文件或目录, 精确
tar              tf 1.tgz                       # 列出压缩包中的文件和目录, 根据后缀自动选择压缩类型
tar              tf 1.tgz  ...                  # 列出压缩包中的指定文件或目录, 说明同解压

tar zxf 1.tgz     # 解压并解包 gzip
tar jxf 1.tar.bz2     # 解压并解包 bz2

unzip    1.zip    123/       # 解压部分空目录, 精确, 需要从顶层路径开始 (必须包含斜杠)
unzip    1.zip   "123/*"     # 解压部分  目录, 精确, 需要从顶层路径开始
unzip    1.zip   "*.txt"     # 解压部分文件, 通配符, 包括子目录, 假设不存在文件 *.txt
unzip    1.zip -x ...        # 解压缩, 跳过指定文件或目录, 规则同上
unzip    1.zip -d ...        # 解压缩到指定目录
unzip -j 1.zip               # 解压时, 文件都移到顶层路径
unzip -o 1.zip               # 解压时, 直接覆盖重复的文件, 不提醒
unzip -n 1.zip               # 解压时,   不覆盖重复的文件
unzip -l 1.zip               # 列出 1.zip 的目录结构, 简单
unzip -v 1.zip               # 列出 1.zip 的目录结构, 详细点

unrar    v 1.rar          # 列出压缩包信息, 详细
unrar    l 1.rar          # 列出压缩包信息, 简易
unrar    l 1.rar ...      # 列出压缩包内的指定文件或目录
unrar    e 1.rar ...      # 解压缩到指定路径, 忽略压缩包内的路径
unrar    x 1.rar ...      # 解压缩到指定路径, 使用完整的压缩包路径
unrar    x 1.rar ... ...  # 解压缩到指定路径, 使用完整的压缩包路径, 只解压部分文件

tcpdump 可选项 协议 源 类型 值
* 协议: tcp udp icmp ip arp
* 源:   src dst
* 类型: host(IP) net(网络) port(端口号) portrange(一系列端口号)

* [S]: SYN(发起连接), [P]: push(发送), [F]:fin(结束), [R]: RST(重置), [.](确认或其他)
* ack 表示下一个要接收的 seq 号
* length 有效数据的长度
* win 接收窗口的大小
* 为避免shell干扰, 可将内容用引号包含
* and  or 可以组合多个条件

tcpdump -D                      # 列出可以 tcpdump 的网络接口
tcpdump -i eth0                 # 捕捉某一网络接口
tcpdump -i any                  # 捕捉所有网络接口
tcpdump -i any -c 20            # 捕捉所有网络接口, 限制包的数量
tcpdump -i any -n               # 捕捉所有网络接口, 使用IP和端口号, 而不是域名和服务名称
tcpdump -i any -w ...           # 捕捉所有网络接口, 将数据保存在文件中
tcpdump -i any -r ...           # 捕捉所有网络接口, 从文件中读取数据
tcpdump -i any -A               # 捕捉所有网络接口, 打印报文 ASCII
tcpdump -i any -x               # 捕捉所有网络接口, 打印包的头部, -xx -X -XX 类似
tcpdump -i any -e               # 捕捉所有网络接口, 输出包含数据链路层信息
tcpdump -i any -l               # 捕捉所有网络接口, 使用行缓存, 可用于管道
tcpdump -i any -N               # 捕捉所有网络接口, 不打印域名
tcpdump -i any -Q in            # 捕捉所有网络接口, 指定数据包的方向 in, out, inout
tcpdump -i any -q               # 捕捉所有网络接口, 简洁输出
tcpdump -i any -s ...           # 捕捉所有网络接口, 设置读取的报文长度,0 无限制
tcpdump -i any -S ...           # 捕捉所有网络接口, 使用绝对 seq
tcpdump -i any -v               # 捕捉所有网络接口, 显示详细信息, -vv -vvv 更详细
tcpdump -i any -t               # 捕捉所有网络接口, 不打印时间
tcpdump -i any -tt              # 捕捉所有网络接口, 发送(绝对时间), 确认(绝对时间)(时间戳)
tcpdump -i any -ttt             # 捕捉所有网络接口, 发送(相对时间), 确认(相对间隔)(时分秒 毫秒)
tcpdump -i any -tttt            # 捕捉所有网络接口, 发送(绝对时间), 确认(绝对时间)(年月日-时分秒)
tcpdump -i any -ttttt           # 捕捉所有网络接口, 发送(相对时间), 确认(相对时间)(时分秒 毫秒)
tcpdump -l                      # 使用行缓存, 可用于管道
tcpdump src  host 192.168.1.100 # 指定源地址 可以使用 /8 表明网络
tcpdump dst  host 192.168.1.100 # 指定目的地址
tcpdump      host 192.168.1.100 # 指定主机地址
tcpdump       net 192.168.1     # 指定网络地址, 也可以使用 /8 表示
tcpdump src  port 22            # 指定源端口号
tcpdump dst  port 22            # 指定目的端口号
tcpdump      port 22            # 指定端口号, 可使用服务名称
tcpdump not  port 22            # 排除端口号
tcpdump tcp                     # 指定协议
tcpdump "tcp[tcpflags] == tcp-syn" # 基于tcp的flag过滤
tcpdump less 32                 # 基于包大小过滤
tcpdump greater 64              # 基于包大小过滤
tcpdump ether   host  ...       # 基于 MAC 过滤
tcpdump gateway host ...        # 基于网关过滤
tcpdump ether broadcast         # 基于广播过滤
tcpdump ether multicast         # 基于多播过滤
tcpdump ip broadcast            # 基于广播过滤
tcpdump ip multicast            # 基于多播过滤

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
useradd -m -d ... #   指明主目录, 主目录可以不存在, 不存在的话会自动新建
useradd -m ...    #   用户主目录不存在的话自动新建
useradd -M ...    #   用户主目录不会新建
useradd -N ...    #   不创建和用户同名的组
useradd -o ...    #   允许 UID 重复
useradd -r ...    #   创建系统用户

usermod           # 修改用户
usermod -a -G ... #   添加附属组
usermod -m ...    #   移动主目录
usermod -l ...    #   修改登录名
usermod -L ...    #   锁定用户
usermod -U ...    #   解锁用户
                  #   其他选项同 useradd

passwd            # 修改 root 密码
passwd -stdin     # 修改 root 密码, 从标准输入读取
passwd        lyb # 修改 lyb  密码

sudo -u USERNAME COMMAND                      # 指定用户执行命令
sudo -S date -s "20210722 10:10:10" <<< "123" # 脚本中免密码使用

users  # 列出所有登陆用户

w      # 列出谁登录, 以及目前在干什么
who    # 列出谁登录
who -m # 列出当前终端登录的用户
whoami # 列出当前终端的有效用户

id        # 输出实际或有效的用户和组信息

last      # 列出最近保存的登录的信息
lastb     # 列出最近保存的登录的信息, 包括失败情况

lastlog           # 列出最近一次的登录信息
lastlog -b 10     # 最近一次的登录在 10 天前的信息
lastlog -t 10     # 最近一次的登录在 10 天内的信息
lastlog -C -u lyb # 清除 lyb 最近一次的登录信息
lastlog -S -u lyb # 设置 lyb 最近一次的登录信息
lastlog    -u lyb # 查看 lyb 最近一次的登录信息

## 模式类别
#### 普通模式
h      # 左移一个字符
j      # 下移一行
k      # 上移一行
l      # 右移一个字符

x      # 删除当前光标所在位置的字符
dl     # 删除当前光标所在位置的字符
dw     # 删除当前光标所在位置到单词末尾的字符
daw    # 删除当前光标所在位置的单词
d2w    # 删除当前光标所在位置之后的两个单词
2dw    # 删除当前光标所在位置之后的两个单词
dd     # 删除当前光标所在行
5dd    # 删除当前光标所在行开始的五行
dap    # 删除当前光标所在段落
d$     # 删除当前光标所在位置至行尾的内容
d^     # 删除当前光标所在位置至行头的内容

J      # 删除光标所在行尾的换行符
u      # 撤销上一命令
ctrl+r # 撤销上一个撤销
a      # 在光标后追加数据
A      # 在光标所在行尾追加数据
r char # 使用 char 替换光标所在位置的单个字符
R text # 进入替换模式，直到按下ESC键
i      # 在当前光标后插入数据
I      # 在当前光标所在行行头插入数据

s      # 删除当前光标所在位置的字符, 并进入插入模式
cl     # 删除当前光标所在位置的字符, 并进入插入模式
cw     # 删除当前光标所在位置的单词, 并进入插入模式
cap    # 删除当前光标所在位置的段落, 并进入插入模式
C      # 删除当前光标所在位置到该行末尾的字符, 并进入插入模式
c$     # 删除当前光标所在位置到该行末尾的字符, 并进入插入模式
S      # 删除当前光标所在行, 并进入插入模式

/  #         向后查找指定字符串, n 查找下一个, N 查找上一个
?  #         向前查找指定字符串, n 查找上一个, N 查找下一个
f  # 在当前行向后查找指定字符  , ; 查找下一个, , 查找上一个
F  # 在当前行向前查找指定字符  , ; 查找上一个, , 查找下一个
t  # 在当前行向后查找指定字符  , ; 查找下一个, , 查找上一个, 光标将停在找到字符的前一个上
T  # 在当前行向前查找指定字符  , ; 查找上一个, , 查找下一个, 光标将停在找到字符的前一个上
%  # 跳转到对应的括号

Esc -- Ctrl+[ # 回到 普通模式

#### 插入模式
#### 普通-插入模式
例如: Ctrl+Ozz, 将当前行置于屏幕中间

1. 使用 Ctrl+O 进入普通模式
2. 执行命令 zz
3. 回到插入模式

#### 命令模式
:x          # 保存并退出

:!ls        # 执行外部命令
:r !ls      # 将外部命令的执行结果插入到下一行
:1,5w !ls   # 将指定行作为命令的输入
:1,5  !ls   # 将指定行作为命令的输入, 删除这些行, 然后将外部命令的输出插入到这些行

vim -c 'set binary noeol' -c 'wq!' 1.txt # 移除文件末尾的换行符
vim -c 'set eol'          -c 'wq!' 1.txt # 添加文件末尾的换行符

vim -c "...." 1.txt # vim 启动时执行命令
vim    "+..." 1.txt # vim 启动时执行命令

set nobomb     #  去掉 bomb, 在 vimrc 中不生效
set   bomb     #  添加 bomb

set     encoding=utf-8     # vim 内部使用的编码, 一般用不到
set fileencoding=utf-8     # 编辑文件时, 设置文档保存时的编码
                           # 文件无乱码时, 可以使用此选项转换编码规则
set fileencodings=ucs-bom,utf-8,gbk,big5,gb18030,latin1
                           # 探测文件编码格式的顺序
set termencoding=utf-8     # 和终端显示有关, 一般不需要修改

set nohlsearch # 去掉高亮

edit ++enc=utf-8 ... # 以 utf-8 重新打开文件

w! ++enc=utf8 # 使用 utf-8 重新加载该文件, 使用 utf-8 保存该文件

Ctrl+F 下翻一屏
Ctrl+B 上翻一屏

awk '
     BEGIN   { getline     } #  可选  读取一行
     pattern { commands    } #  pattern 类型
                             #      * NR < 5        # 行号 [1,4] 的行
                             #      * NR==1,NR==4   # 行号 [1,4] 的行
                             #      * /linux/       #   包含 linux 的行, 支持正则
                             #      * !/linux/      # 不包含 linux 的行, 支持正则
                             #      * /start/,/end/ # [] 区间匹配, 支持正则
                             #      * $1  ~ /123/   # 使用正则表达式匹配
                             #      * $1 !~ /123/   # 使用正则表达式匹配, 排除匹配到的行
                             #      * $1 ==  123    # 数值匹配, 精确匹配
                             #      * $1 == "123"   # 字符串匹配, 精确匹配
     END     { print "end" } # 可选
    ' 1.txt

awk            '{ print $0 }' 1.txt #
awk -F:        '{ print $0 }' 1.txt # 以字符       : 作为字段分割符
awk -F123      '{ print $0 }' 1.txt # 以字符串   123 作为字段分割符
awk -F[123]    '{ print $0 }' 1.txt # 以字符   1 2 3 作为字段分割符
awk -f         1.awk          1.txt # 从文件中读取命令
awk -v lyb=... '{ print $0 }' 1.txt # 定义变量
    # * 数字:
    #     * 包括整数和浮点数
    #     * 整数除以整数，结果可能是小数
    #     * int(...) 将浮点数转换为整数，将舍弃小数部分，比如 int(1.9) == 1, int(-1.9) == -1
    #     * + 将对数字进行相加, 即使是字符串
    # * 字符串: 以单引号 或 双引号 包含的字符串
    #     * tolower() -- 小写
    #     * toupper() -- 大写
    #     *  length() -- 长度
    #     *     sub() -- 正则查找, 替换第一处
    #     *    gsub() -- 正则查找, 替换所有
    #     *  gensub() -- 正则查找, 可选择替换所有还是某一个, 不修改原字符串
    #     * index() ---- 字符串查找
    #     * match() ---- 字符串查找(正则表达式), 并将结果保存到数组
    #     * split() ---- 字符串 => 数组
    #     * substr() --- 子串
    #     * 字符串连接直接使用空分开即可
    # * 数组, awk 使用关联数组, 下标使用数字或字符串都成
    #     * 添加或修改元素  : arr[i] = ...
    #     * 删除数组中的变量: delete arr[i]
    #     * 遍历数组: i 为数组下标，注意返回的顺序不固定
    #         for (i in arr) {
    #             ....
    #         }
    #     * asort()  -- 元素排序
    #     * asorti() -- 索引排序
    # * 变量:
    #     * 变量不需要声明，可以直接使用
    #     * 变量使用一般不用使用 $, 除非是数字型变量，为了和数字区分，需要加上 $ 符号
    # * 赋值：赋值号左右两边有无空格都成
    # * 语句使用分号分割
    # *       if 语句, 同 C语言
    # *    while 语句, 同 C语言
    # * do while 语句, 同 C语言
    # *      for 语句，同 C语言, 外加 for (i in arr) i 为索引, arr 为数组
    # * 时间函数
    #     * systime()  -- 获取当前的时间戳
    #     * strftime() -- 时间戳 --> 格式化
    #     * mktime()   -- 年月日等 --> 时间戳
    # * 其他常用函数
    #     * print    参数以逗号分割, 输出的字段分割符默认为空格, 结尾将输出换行符
    #     * printf   同 C 语言
    # * 常用变量
    #       * $0  整行
    #       * $1  第一列
    #       * FS  输入字段分隔符 默认值为空字符
    #       * RS  输入记录分隔符 默认值为换行符
    #       * OFS 输出字段分隔符 默认值为空格
    #       * ORS 输出记录分隔符 默认值为换行符
    #       * FILENAME   用作gawk输入数据的数据文件的文件名
    #       * FNR        当前数据文件中的数据行数
    #       * IGNORECASE 设成非零值时，忽略gawk命令中出现的字符串的字符大小写
    #       * NF         数据文件中的字段总数
    #       * NR         已处理的输入记录数
    #       * RLENGTH    由match函数所匹配的子字符串的长度
    #       * RSTART     由match函数所匹配的子字符串的起始位置
    # * 函数, 执行 shell 命令及测试 见: test.sh

# 操作系统-正则表达式
## 正则表达式需要考虑的问题
1. 同一行只匹配一个, 还是多个
2. 匹配时, 是否忽略大小写(grep -i)

## 正则表达式语法
### 基础 扩展和 perl 风格
* 基础的正则表达式: grep, sed, vim
* 扩展的正则表达式: egrep, grep -E, sed -r, gawk
* perl的正则表达式: perl, grep -P

|        |说明                              |     基础             |   扩展   |   Perl 风格          |
|--------|----------------------------------|----------------------| ---------|----------------------|
|^       |字符串开头                        |     支持             |   支持   |    支持              |
|$       |字符串结尾                        |     支持             |   支持   |    支持              |
|.       |除换行符以外的任意字符            |     支持             |   支持   |    支持              |
|[]      |中括号中的任意字符                |     支持             |   支持   |    支持              |
|[^]     |中括号外的任意字符                |     支持             |   支持   |    支持              |
|?       |前面字符出现 [0,    1] 次, 贪婪   |   不支持, 转义后支持 |   支持   |    支持              |
|*       |前面字符出现 [0, 无穷] 次, 贪婪   |     支持             |   支持   |    支持              |
|+       |前面字符出现 [1, 无穷] 次, 贪婪   |   不支持, 转义后支持 |   支持   |    支持              |
|{n}     |前面字符出现  n        次, 贪婪   |   不支持, 转义后支持 |   支持   |    支持              |
|{n,}    |前面字符出现 [n, 无穷] 次, 贪婪   |   不支持, 转义后支持 |   支持   |    支持              |
|{n,m}   |前面字符出现 [n,    m] 次, 贪婪   |   不支持, 转义后支持 |   支持   |    支持              |
|        |在贪婪的字符后加上 ? 表示懒惰     |   不支持             | 不支持   |    支持              |
|()      |把括号内的内容当作一个整体        |   不支持, 转义后支持 |   支持   |    支持              |
|\1      |子表达式, 以左括号计数            |     支持             |   支持   |    支持              |
|(?=...) |向前查找  匹配指定内容, 但不返回  |   不支持             | 不支持   |    支持              |
|(?!...) |向前查找不匹配指定内容, 但不返回  |   不支持             | 不支持   |    支持              |
|(?<=...)|向后查找  匹配指定内容, 但不返回  |   不支持             | 不支持   |    支持, 只能固定长度|
|(?<!...)|向后查找不匹配指定内容, 但不返回  |   不支持             | 不支持   |    支持, 只能固定长度|
|(?(1))  |第一个子表达式成功才匹配          |   不支持             | 不支持   |    支持              |
| \|     |多个表达式或                      |   不支持, 转义后支持 |   支持   |    支持              |


### 对转义字符的支持
|                                |   grep|(grep -E)|(grep -P)| egrep |  sed  |(sed -r) |perl|  gawk|  vim |
|--------------------------------|-------|---------|---------|-------|-------|---------|----|------|------|
| \b   单词开头或结尾            |   支持|  支持   |  支持   |  支持 |  支持 |  支持   |支持|不支持|不支持|
| \B 非单词开头或结尾            |   支持|  支持   |  支持   |  支持 |  支持 |  支持   |支持|不支持|不支持|
| \d   数字                      | 不支持|不支持   |  支持   |不支持 |不支持 |不支持   |支持|不支持|  支持|
| \D 非数字                      | 不支持|不支持   |  支持   |不支持 |不支持 |不支持   |支持|不支持|  支持|
| \s   空白字符                  |   支持|  支持   |  支持   |  支持 |  支持 |  支持   |支持|不支持|  支持|
| \S 非空白字符                  |   支持|  支持   |  支持   |  支持 |  支持 |  支持   |支持|不支持|  支持|
| \w   数字 字母 下划线          |   支持|  支持   |  支持   |  支持 |  支持 |  支持   |支持|不支持|  支持|
| \W 非数字 字母 下划线          |   支持|  支持   |  支持   |  支持 |  支持 |  支持   |支持|不支持|  支持|
| \l 下一字符转换为小写          | 不支持|不支持   |不支持   |不支持 |  支持 |  支持   |支持|不支持|  支持|
| \L 所有字符转换为小写, 直到 \E | 不支持|不支持   |不支持   |不支持 |  支持 |  支持   |支持|不支持|  支持|
| \u 下一字符转换为大写          | 不支持|不支持   |不支持   |不支持 |  支持 |  支持   |支持|不支持|  支持|
| \U 所有字符转换为大写, 直到 \E | 不支持|不支持   |不支持   |不支持 |  支持 |  支持   |支持|不支持|  支持|

## 实战
### 1. 查找合法的 IPv4 地址 (由点分割的四个数字, 每个数字的取值都是 [0, 255])
$ v='\d|[1-9]\d|1\d{2}|2[0-4]\d|25[0-5]'
$ grep -P -o  "^\s*(($v)\.){3}($v)\s*\$" 1.txt
$
$ v='[0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]'
$ grep -E -o  "^\s*(($v)\.){3}($v)\s*\$" 1.txt

### 2. 查看固定电话是否合法(0354-5757023 (0354)5757023 5757023)
* 区号必须以0开头, 区号可以是1到3位
* 电话号码必须是7位

$ grep -P -o '^\s*((\()?0\d{1,3}(?(2)\)|-))?\d{7}\s*$' 2.txt
$
$ grep -P -o '^\s*(0\d{1,3}-|\(0\d{1,3}\))\d{7}\s*$'   2.txt
```

## 基础知识
```
硬盘: 1T = 1000G = 1000 * 1000 * 1000 * 1000B = ... / 1024 / 1024 /1024 GB = 931GB
网卡: 1000M = 1000Mbps = 125MB (网速也一样)

  带宽: 网速, 上限由网卡控制
吞吐量: 有效数据的速度, 速度小于带宽
  延时: 客户端发送数据到收到数据的时差

kmg(1000), KMG(1024), B(字节), b(位)
```

## 为什么不能去掉IP(32位)
* 为了划分子网, 方便路由, 传送数据到子网

## IP 分类
```
1.0.0.0~126.255.255.255   -- a类
128.0.0.0~191.255.255.255 -- b类
192.0.0.0~223.255.255.255 -- c类
224.0.0.0~239.255.255.255 -- 组播地址
240.0.0.0~255.255.255.254 -- 保留
10.0.0.0/8                -- a类私有
172.16.0.0/12             -- b类私有
192.168.0.0/16            -- c类私有
127.0.0.0/8               -- 本机使用
224.0.0.0/24              -- 本网络组播
239.0.0.0/8               -- 私有组播

0.0.0.0                   -- 使用 DHCP 获取 IP 时, 填的源 IP
255.255.255.255           -- 使用 DHCP 获取 IP 时, 填的目标 IP
```

## 为什么不能去掉MAC(48位, 一般无法改变)
1. 网络协议分层, 不同层实现不同的功能, 交换机会使用其传递数据
2. 直接使用 IP 其实也可以, 这个就是历史原因了

## 端口号
```
* [0, 1024)      # 公认端口号, 需要 root 启动, 比如 80
* [1024, 32768)  # 注册端口, 可以自己注册一些常用服务
* [32768, 60990) # 动态端口, 进程未指定端口号时, 将从这个范围内获取一个端口号
                 # 可通过文件 /proc/sys/net/ipv4/ip_local_port_range 获取
* [60990, 65535)
```

## 集线器: 无脑转发数据到所有出口(很少使用了)(什么都不知道)
* 机器收到不是自己的数据将丢弃

## 交换机: 将指定数据直接发送到目标机器(知道 MAC)
* 利用MAC地址表发送数据到指定机器, 找不到时, 将发送数据给所有机器
* 到达的数据需要知道目标的MAC地址
* 机器数量过大时, 会很难处理

## 路由器: 连接不同的网络(知道 IP 和 MAC)
* 真正的路由器应该只有路由的功能

## 单播(一般的网络服务都是单播)
1. 源 IP 和目标 IP 属于同一个子网时, 利用 arp 获取目标的 MAC, 然后利用交换机发送数据到指定机器
2. 否则, 利用路由表获取下一跳的 IP 地址
3. 利用 arp 获取下一跳的 MAC, 然后利用交换机发送数据到下一跳的机器
4. 默认网关会修改源 MAC, 然后再查找下一跳或指定机器
5. 数据传输过程中, 源 IP 和目标 IP 一般不变, 除了 NAT 等

## 组播(IGMP 直播 电视)(TCP 不支持)
1. 组播源注册: 服务器(组播源IP)向中介机构(RP)注册组播IP(2.2.2.2)
2. 客户端向中介机构(RP)申请加入组播IP: 生成基于中介机构(RP)的树(RPT), 同时获取组播源IP
3. 客户端向服务器(组播源IP)申请加入组播IP: 生成基于源的树(SPT), 废弃掉 RPT(SPT路径更优)
4. 服务器通过SPT, 向所有的注册组播IP的用户发送数据
    * 源IP和MAC填自己的数据
    * 目的IP为组播地址
    * 目的MAC为: 01:00:5e + 组播IP 地址低 23 bit(区分单播 组播 广播)
    * 由于目的IP为组播IP, 无法获取确切的MAC, 指定某一机器, 所以只能采用广播向所有机器发送数据
5. 客户端或者路由器通过接收到的数据的组播地址来确定是不是自己所需要的数据

## 广播(ARP, 使用DHCP申请IP地址时)(TCP 不支持)
* 发送所有数据到当前网络的所有机器
* 一般不能跨网络

## 任播(TCP 不支持)
* 最近或最合适的客户

## 应用层(消息)
* DHCP(广播, UDP)
    1. 新机器(IP: 0.0.0.0)发送信息给当前网络(IP: 255.255.255.255)的所有机器(不会跨网关)
    2. 包含 DHCP 服务器的机器发送新的 IP 给新机器(IP: 255.255.255.255)
    3. 新机器(IP: 新IP)发送确认信息给 DHCP 服务器
* http
* DNS
    * A ------------------ 域名 => IPv4
    * AAAA --------------- 域名 => IPv6
    * CNAME -------------- 域名 => 另一域名
    * /etc/resolv.conf --- DNS 服务器的地址
    * /etc/hosts --------- 域名 和 IP 的对应关系
* ICMP(传输控制协议 不使用端口号) -- ping 实现

## 传输层(段)
* TCP: 面向连接的可靠的字节流协议
* UDP: 无连接, 固定长度的不可靠的数据报协议

## 网络层(数据包)
* IPv4
* IPv6

## 网络接口层(帧)(以太网)
* MTU 最大传输单元 (链路层)
* 通过MAC可以区分是单播还是(组播或广播)
* 以太网
* WiFi

## 防火墙
```
包过滤防火墙: 过滤某些不必要的流量, 依靠 IP 端口号 协议类型(ICMP)
代理防火墙: http 代理
            socks 代理
```

