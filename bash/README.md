
## 作业控制
```
前台运行              # sleep 30
后台运行              # sleep 30 &
前台运行 --> 后台暂停 # ctrl+z
前台运行 --> 后台运行 # 无法直接实现
后台运行 --> 前台运行 # fg %作业号, 有无 % 都成
后台运行 --> 后台暂停 # 无法直接实现
后台暂停 --> 前台运行 # fg %作业号, 有无 % 都成
后台暂停 --> 后台运行 # bg %作业号, 有无 % 都成
                      # 无法在后台运行的命令会失败
                      # 比如 vim
  列出后台作业        # jobs
  列出后台作业        # jobs %作业号
                      # 有无 % 都成
  列出后台作业的 PID  # jobs -l
只列出后台作业的 PID  # jobs -p
只列出进程改变的作业  # jobs -n
只列出停止的作业      # jobs -s
只列出运行中的作业    # jobs -r
  杀死作业            # kill %作业号
                      # 作业号必须有 %
                      # 使用 bash 内置的 kill
```

## 进程
```
ps -ef             # 显示所有进程
ps -o pid,command  # 只显示进程 ID 和进程名称
ps -o fuser=       # 只显示实际用户
ps -o euser=       # 只显示有效用户
ps -o lstart,etime # 只显示启动时间, 耗时
ps -p 123          #   显示指定进程的信息
ps -u lyb          # 有效用户为 lyb 的进程
ps -U lyb          # 实际用户为 lyb 的进程
ps -ww             # 不限制输出宽度
                   # 显示完整进程名称
pwdx pid...        # 列出进程的工作目录
                   #
pgrep vim          # 列出 vim 的进程号
                   # 使用前缀匹配
                   # 使用扩展的正则表达式
                   # 进程名称只能使用前 15 位
pgrep -a           # 列出进程号和完整的进程名称
pgrep -c           # 列出进程数目
pgrep -l           # 列出进程号和进程名称
pgrep -u lyb       # 有效用户ID
pgrep -U lyb       # 实际用户ID
                   #
pkill    vim       # 杀死进程
                   # 使用前缀匹配
                   # 使用扩展的正则表达式
                   # 进程名称只能使用前 15 位
pkill -9 vim       # 发送指定信号
                   # 其他参数和 pgrep 类似
killall vim        # 进程名称
killall -9 vim     # 指定信号
killall -I vim     # 忽略大小写
killall -i vim     # 删除之前确认
killall -r vim     # 使用扩展的正则表达式
                   # 前缀匹配
killall -e vim     # TODO 干嘛的?
killall -u lyb vim # 指定用户的进程
                   #
kill PID           # 进程ID
                   #
/proc/.../cmdline  # 完整的启动命令
/proc/.../comm     # 进程名称, 最多 15 位
/proc/.../cwd      # 当前目录
                   #
top                # 使用 CPU 排序
                   # M 按内存使用排序
                   # f 选择排序字段
```


-----------------------------------------------------------------
getconf NAME_MAX /
getconf PATH_MAX /

## 命令需要注意的问题
通配符还是基础正则表达式, 还是扩展正则表达式
如何处理符号链接

## 通用参数

## 通配符
?      # 代表一个字符
*      # 代表零个或多个字符
[123]
[1-5]
[!a]
[^a]

## 基础正则表达式
^      # 开头
$      # 结尾
.      # 除换行符以外的任意字符
[]     # 中括号中      的任意字符
[^]    # 中括号中字符外的任意字符
?      # 前面字符出现 0 次 或 一次
*      # 前面字符出现 0 次 或 多次

## 扩展正则表达式
+      # 前面字符出现 1 次 或 多次
{n}    # 前面字符出现 n 次
{n,}   # 前面字符出现 n 次 及以上
{n, m} # 前面字符出现 n 次 到 m 次
()     # 将括号内的内容看成一个整体
|      # 或

## TODO
* 判断一个进程是否处于后台运行

## Bash 基础

Linux 基础知识
* 文件名称不能包含 /

#### 查看 Linux 临时端口号的范围
```
cat /proc/sys/net/ipv4/ip_local_port_range
32768   60999
``

* [0, 1024) 公认端口号, 需要 root 启动, 比如 80
* [1024, 32768) 注册端口, 可以自己注册一些常用服务
* [32768, 60990) 动态端口, 进程未指定端口号时, 将从这个范围内获取一个端口号
* [60990, 65535)

# 查询 域名 对应 的 IP
* nslookup baidu.com

\command # 忽略别名


#### 重定向
bash  < 1.txt
bash 1< 1.txt       # 标准输入重定向
ls    > 1.txt
ls   1> 1.txt       # 标准输出重定向
ls   >> 1.txt
ls  1>> 1.txt       # 标准输出添加重定向
ls   2> 1.txt       # 标准错误重定向
ls  2>> 1.txt       # 标准错误添加重定向
ls > 1.txt 2> 2.txt # 标准输出重定向到 1.txt, 标准错误重定向到 2.txt
ls >&2 2> 2.txt     # 标准输出重定向到和标准错误相同, 即屏幕, 标准错误重定向到 2.txt
ls > 1.txt 2>&1     # 标准输出重定向到 1.txt, 标准错误重定向到 和 标准输出相同, 即 1.txt
ls &> 1.txt         # 同时重定向标准输出和标准错误 到 1.txt
exec &>> lyb.log    # 脚本内重定向, 将 当前 shell 的标准输出 和 标准错误 重定向到 lyb.log

建议使用:
* ls > 1.txt  2> 2.txt
* ls &> /dev/null
* exec &>> lyb.log

## 各种括号的作用
* 单个小括号
    * lyb=(1 2 3)  # 数组
    * (ls)         # 子shell执行命令, 输出到屏幕上
    * lyb=$(ls)    # 子shell执行命令, 存入变量
    * cat <(ls)    # 将命令 或 函数的输出做为 文件, 命令要有打开 文件 的动作
* 双小括号
    * ((1+2))      # 数学计算, 变量不需要加 $, 计算结果不为 0 时, 表示状态正常
    * lyb=$((1+2)) # 数学计算, 变量不需要加 $, 计算结果存入变量
* 单中括号
    * [ -a file ]    # 判断文件的各种状态, < 等会有问题
    * lyb=$[lyb+lyb] # 数学计算, 变量不需要加 $, 计算结果存入变量
* 双中括号
    * [[ -a file ]]    # 判断文件的各种状态, < 等不会有问题, 支持正则
* 大括号
    * 代码块
    * 作为变量的分割符
    * {1..10..2}  # 获取字符序列

括号很复杂, 建议:
* 使用双小括号进行数学计算, 比如: lyb=$((123+456))
* 使用双中括号进行文件判断, 支持正则: [[ lyb =~ ^l ]]

## 字符串
length=${#val}       # 输出字符串的长度
${val:起始位置:长度} # 获取子串
lyb=123
lyb=$lyb+123 # lyb 将变成 123+123

${var}          # 取变量的值
${var:-word}    # 如果 var 存在, 且不为空, 返回 var 的值, 否则, 返回 word
${var:=word}    # 如果 var 存在, 且不为空, 返回 var 的值, 否则, 设置 var=word, 然后返回 word
${var:+word}    # 如果 var 存在, 且不为空, 则返回 word 的值, 否则, 返回 空
${var:?message} # 如果 var 存在, 且不为空, 返回 var 的值, 否则, 返回 输出 message, 并退出

lyb=123.456.txt
lyb=${lyb%.*}       # 后缀非贪婪匹配, lyb 为 123.456
lyb=${lyb%%.*}      # 后缀  贪婪匹配, lyb 为 123
lyb=${lyb#*.}       # 前缀非贪婪匹配, lyb 为 txt
lyb=${lyb##*.}      # 前缀  贪婪匹配, lyb 为 456.txt
lyb=${lyb/*./str}   # 全文  贪婪匹配, lyb 为 txt, 匹配一次
lyb=${lyb//*./str}  # 全文  贪婪匹配, lyb 为 txt, 匹配多次
lyb=${lyb^^}        # 变为大写
lyb=${lyb,,}        # 变为小写

和 变量的区别
* 在复制号左边的只能是变量
* 以 $ 开头的, 也是变量
* 其他的无论加不加引号, 都是字符串

## 数组
v=(1 2 3) # 定义数组
${v[1]}   # 数组中指定元素的值
${v[*]}   # 数组中所有元素的值, "1 2 3"
${v[@]}   # 数组中所有元素的值, "1" "2" "3"
${#v[*]}  # 数组中元素的个数
${#v[@]}  # 数组中元素的个数
${!v[@]}  # 获取所有的 key
${!v[*]}  # 获取所有的 key

declare -A v # 关联数组, map
v[a]=a
v[b]=b

## 子shell
source .bashrc # 当前 shell 执行, 变量等会影响当前 shell
     . .bashrc # 同上
./bin.sh       # 在子 shell 中执行, 变量等不会影响当前 shell

## 脚本
$0 # 脚本名称
$1 # 第一个参数
$* # 所有参数拼成一个字符串
$@ # 参数序列
$# # 参数个数

## 脚本上重定向
cat << EOF
    $lyb
EOF

## 常用命令
!!    # 执行上一条命令
!l    # 执行最近使用的以 l 打头的命令
!l:p  # 输出最近使用的以 l 打头的命令
!num  # 执行历史命令列表的第 num 条命令
!$    # 表示上一条命令的最后一个参数

apt show    vim # 列出软件包的信息
apt install vim # 安装软件包
apt remove  vim # 卸载软件包
apt purge   vim # 卸载软件包, 删除数据和配置文件
apt update      # 更新软件源
apt upgrade     # 更新软件

atime  # 文件内容最后被读取的时间
       # 出于性能考虑, 只有以下情况会更新
       #     atime 比 mtime 或 ctime 旧
       #     atime 比上一次 atime 超过 24 小时
       #     mount 时, 使用了 strictatime 选项

awk 'BEGIN   { print "start" }
     pattern { commands      }
     END     { print "end"   }' 1.c
 # BEGIN 和 END 都是可选的
 #         FS 输入字段分隔符
 #         RS 输入记录分隔符
 #        OFS 输出字段分隔符
 #        ORS 输出记录分隔符
 #    ENVIRON 取环境变量
 #   FILENAME 数据文件的文件名
 # IGNORECASE 忽略大小写
 #         NF 字段数量
 #         NR 当前行号, 从 1 开始
 #        FNR 当前文件中的数据行数
 #         $0 当前记录的内容
 #         $1 第一个字段的内容
 #         $2 第二个字段的内容
 # awk 使用扩展的正则表达式
 # pattern 的类型
 #      NR < 5    # 行号小于5的行
 # NR==1,NR==4    # 行号在 [1,4] 之间的行
 #     /linux/    #   包含 linux 的行
 #    !/linux/    # 不包含 linux 的行
 # /start/,/end/  # [] 区间匹配
 # $1  ~ /lyb.*/  #     字段匹配
 # $1 !~ /lyb.*/  # 排除字段匹配
 # $1 == 123      # $1 如果能转化为数字
                  # 将使用数字匹配
 # -v lyb=$SHELL  # 定义变量
 # -F:            # 设置分割符

 # * print 以逗号分割
 # * getline 读取一行
 # * ls | getline 从命令中读取

bash file_name # 执行文件内的命令
bash -c "ls"   # 将字符串的内容交由 bash 执行, 字符串里可包含重定向和管道

bc <<< "scale=2; 10/2" # 设置使用两位小数, 输出: 5.00
bc <<< "ibase=2;  100" # 输入使用二进制, 输出: 4
bc <<< "obase=2;   10" # 输出使用二进制, 输出: 1010

cat -A 1.txt # 同 -vET
cat -b 1.txt # 显示行号, 不包括空行
cat -e 1.txt # 同 -vE
cat -E 1.txt # 列出行尾标识
cat -n 1.txt # 显示行号
cat -s 1.txt # 去掉多余的连续的空行
cat -t 1.txt # 同 -Tv
cat -T 1.txt # 显示 TAB
cat -v 1.txt # 显示不可打印字符

chattr +i file # 设置文件不可修改
chattr -i file # 取消文件不可修改

chmod u=rwx 1.c # 所属用户
chmod g+x   1.c # 所属组
chmod o-r   1.c # 其他
chmod a+x   1.c # 上述所有
chmod  +x   1.c # 排除 umask 的权限
chmod  755  1.c # 使用数字设置权限
chmod 4755  1.c #
chmod u+s   1.c # 设置 SUID 权限
                # 只针对文件生效
                # 只针对二进制文件生效
                # 命令运行时, 拥有命令所属用户的权限
                # 没有可执行权限时, 展示 S
                #   有可执行权限时, 展示 s
chmod 2755  1.c
chmod g+s   1.c # 设置 SGID 权限
                # 对文件:
                #   只针对二进制文件生效
                #   命令运行时, 拥有命令所属组的权限
                # 对目录:
                #   新增的文件所属的组是此目录所属的组
                #      而不是此用户所属的组
                # 没有可执行权限时, 展示 S
                #   有可执行权限时, 展示 s
chmod 1755  1.c
chmod o+t   1.c # 设置 SBIT
                # 只针对目录生效
                # 此目录下的文件只有自己可以删除
                # 没有可执行权限时, 展示 T
                #   有可执行权限时, 展示 t

chown lyb:lyb 1.c # 修改文件所属的组和用户

comm 1.txt 2.txt                    # 文件的交并补全
comm 1.txt 2.txt       | tr -d '\t' # 全集
comm 1.txt 2.txt -1 -2 | tr -d '\t' # 交集
comm 1.txt 2.txt -3    | tr -d '\t' # 求不同时出现在两个文件中的部分
comm 1.txt 2.txt -1 -3              # B - A
comm 1.txt 2.txt -2 -3              # A - B

cp    123 456             # 拷贝文件时, 123 默认使用符号链接所指向的文件
                          # 拷贝目录时, 123 默认使用符号链接本身
                          # 456 只使用符合链接所指向的文件
cp -r 123 456             # 递归复制
cp -s 123 456             # 生成符号链接, 只能在当前目录生效
cp -d 123 456             # 总是拷贝符号链接本身
cp -P 123 456             # 总是拷贝符号链接本身
cp -L 123 456             # 总是拷贝符号链接所指的文件
cp --parents a/b/c/d test # 全路径复制, 将生成 test/a/b/c/d

crontab -l # 查询任务表
crontab -e # 编辑任务表
crontab -r # 删除任务表
           #   格式为: f1          f2         f3       f4       f5                      exe
           # 分别表示: 分钟(0-59)  小时(0-23) 日(1-31) 月(1-12) 星期几(0-6, 星期天为 0) 执行的程序
           # * 表示每分钟等都执行
           # 1-3 表示 1 到 3分钟内执行
           # */3 表示每 3 分钟执行一次
           # 1-10/3 表示 1-10 分钟内, 每 3 分钟执行一次
           # 1,3,5 表示 1,3,5 分钟执行
           # crontab 不会自动执行 .bashrc, 如果需要, 需要在脚本中手动执行

ctime  # 状态修改时间
       #   文件内容修改
       #   文件名称修改: mv, rename
       #   所有者, 所属组变化: chown
       #   权限修改: chmod

Ctrl+A      # TODO-将光标移到行首
Ctrl+B      # TODO-将光标向左移动一个字符
Ctrl+C      # TODO-向前台进程组发送 SIGINT, 默认终止进程
Ctrl+D      # TODO-删除光标前的字符 或 产生 EOF 或 退出终端
Ctrl+E      # TODO-将光标移到行尾
Ctrl+F      # TODO-将光标向右移动一个字符
Ctrl+G      # TODO-退出当前编辑
Ctrl+H      # TODO-删除光标前的一个字符
Ctrl+I      # TODO-删除光标前的一个字符
Ctrl+J      # TODO-删除光标前的一个字符
Ctrl+K      # TODO-删除光标处到行尾的字符
Ctrl+L      # TODO-清屏
Ctrl+M      # TODO-清屏
Ctrl+N      # TODO-查看历史命令中的下一条命令
Ctrl+O      # TODO-类似回车，但是会显示下一行历史
Ctrl+P      # TODO-查看历史命令中的上一条命令
Ctrl+Q      # TODO-解锁终端
Ctrl+R      # TODO-历史命令反向搜索, 使用 Ctrl+G 退出搜索
Ctrl+S      # TODO-锁定终端 或 历史命令正向搜索, 使用 Ctrl+G 退出搜索
Ctrl+T      # TODO-交换前后两个字符
Ctrl+U      # TODO-删除光标处到行首的字符
Ctrl+V        TODO-           # 输入字符字面量，先按 Ctrl+V 再按任意键 ?
Ctrl+W      # TODO-删除光标左边的一个单词
Ctrl+X        TODO-           # 列出可能的补全 ?
Ctrl+Y      # TODO-粘贴被删除的字符
Ctrl+Z  # 前台运行的程序 --> 后台暂停
Ctrl+/      # TODO-撤销之前的操作
Ctrl+\      # TODO-产生 SIGQUIT, 默认杀死进程, 并生成 core 文件

curl -I ... # 只打印头部信息

cut -f 1,2  # 按列切割
cut -d ":"  # 设置分割符

date "+%F %T"               # 输出: 年-月-日 时-分-秒
date "+%Y-%m-%d %H:%M:%S"   # 输出: 年-月-日 时-分-秒
date "+%F %R"               # 输出: 年-月-日 时-分
date "+%Y-%m-%d %H:%M"      # 输出: 年-月-日 时-分
date "+%s"                  # 输出: 时间戳
date -d "20200202 01:01:01" # 使用: 指定输入日期
date -d "@...."             # 使用: 时间戳
date -r 1.c                 # 使用: 文件的 mtime
date -s "20200202 10:10:10: # 更新系统时间
                            # 需要 root 权限

dd if=/dev/zero of=junk.data bs=1M count=1

df -Th # 所挂载的系统的使用情况

diff    1.txt 2.txt              # 比较两个文件的不同
diff -u 1.txt 2.txt              # 一体化输出, 比较两个文件的不同
diff    1.txt 2.txt > diff.pathc

dirname $(readlink -f $0) # 获取脚本的名称

docker run ubuntu:15.10     /bin/ls                 # 启动 docker 并执行命令 ls
docker run ubuntu:15.10 -it /bin/bash               # 使用交互式终端
docker run ubuntu:15.10 -d                          # 使用后台模式, 返回容器 ID
docker run ubuntu:15.10 -d --name "lyb"             # 给 docker 起一个名字
docker run ubuntu:15.10 -d --net=host               # 主机和 docker 共享 IP 和 端口号
docker run ubuntu:15.10 -d -P                       # docke 内使用随机端口映射主机端口
docker run ubuntu:15.10 -d -p 2000:3000             # 将本机的端口号 2000 绑定到docker 的 3000
docker run ubuntu:15.10 -d -v /home/123:/home/456   # 将本机目录 /home/123 绑定到 docker 的 /home/456

docker port     容器ID                   # 查看端口号映射
docker ps                                # 列出当前运行的容器
docker ps -a                             # 列出所有容器
docker logs     容器ID                   # 查看容器的输出
docker start    容器ID                   # 启动容器
docker stop     容器ID                   # 停止容器
docker restart  容器ID                   # 重新启动容器
docker rm -f    容器ID                   # 删除容器
docker attach   容器ID                   # 进入在后台运行的容器
docker exec -it 容器ID /bin/bash         # 对于在后台运行的容器, 开启交互式终端, 终端退出, docker 不会终止
docker exec     容器ID ls                # 对于在后台运行的容器, 执行命令

dos2unix 1.txt # \r\n --> \n

dpkg -L vim        # 列出 vim 软件包安装的全部文件
dpkg --search /... # 查看该文件是哪个软件包安装的, 使用绝对路径

du                      # 列出目录大小
du -a                   # 列出目录和文件大小
du -d 1                 #
du --max-depth=1        # 最大目录深度
du -sh                  # 只列出整体使用大小
du -ch                  #   列出整体使用大小
du -X 1.txt             #
du --exclude-from=1.txt # 忽略文件中的内容
du --exclude="*.txt"    # 忽略指定文件, 支持通配符

echo       "123"   # 输出换行
echo    -n "123"   # 不换行
echo -e -n "123\t" # 解析转义字符

echo -e "\e[1;30m lyb \e[0m" # 文本颜色:   黑色
echo -e "\e[1;31m lyb \e[0m" # 文本颜色:   红色
echo -e "\e[1;32m lyb \e[0m" # 文本颜色:   绿色
echo -e "\e[1;33m lyb \e[0m" # 文本颜色:   黄色
echo -e "\e[1;34m lyb \e[0m" # 文本颜色:   蓝色
echo -e "\e[1;35m lyb \e[0m" # 文本颜色: 洋红色
echo -e "\e[1;36m lyb \e[0m" # 文本颜色:   青色
echo -e "\e[1;37m lyb \e[0m" # 文本颜色:   白色

echo -e "\e[1;40m lyb \e[0m" # 背景颜色:   黑色
echo -e "\e[1;41m lyb \e[0m" # 背景颜色:   红色
echo -e "\e[1;42m lyb \e[0m" # 背景颜色:   绿色
echo -e "\e[1;43m lyb \e[0m" # 背景颜色:   黄色
echo -e "\e[1;44m lyb \e[0m" # 背景颜色:   蓝色
echo -e "\e[1;45m lyb \e[0m" # 背景颜色: 洋红色
echo -e "\e[1;46m lyb \e[0m" # 背景颜色:   青色
echo -e "\e[1;47m lyb \e[0m" # 背景颜色:   白色

echo -e "\e[1;37m lyb \e[0m" # 文本加粗
echo -e "\e[4;37m lyb \e[0m" # 文本下划线
echo -e "\e[5;37m lyb \e[0m" # 文本闪烁
echo -e "\e[7;37m lyb \e[0m" # 反向选择

exec ls      # 替换当前 shell, 执行后不再执行之后的命令
exec &>1.txt # 打开文件描述符, 然后继续执行之后的命令
env          # 设置环境变量, 然后执行程序

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

firewall-cmd --list-ports                       # 查看所有打开的端口
firewall-cmd --list-services                    # 查看所有打开的服务
firewall-cmd --get-services                     # 查看所有的服务
firewall-cmd --permanent --add-service=http     # 添加服务, 永久生效, 需要重新加载配置
firewall-cmd --permanent --add-service=https    # 添加服务, 永久生效, 需要重新加载配置
firewall-cmd             --add-service=https    # 添加服务
firewall-cmd             --remove-service=http  # 移除服务
firewall-cmd --permanent --add-port=8080/tcp    # 添加端口, 永久生效, 需要重新加载配置
firewall-cmd             --add-port=8080/tcp    # 添加端口
firewall-cmd             --remove-port=8080/tcp # 移除端口
firewall-cmd --reload                           # 重新加载配置
firewall-cmd --complete-reload                  # 重新加载配置, 重启服务
firewall-cmd             --query-masquerade     # 检查是否允许伪装IP
firewall-cmd               --add-masquerade     # 允许防火墙伪装IP
firewall-cmd --permanent   --add-masquerade     # 允许防火墙伪装IP, 永久生效, 需要重新加载配置
firewall-cmd            --remove-masquerade     # 禁止防火墙伪装IP
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080
                                                # 端口转发, 0.0.0.0:80 --> 192.168.0.1:8080
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080 --permanent
                                                # 端口转发, 永久生效, 需要重新加载配置
firewall-cmd --runtime-to-permanent             # 将当前防火墙的规则永久保存

flock    123.txt ls # 使用 123.txt 设置文件互斥锁 并执行命令, 如果获取锁失败, 将等待
flock -n 123.txt ls # 使用 123.txt 设置文件互斥锁 并执行命令, 如果获取锁失败, 将退出
flock -e 123.txt ls # 使用 123.txt 设置文件共享锁 并执行命令, 默认为互斥锁
#### flock: 设置文件锁

常用参数
* -n 表示, 如果获取文件锁失败, 直接退出, 不再等待
* -e 表示, 使用互斥锁, 默认即是互斥锁
* -c 执行一个单独的命令

脚本内使用, 保证脚本最多执行一次
```
[[ "$FLOCKER" != "$0" ]] && exec env FLOCKER="$0" flock -en "$0" "$0" "$@" || :
```

解释:
1. 第一次进入脚本, 由于变量未设置, 会执行 exec
2. 调用 exec, 使用 env 设置 变量名
3. 执行 flock, 重新执行这个脚本, 执行完脚本后会退出, 不会执行之后的命令
    * 使用脚本名作为 文件锁, 脚本名使用绝对路径, 所以不会重复
4. 第二次进入脚本, 由于变量已设置, 直接往下执行就可以了
5. 在此期间, 如果, 有其他脚本进入, 文件锁获取失败, 就直接退出了


gcc -0g main.cc
gcc -01 main.cc
gcc -02 main.cc
gcc -03 main.cc

$ gdb main.cc -g                # 生成可以 gdb 的文件
$
$ gdb [a.out] [pid]             # 启动 gdb
$ gdb> q                        #
$ gdb> quit                     # 退出 gdb
$
$ gdb> file a.out               # 设置可执行文件
$ gdb>                          #
$ gdb> set args arguments       # 设置参数
$ gdb>                          #
$ gdb> r   [arguments]          #
$ gdb> run [arguments]          # 运行程序
$ gdb>                          #
$ gdb> attach pid               # gdb 正在运行的程序
$ gdb>                          #
$ gdb> kill                     # 退出程序
$
$ gdb> info breakpoints         # 列出断点信息
$ gdb>                          #
$ gdb> b     file:function:line #
$ gdb> break file:function:line # 在指定行设置断点
$ gdb> break function           # 在制定函数设置断点
$ gdb> break function if b==0   # 根据条件设置断点
$ gdb>                          #
$ gdb> rbreak function*         # 使用正则设置断点
$ gdb>                          #
$ gdb> tbreak function          # 设置临时断点
$ gdb>                          #
$ gdb> ignore n count           # 忽略断点 n， count 次
$ gdb>                          #
$ gdb> disable [num]            # 忽略断点 num
$ gdb>  enable [num]            # 使断点 num 生效
$ gdb>  delete [num]            # 删除断点 num
$ gdb>                          #
$ gdb> clear file:function:line # 清除指定行的断点
$
$ gdb> c        [num]           #
$ gdb> continue [num]           # 继续运行到指定行 或 断点
$ gdb> u     line               #
$ gdb> until line               # 运行到指定行
$
$ gdb> n    [num]               #
$ gdb> next [num]               # 继续运行多次
$
$ gdb> s                        #
$ gdb> step                     # 进入函数
$ gdb> finish                   # 退出函数
$
$ gdb> p     v            #
$ gdb> print v            # 输出变量的值
$ gdb> print *pointer     # 输出指针指向的值
$ gdb> print *pointeri@10 # 输出数组
$ gdb>
$ gdb> p/x var            # 按十六进制格式显示变量。
$ gdb> p/d var            # 按十进制格式显示变量。
$ gdb> p/u var            # 按十六进制格式显示无符号整型。
$ gdb> p/o var            # 按八进制格式显示变量。
$ gdb> p/t var            # 按二进制格式显示变量。
$ gdb> p/a var            # 按十六进制格式显示变量。
$ gdb> p/c var            # 按字符格式显示变量。
$ gdb> p/f var            # 按浮点数格式显示变量。
$ gdb>                    #
$ gdb> x/8xb &v           # 输出 double 的二进制表示
$ gdb> x/nfu  v           # n 表示打印多少个内存单元
$                         # f 指明打印格式, x, d, u, o, t, a, c, f, 说明同上
$                         # u 表示内存单元, b=1 byte, h=2 bytes, w=4 bytes, g=8 bytes
$ gdb> list               # 列出源码
$ gdb> l                  # 显示当前行之后的源程序
$ gdb> l -                # 显示当前行之前的源程序
$ gdb> list 2,10          # 显示 2 - 10 行的源程序
$ gdb>  set listsize 20   # 设置列出源码的行数
$ gdb> show listsize      # 输出列出源码的行数
$
$ gdb> set  print elements 0 # 设置打印变量长度不受限制
$ gdb> show print elements
$
$ gdb>  watch v         # v 的值有变化时,     立刻停住
$ gdb> rwatch v         # v 的值被读时,       立刻停住
$ gdb> awatch v         # v 的值被读或被写时, 立刻停住
$ gdb> info watchpoints # 查看所有的观察点
$
$ gdb> backtrace # 显示堆栈信息
$ gdb> bt        # 显示堆栈信息
$
$ gdb> frame n # 查看指定层的堆栈信息
$ gdb> f     n # 查看指定层的堆栈信息

$ gdb> into display       # 列出自动打印的值
$ gdb>                    #
$ gdb> display v          # 自动打印 v
$ gdb> delete display     # 删除自动打印
$
$ gdb> info skip          # 列出要跳过的文件 或 函数
$ gdb>                    #
$ gdb> skip function add  # 跳过函数
$ gdb> skip disable [num] # 暂时不跳过
$ gdb> skip  enable [num] # 设置跳过
$ gdb> skip  delete [num] # 删除跳过

getopt  # a  无参数, a: 有参数
        # -- 表示可选参数的终止
        # 会重新排列参数
        # 可以解析 --bug
        # 可以区分无参数, 有参数, 可选参数的情况
        # -kval 可以当作 -k val 处理
        # 参数带空格可能出问题

getopts # -o 短选项, -l 长选项
        # a 无参数, a: 有参数, a:: 参数可选
        #  -- 表示可选参数的终止
        # 不会重排参数
        # 只能解析 -k, -k val, 不能解析 --bug, -kval
        # 只能区分有参数和无参数的情况
        # 参数带空格也能处理

git config --global core.quotepath false # 引用路径不使用八进制, 中文名不再乱码

grep -v                   # 输出不匹配的内容
grep -c                   # 输出匹配的行的次数, 同一行只输出一次
grep -o                   # 只输出匹配的内容
grep -n                   # 输出匹配的行号
grep -l                   # 输出匹配的文件
grep -f                   # 从文件中读取匹配模式
grep -i                   # 忽略大小写
grep -h                   # 不输出文件名
grep -q                   # 静默输出
grep -A 5                 # 输出之前的行
grep -B 5                 # 输出之后的行
grep -C 5                 # 输出之前之后的行
grep -e .. -e ..          # 多个模式取或
grep -E ..                # 使用扩展的正则表达式, 同 egrep
grep -W ..                # 单词匹配
grep -X ..                # 行匹配
grep ... --inclue "*.c"   # 指定文件
grep ... --exclue "*.c"   # 忽略文件
grep ... --exclue-dir src # 忽略目录

groupadd               # 添加组
groupdel               # 删除组
groupdel               # 修改组
groups                 # 查看所属的组

history

iconv

ip addr
ip route

less
空格   : 下一页
ctrl+F : 下一页
b      : 上一页
ctrl+b : 上一页
回车   : 下一行
=      : 当前行号
y      : 上一行

ln -s target symbolic_link_name # 创建符号链接

                   ## lsof -- sudo yum install lsof
lsof -iTCP         # 查看 TCP 信息
lsof -i :22        # 查看指定 端口号 的信息
lsof -i@1.2.3.4:22 # 查看是否连接到指定 IP 和 端口号上
lsof -p 1234       # 指定 进程号
lsof -d 0,1,2,3    # 指定 文件描述符
lsof -t            # 仅获取进程ID
lsof -a            # 参数取且

ls           # 列出当前目录中的元素
ls -a        # 列出当前目录中的元素, 包括隐藏的文件
ls -A        # 同上, 但不包括 . 和 ..
ls -S        # 使用 文件大小 排序, 大 --> 小
ls -v        # 使用 版本号 排序
ls -X        # 使用 扩展名 排序
ls -d        # 只列出目录本身，而不列出目录内元素
ls -l        # 列出当前目录中的元素的详细信息
ls -h        # 使用人类可读的形式
ls -F        # 在目录后添加 /，在可执行文件后添加 *
ls -r        # 逆序
ls -R        # 递归
ls -1        # 在每一行列出文件名
ls -L        # 符号链接所指向的文件, 而不是符号链接本身
ls -I "*.sh" # 忽略文件, 使用通配符
ls -c        # 使用 ctime 排序, 新 --> 旧
ls -cl       # 展示 ctime, 使用文件名排序
ls -clt      # 使用 ctime 排序 和 展示
ls -t        # 使用 mtime 排序, 新 --> 旧
ls -tl       # 使用 mtime 排序 和 展示
ls -u        # 使用 atime 排序, 新 --> 旧
ls -ul       # 展示 atime, 使用文件名排序
ls -ult      # 使用 atime 排序 和 展示

md5sum 1.txt # MD5 检验

mkdir    abc   # 创建目录
mkdir -p a/b/c # 递归创建目录, 目录已存在时不报错

mktemp         # 临时文件
mktemp -d      # 临时目录

## more
空格   : 下一页
ctrl+F : 下一页
b      : 上一页
ctrl+b : 上一页
回车   : 下一行
=      : 当前行号

mtime  # 文件内容被修改的时间

mv a b # a 是符号链接时, 将使用符号链接本身
       # b 是指向目录  的符号链接时， 相当于 移到 b 本身
       # b 是指向目录  的符号链接时， 相当于 移到 b 最终所指向的目录下
       # b 是指向不存在的符号链接时， 相当于 重命名

nohup sleep 1000 & ## 脱离终端, 在后台运行

ntpdate -s time-b.nist.gov # 使用时间服务器更新时间

patch     1.txt diff.pathc  # 恢复文件
patch -p1 1.txt diff.pathc  # 恢复文件, 忽略 diff.pathc 的第一个路径

passwd lyb # 修改密码

readlink symbolic_link_name     # 读取符号链接
readlink symbolic_link_name -f  # 读取符号链接, 递归

read name     # 读取, 如果参数值小于字段数, 多余的值放入最后一个字段
read -p "123" # 指定提示符
read -t 5     # 指定超时时间

rm     a    # 文件删除
rm -r  a    # 递归删除
rm -rf a    # 强行删除, 文件不存在时, 忽略

rmdir abc                            # 删除空目录
rmdir -p a/b/c                       # 递归删除, 相当于依次删除 a/b/c a/b a
rmdir --ignore-fail-on-non-empty abc # 忽略非空目录

sed # 读取一行到模式空间 --> 执行操作 -- 循环
    # i-行前插入, a-行后插入, c-修改行, y-字符转换, = 行号,
    # l 打印不可打印字符
    # w 写入文件, r 插入文件的内容
    # n 读取下一行到模式空间 N 将下一行添加到模式空间内容后
    # d 删除模式空间的内容   D 删除模式空间的第一行内容, 之后跳到开头
    # p 打印模式空间的内容   P 打印模式空间的第一行内容
# h 将模式空间复制到保持空间
# H 将模式空间附加到保持空间
# g 将保持空间复制到模式空间
# G 将保持空间附加到模式空间
# x 交换模式空间和保持空间的内容
# ! 不执行...
# :abc 定义标签
# b abc 跳到指定标签
# t abc 前一个命令成功会跳转
# & 匹配到的内容
sed -n                              # 不输出内容
sed -e ...                          # 指定命令
sed -f ...                          # 从文件读取命令
sed    "s/123/456/g"          1.txt
sed    "1,5s/123/456/g"       1.txt # [1,5]
sed    "1,$s/123/456/g"       1.txt # [1,$]
sed    "/lyb/s/123/456/g"     1.txt # 使用正则表达式确定范围
sed -i "s/123/456/g"          1.txt # 直接在原文件上修改
sed -i "s|123|456|g"          1.txt # 使用不同的分割符
sed -i "/^$/d"                1.txt # 删除空行
sed -i "s/.*/[&]/g"           1.txt # & 用于表示所匹配到的内容
sed -i "s/\([0-9]*\).*/\1/g"  1.txt # \1 表示第一个字串
sed -i "s/\([0-9]\+\).*/\1/g" 1.txt # \1 表示第一个字串, 为什么 + 要转义 * 不用

set -u
set -o nounset  # 使用未初始化的变量报错
set -e
set -o errexit  # 只要发生错误就退出
                # [[ 1 != 1 ]] 会退出
                # [[ 1 != 1 ]] && ... 不会退出
                # 函数返回非 0 值会退出
                # 建议使用: [[ 1 != 1 ]] && ... || : 的格式
set -o pipefail # 只要管道发生错误就退出
set -E
set -o errtrace # 函数报错时, 也会执行 trap ... ERR 的命令
set -x
set -o  xtrace  # 执行前打印命令
set -v
set -o verbose  # 读取前打印命令
set -o vi       # 使用 vi 快捷键
set -- ....     # 重新排列参数


sort            # 排序
sort -b         # 忽略前置空白
sort -c         # 检查是否已排序
sort -d         # 字典序排序
sort -f         # 忽略大小写
sort -k 4       # 指定排序的列字段
sort -k 4.1,4.2 # 指定排序的列字段
sort -h         # 以 K, M, G 排序
sort -i         # 忽略不可打印字符
sort -m         # 合并排序过的文件
sort -M         # 以月份排序
sort -n         # 以数字进行排序
sort -r         # 逆序
sort -t :       # 指定列的分割符
sort -u         # 重复项只输出一次
sort -V         # 以版本号排序
sort lyb -o lyb # 排序并存入原文件

###ssh 常用命令
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
                                # 此时, 使用 ssh 123 相当于使用 ssh -p 2222 lyb@1.2.3.4
DynamicForward 1080             # 指定动态转发端口
LocalForward  1234 1.2.3.4:5678 # 指定本地端口转发
RemoteForward 1234 1.2.3.4:5678 # 指定远程端口转发

#### ssh 服务端的常见配置: /etc/ssh/sshd_config, man sshd_config
AllowTcpForwarding yes     # 是否允许端口转发, 默认允许
ListenAddress 1.2.3.4      # 监听地址
PasswordAuthentication     # 指定是否允许密码登录，默认值为 yes
Port 22                    # 监听端口号
GatewayPorts no            # 远程转发时, 是否允许其他主机使改端口号, 默认不允许

stat       1.c # 列出 birth atime mtime ctime
stat -c %a 1.c # 查看权限, 644 形式
stat -c %A 1.c # 查看权限, rwx 形式
stat -c %g 1.c # 查看文件所属组的 ID
stat -c %G 1.c # 查看文件所数组的 name
stat -c %h 1.c # 查看硬链接的个数
stat -c %m 1.c # 查看挂载点
stat -c %u 1.c # 查看文件所属用户的 ID
stat -c %U 1.c # 查看文件所属用户的 name
stat -c %w 1.c # 查看 birth
stat -c %x 1.c # 查看 atime
stat -c %y 1.c # 查看 mtime
stat -c %z 1.c # 查看 ctime
stat -L    1.c # 符号链接所指向的文件, 而不是符号链接本身

sudo                                                 # 权限管理文件: /etc/sudoers, 使用 visudo 编辑
                                                     # 使用当前用户的密码
sudo -u USERNAME COMMAND                             # 指定用户执行命令
echo "654321" | sudo -S date -s "20210722 10:10:10"  # 脚本中免密码使用

## 用户切换
su              # 切换 root, 输入 root 密码
su root         # 同 su
su -            # 切换 root, 更新主目录, 环境变量等等
su -l           # 同 su -
su - root       # 同 su -
su - root -c ls # 使用 root 执行命令 ls

systemctl start      nginx   # 启动 nginx
systemctl stop       nginx   # 停止 nginx
systemctl restart    nginx   # 重启 nginx
systemctl status     nginx   # 查看 nginx 状态
systemctl enable     nginx   # 开机自动启动 nginx
systemctl disable    nginx   # 开机禁止启动 nginx
systemctl is-active  nginx   # 查看 nginx 是否启动成功
systemctl is-failed  nginx   # 查看 nginx 是否启动失败
systemctl is-enabled nginx   # 查看 nginx 是否开机启动

tail -f * # 动态查看新增内容

tar -cvf  /path/to/foo.tar --exclude=\*.o /path/to/foo/ # foo         --> foo.tar, 忽略 .o 文件
tar -cvf  /path/to/foo.tar                /path/to/foo/ # foo         --> foo.tar
tar -czvf /path/to/foo.tgz                /path/to/foo/ # foo         --> foo.tgz
tar -czvf /path/to/foo.tar.gz             /path/to/foo/ # foo         --> foo.tar.gz
tar -cjvf /path/to/foo.tar.bz2            /path/to/foo/ # foo         --> foo.tar.bz2
tar -xvf  /path/to/foo.tar                              # foo.tar     --> foo
tar -xzvf /path/to/foo.tgz                              # foo.tgz     --> foo
tar -xzvf /path/to/foo.tar.gz                           # foo.tar.gz  --> foo
tar -xjvf /path/to/foo.tar.bz2                          # foo.tar.bz2 --> foo
tar -xjvf /path/to/foo.tar.bz2 -C /path/to/destination/ # foo.tar.bz2 --> foo, 指定工作目录
tar -acf /path/to/foo.tgz --exclude="*.o" /path/to/foo/ # 根据后缀自动 打包 或 压缩, 并忽略指定文件
tar -acf /path/to/foo.tgz -X file         /path/to/foo/ # 根据后缀自动 打包 或 压缩, 并忽略 file 内的文件
tar -xf  /path/to/foo.tgz -C /path/to/destination/      # 根据后缀 解包 或 解压 到指定目录
tar -tf a.tgz                                           # 列出 tgz 中的文件和目录

tee    1.txt # 管道中把文件拷贝到文件
tee -a 1.txt # 管道中把文件添加到文件

touch        1.c # 修改 atime mtime
                 # 修改 mtime 会影响 ctime
touch -a     1.c # 修改 atime
touch -c     1.c # 文件不存在时, 不创建文件
touch -d ... 1.c # 指定时间, 而不是当前时间
touch -h     1.c # 改变符号链接本身, 而不是所指向的文件
touch -m     1.c # 修改 mtime
                 # 修改 mtime 会影响 ctime
touch -r 2.c 1.c # 以 2.c 的时间修改 1.c
touch -t ... 1.c # 指定时间
                 # 依次是: 时区-年-月-日-时-分-秒

trap ... ERR  # 发生错误退出时, 执行指定命令
trap ... EXIT # 任意情况退出时, 执行指定命令

tree -p "*.cc"       # 只显示  匹配到的文件
tree -I "*.cc"       # 只显示没匹配到的文件
tree -H . -o 1.html  # 指定目录生成 html 文件

tr    'a-z' 'A-Z' # 小写转大写
tr -d 'a-z'       # 删除字符
tr -s ' '         # 压缩字符

uniq    # 删除重复的行
uniq -c # 输出统计的次数
uniq -d # 只输出重复的行, 重复的项只输出一次
uniq -D # 只输出重复的行, 重复的项只输出多次
uniq -i # 忽略大小写
uniq -u # 只输出没重复的行

unix2doc 1.txt # \n --> \r\n

unzip -l a.zip # 列出 zip 的内容
unzip -j a.zip # 解压时, 不要路径

useradd               # 添加用户
userdel               # 删除用户
usermod               # 修改用户
usermod    -g lyb kds # 将 kds 的主组变为 lyb
usermod    -G lyb kds # 将 kds 的附组变为 lyb
usermod -a -G lyb kds # 将 kds 的附组添加 lyb

vim
Ctrl+F 下翻一屏
Ctrl+B 上翻一屏

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
a      # 在光标后追加数据
A      # 在光标所在行尾追加数据
r char # 使用 char 替换光标所在位置的单个字符
R text # 进入替换模式，直到按下ESC键
i      # 在当前光标后插入数据
I      # 在当前光标所在行行头插入数据

cl
cw
cap    # 删除内容并进入插入模式

yy     # 复制当前行
5y     # 复制包含当前行在内的 5 行

G      # 移到最后一行
gg     # 移到第一行
num gg # 移到第 num 行

/  #         向后查找指定字符串, n 查找下一个, N 查找上一个
?  #         向前查找指定字符串, n 查找上一个, N 查找下一个
f  # 在当前行向后查找指定字符  , ; 查找下一个, , 查找上一个
F  # 在当前行向前查找指定字符  , ; 查找上一个, , 查找下一个
t  # 在当前行向后查找指定字符  , ; 查找下一个, , 查找上一个, 光标将停在找到字符的前一个上
T  # 在当前行向前查找指定字符  , ; 查找上一个, , 查找下一个, 光标将停在找到字符的前一个上

Esc -- Ctrl+[ # 回到 普通模式

#### 插入模式

#### 普通-插入模式

例如: Ctrl+Ozz, 将当前行置于屏幕中间

1. 使用 Ctrl+O 进入普通模式
2. 执行命令 zz
3. 回到插入模式

#### 命令模式
:s/old/new/     # 替换光标所在行第一个的 old
:s/old/new/2g   # 替换光标所在行第二个以及之后的 old
:s/old/new/g    # 替换光标所在行所有的 old
:n,ms/old/new/g # 替换行号n和m之间所有的 old
:%s/old/new/g   # 替换整个文件中的所有的 old
:%s/old/new/gc  # 替换整个文件中的所有 old，但在每次出现时提示
:s/^old/new/    # 替换光标所在行的以 old 打头的
:s/old$/new/    # 替换光标所在行的以 old 结尾的
:s/^$//         # 删除空行

:q          #     退出
:q!         # 强制退出
:w filename # 保存为指定文件
:wq         # 保存并退出

:!ls        # 执行外部命令
:r !ls      # 将外部命令的执行结果插入到下一行
:1,5w !ls   # 将指定行作为命令的输入
:1,5  !ls   # 将指定行作为命令的输入, 删除这些行, 然后将外部命令的插入到这些行

:set nohlsearch # 去掉高亮

wc    # 输出 换行符数 字符串数 字节数
wc -l #   行数
wc -w # 字符串数
wc -c # 字节数
wc -m # 字符数

cat lyb | xargs -i vim {} # 以此编辑 lyb 中的每一个文件

yum list installed       # 列出已安装的软件
yum list vim             # 列出某软件包的详细信息
yum list updates         # 列出可用更新
yum provides file_name   # 查看文件属于哪个软件包
yum update package_name  # 更新某个软件包
yum update               # 更新所有软件包
yum install package_name # 安装软件
yum remove  package_name # 卸载软件
yum erase   package_name # 卸载软件，删除数据和文件
yum provides /etc/vimrc  # 查看文件由哪个软件使用
yum repolist             # 列出使用的软件源
--------------------------------------------------

#### IFS
* IFS 的默认值是: " \t\n"
* 查看 IFS 值: echo -n "$IFS" | hexdump
* IFS 包含转义字符时, 需要在开头添加 $, IFS=$'\n'
* IFS 为默认值 或 " \t\n" 时
    * 整个对象开头和结尾的空字符都将忽略
        * for 遍历 str="   123 456 789  " 时, 将生成 3 个串: 123 456 789
    * 对象内部连续的空字符都将当作一个字符
        * for 遍历 str="123   456    789" 时, 将生成 3 个串: 123 456 789
* IFS 为其他值时, 假定: IFS="a "
    * 如果, IFS 包含空字符, 对象内部连续的空字符都将当作一个字符
        * for 遍历 str="123      456a789" 时, 将生成 3 个串: 123 456 789
    * 其他字符连续出现时, 将当作多个分隔符
        * for 遍历 str="123aa456a789" 时, 将生成 4 个串: 123 空字符串 456 789
    * $*, ${str[*]}: 将使用 IFS 的第一个字符连起来
        * str=(1 2 3); echo "${str[*]" 将输出: 1a2a3
    * 对象末尾的分割符将被忽略
        * for 遍历 str="123aa456a789a" 时, 将生成 4 个串: 123 空字符串 456 789

#### 内置的 echo 将以 IFS 切分参数, 输出以空格隔开
* echo  123   456   789  # 将输出: 123 456 789
* echo "123   456   789" # 将输出: 123   456  789, 原样输出

#### Bash 常用快捷键

Esc+B              # 移动到当前单词的开头(左边)
Esc+F              # 移动到当前单词的结尾(右边)

Alt+B              # 向后（左边）移动一个单词
Alt+d              # 删除光标后（右边）一个单词
Alt+F              # 向前（右边）移动一个单词
Alt+t              # 交换字符 ?
Alt+BACKSPACE      # 删除光标前面一个单词，类似 Ctrl+W，但不影响剪贴板
Ctrl+X Ctrl+X      # 连续按两次 Ctrl+X，光标在当前位置和行首来回跳转
Ctrl+X Ctrl+E      # 用你指定的编辑器，编辑当前命令
Ctrl+insert        # 复制命令行内容
shift+insert       # 粘贴命令行内容

Esc+.              # 获取上一条命令的最后的部分
