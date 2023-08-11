
##
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

basename ... # 获取文件名
dirname  ... # 获取目录名

bc <<< "scale=2; 10/2" # 使用两位小数,   输出: 5.00
bc <<< "ibase=2;  100" # 输入使用二进制, 输出: 4
bc <<< "obase=2;   10" # 输出使用二进制, 输出: 1010

cat    1.txt      # 输出 1.txt 的内容
cat -n 1.txt      # 显示行号
cat -b 1.txt      # 显示行号, 行号不包括空行
cat -s 1.txt      # 去掉多余的连续的空行
cat -T 1.txt      # 显示 TAB

chattr +i 1.c # 设置文件不可修改
chattr -i 1.c # 取消文件不可修改

column -t # 列对齐

comm                        1.c 2.c                    # 要求文件已排序, 以行比较
comm --check-order          1.c 2.c                    #   检测文件是否已排序
comm --nocheck-order        1.c 2.c                    # 不检测文件是否已排序
comm --output-delimiter=... 1.c 2.c                    # 指定列分割, 默认是 TAB
comm                        1.c 2.c       | tr -d '\t' # 全集
comm                        1.c 2.c -1 -2 | tr -d '\t' # 交集
comm                        1.c 2.c -3    | tr -d '\t' # B - A 和 A - B
comm                        1.c 2.c -1 -3              # B - A
comm                        1.c 2.c -2 -3              # A - B

cp    123 456      # 拷贝文件时, 使用符号链接所指向的文件
                   # 拷贝目录时, 目录中的符号链接将使用符号链接本身
                   # 456 只使用符号链接所指向的文件
cp -r 123 456      # 递归复制
cp -P 123 456      # 总是拷贝符号链接本身
cp -L 123 456      # 总是拷贝符号链接所指的文件
cp --parents a/b t # 全路径复制, 将生成 t/a/b

chmod  755    1.c # 设置权限, 不足四位时, 补前缀 0
chmod  644 -R 1.c # 递归
chmod 4755    1.c # 设置 SUID(4)
chmod 2755    1.c # 设置 SGID(2)
chmod 1755    1.c # 设置 SBIT(1)

chown lyb:lyb 1.c # 修改文件所属的组和用户

cut                        -b 2   1.c # 按字节切割, 输出第 2 个字节
cut                        -c 2-  1.c # 按字符切割, 输出 [2, 末尾] 字符
cut                        -f 2-5 1.c # 按列切割,   输出 [2,5] 列
cut -d STR                 -f 2,5 1.c # 设置输入字段的分隔符, 默认为 TAB, 输出 第 2 列和第 5 列
cut -s                     -f  -5 1.c # 不输出不包含字段分隔符的列, 输出 [开头, 5] 的列
cut --output-delimiter=STR -f  -5 1.c # 设置输出的字段分隔符, 默认使用输入的字段分隔符

date    "+%Y-%m-%d %H:%M:%S %z"     # 输出: 年-月-日 时-分-秒 时区
date    "+%F %T %z"                 # 输出: 年-月-日 时-分-秒 时区
date    "+%j"                       # 输出: 一年中的第几天
date    "+%u"                       # 输出: 一周中的第几天(1..7), 1 为周一
date    "+%U"                       # 输出: 一年中的第几周(00..53), 从周一开始
date    "+%w"                       # 输出: 一周中的第几天(0..6), 0 为周末
date    "+%W"                       # 输出: 一年中的第几周(00..53), 从周末开始
date    "+%s"                       # 输出: 时间戳
date -d "2020-02-02 01:01:01 +0800" # 指定输入日期和时间, 秒数不能为 60
date -d "@...."                     # 使用: 时间戳
date -d "next sec"                  # 下一秒
date -d "next secs"                 # 下一秒
date -d "next second"               # 下一秒
date -d "next seconds"              # 下一秒
date -d "next min"                  # 下一分钟
date -d "next mins"                 # 下一分钟
date -d "next minute"               # 下一分钟
date -d "next minutes"              # 下一分钟
date -d "next hour"                 # 下一小时
date -d "next hours"                # 下一小时
date -d "next day"                  # 明天
date -d "next days"                 # 明天
date -d "next mon"                  # 下周一
date -d "next monday"               # 下周一
date -d "next month"                # 下个月
date -d "next months"               # 下个月
date -d "next year"                 # 下年
date -d "next years"                # 下年
date -d "next year  ago"            # 去年, 除年外, 其他也可以
date -d "next years ago"            # 去年, 除年外, 其他也可以
date -d "10year"                    # 十年以后, 除年外, 其他也可以
date -d "10years"                   # 十年以后, 除年外, 其他也可以
date -d "10   year"                 # 十年以后, 除年外, 其他也可以
date -d "10   years"                # 十年以后, 除年外, 其他也可以
date -d "10   year  ago"            # 十年以前, 除年外, 其他也可以
date -d "10   years ago"            # 十年以前, 除年外, 其他也可以
date -d "tomorrow"                  # 明天
date -d "now"                       # 现在
date -s "2020-02-02 10:10:10"       # 更新系统时间, 需要 root, 格式见 -d 选项
date -r 1.c                         # 使用: 文件的 mtime

df   -Th                # 查看磁盘挂载情况

diff    1.txt 2.txt # 比较两个文件的不同
diff -u 1.txt 2.txt # 一体化输出, 比较两个文件的不同

dd if=/dev/zero of=junk.data bs=1M count=1
dd if=/dev/zero bs=1M count=1000 | nc 127.0.0.1 9999 # 测速-客户端

dos2unix 1.txt

du                      # 列出目录大小
du -0                   # 输出以 \0 分割, 默认是换行符
du -a                   # 列出目录和文件大小
du -d 1                 # 最大目录深度
du -sh                  # 只列出整体使用大小
du --exclude="*.txt"    # 忽略指定文件, 支持通配符

echo -n "123"                # 不换行
echo -e "\e[1;33m lyb \e[0m" # 文本黄色 加粗
echo  $'123\''               # 单引号内存在单引号的情况
echo  $(cal)                 # 输出字符以空格区分
echo "$(cal)"                # 保留输出字符的分割符
echo ${!S*}                  # 列出所有包含 S 的变量

file 1.txt # 查看换行符等

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

free -h     # 内存使用情况

getconf NAME_MAX / # 获取变量的值
getconf PATH_MAX /

getopts # 处理参数, -- 表示可选参数的终止

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
grep -P ..                # 使用 perl 风格的正则表达式
grep -W ..                # 单词匹配
grep -X ..                # 行匹配
grep ... --inclue "*.c"   # 指定文件
grep ... --exclue "*.c"   # 忽略文件
grep ... --exclue-dir src # 忽略目录

hd         1.txt # 每组一个字节 显示十六进制+ASCII -- 不建议使用, 得考虑字节序
hexdump -b 1.txt # 每组一个字节 显示八进制
hexdump -c 1.txt # 每组一个字节 显示字符
hexdump -C 1.txt # 每组一个字节 显示十六进制+ASCII
hexdump -d 1.txt # 每组两个字节 显示  十进制
hexdump -o 1.txt # 每组两个字节 显示  八进制
hexdump -x 1.txt # 每组两个字节 显示十六进制

history

iconv -f gbk -t utf-8 1.txt -o 1.txt

less # 空格   : 下一页
     # ctrl+F : 下一页
     # b      : 上一页
     # ctrl+b : 上一页
     # 回车   : 下一行
     # =      : 当前行号
     # y      : 上一行

ln -s target symbolic_link_name # 创建符号链接

ls &> /dev/null # 重定向

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

md5sum 1.txt # MD5 检验

mkdir    abc   # 创建目录
mkdir -p a/b/c # 递归创建目录, 目录已存在时不报错

mktemp         # 临时文件
mktemp -d      # 临时目录

more    # 空格   : 下一页
        # ctrl+F : 下一页
        # b      : 上一页
        # ctrl+b : 上一页
        # 回车   : 下一行
        # =      : 当前行号

mv a b # a 是符号链接时, 将使用符号链接本身
       # b 是指向文件  的符号链接时， 相当于 移到 b 本身
       # b 是指向目录  的符号链接时， 相当于 移到 b 最终所指向的目录下
       # b 是指向不存在的符号链接时， 相当于 重命名

nohup sleep 1000 & # 脱离终端, 在后台运行, 忽略信号 SIGHUP

od -t a   1.txt # 每组一个字节, 显示字符(nl) -- 不建议使用, 得考虑字节序
od -t c   1.txt # 每组一个字节, 显示字符(\n)
od -t d4  1.txt # 每组四个字节, 显示有符号的十进制数字
od -t f4  1.txt # 每组四个字节, 显示浮点数
od -t o4  1.txt # 每组四个字节, 显示  八进制数字
od -t u4  1.txt # 每组四个字节, 显示无符号的十进制数字
od -t x4  1.txt # 每组四个字节, 显示十六进制数字
od -t d4z 1.txt # 每组四个字节, 显示十进制数字, 并显示原始字符
od -a     1.txt # 同 -t a
od -b     1.txt # 同 -t o1
od -c     1.txt # 同 -t c
od -d     1.txt # 同 -t u2
od -f     1.txt # 同 -t f
od -i     1.txt # 同 -t dI
od -l     1.txt # 同 -t dL
od -o     1.txt # 同 -t o2
od -s     1.txt # 同 -t d2
od -x     1.txt # 同 -t x2
od --endian={big|little} 1.txt # 指明大小端

passwd            # 修改 root 密码
passwd -stdin     # 修改 root 密码, 从标准输入读取
passwd        lyb # 修改 lyb  密码

patch     1.txt diff.pathc  # 恢复文件
patch -p1 1.txt diff.pathc  # 恢复文件, 忽略 diff.pathc 的第一个路径

patch     1.txt diff.pathc  # 恢复文件
patch -p1 1.txt diff.pathc  # 恢复文件, 忽略 diff.pathc 的第一个路径

readlink    1.c.link  # 读取符号链接
readlink -f 1.c.link  # 读取符号链接, 递归

read name     # 读取, 如果参数值小于字段数, 多余的值放入最后一个字段

readlink    1.c.link  # 读取符号链接
readlink -f 1.c.link  # 读取符号链接, 递归

redis flushdb # 清空数据
redis -c ...  # 集群时需要使用 -c 启动, 否则查不到数据

rm -r  a    # 递归删除
rm -rf a    # 强行删除, 文件不存在时, 忽略

route    -- 已过时, 被 ip route 替代

rz          #  windows 向 虚拟机  发送数据

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
sort -n         # 以数字进行排序
sort -r         # 逆序
sort -t :       # 指定列的分割符
sort -u         # 重复项只输出一次
sort -V         # 以版本号排序
sort lyb -o lyb # 排序并存入原文件

sleep 30   # 前台运行
sleep 30 & # 后台运行

systemctl start      nginx   # 启动 nginx
systemctl stop       nginx   # 停止 nginx
systemctl restart    nginx   # 重启 nginx
systemctl status     nginx   # 查看 nginx 状态
systemctl enable     nginx   # 开机自动启动 nginx
systemctl disable    nginx   # 开机禁止启动 nginx
systemctl is-active  nginx   # 查看 nginx 是否启动成功
systemctl is-failed  nginx   # 查看 nginx 是否启动失败
systemctl is-enabled nginx   # 查看 nginx 是否开机启动

sz          #  虚拟机  向 windows 发送数据

tac               # 最后一行 => 第一行

tail -f * # 动态查看新增内容

tee    1.txt # 管道中把文件拷贝到文件
tee -a 1.txt # 管道中把文件添加到文件

tr    'a-z' 'A-Z' # 小写转大写
tr -d 'a-z'       # 删除字符
tr -s ' '         # 压缩字符

tree -p "*.cc"       # 只显示  匹配到的文件
tree -I "*.cc"       # 只显示没匹配到的文件
tree -H . -o 1.html  # 指定目录生成 html 文件

                 # 修改文件时间
touch        1.c # 修改 atime mtime ctime
touch -a     1.c # 修改 atime
touch -c     1.c # 文件不存在时, 不创建文件
touch -h     1.c # 改变符号链接本身, 而不是所指向的文件
touch -m     1.c # 修改       mtime ctime
touch -r 2.c 1.c # 以 2.c 的时间修改 1.c
touch -d ... 1.c # 指定时间, 格式同 date
touch -t ... 1.c # 指定时间
                 # 依次是: 时区-年-月-日-时-分-秒

tr    'a-z' 'A-Z' # 小写转大写
tr -d 'a-z'       # 删除字符
tr -s ' '         # 压缩字符

traceroute: 查看数据包经过的路径

tree -p "*.cc"       # 只显示  匹配到的文件
tree -I "*.cc"       # 只显示没匹配到的文件
tree -H . -o 1.html  # 指定目录生成 html 文件

uniq    # 删除重复的行
uniq -c # 输出统计的次数
uniq -d # 只输出重复的行, 重复的项只输出一次
uniq -D # 只输出重复的行, 重复的项输出多次
uniq -i # 忽略大小写
uniq -u # 只输出没重复的行

unix2doc 1.txt

uname -a # 全部信息
uname -m # x86_64 等
uname -r # 内核版本

uptime -s # 列出系统启动时间

cat lyb | xargs -i vim {} # 以此编辑 lyb 中的每一个文件

xxd -b     1.txt  # 输出二进制而不是十六进制
xxd -e     1.txt  # 使用小端模式
xxd -g ... 1.txt  # 每组的字节数            -- 建议使用, 读取的顺序和存储的顺序相同, 不需要考虑字节序

wc    # 输出 换行符数 字符串数 字节数
wc -l #   行数
wc -w # 字符串数
wc -c # 字节数
wc -m # 字符数

```

## 用户管理
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

id        # 输出实际或有效的用户和组信息

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


ss       # 显示已连接的 UDP, TCP, unix domain sockets
ss -x    # unix domain sockets
ss -u    #          UDP
ss -t    # 已连接的 TCP
ss -tl   #   监听的 TCP
ss -ta   # 已连接和监听的 TCP
ss -tln  # 服务使用数字而不是名称
ss -tlnp # 列出监听的进程号, 需要root 权限
ss -s    # 显示统计
ss src   192.168.198.128:22  # 通过源  IP和端口号筛选信息
ss dst   192.168.198.1:51932 # 通过目的IP和端口号筛选信息
ss sport OP 22               # 通过源  端口号过滤数据
ss dport OP 22               # 通过目的端口号过滤数据
                             # OP 可以是空, >(gt) >=(ge) <(lt) <=(le) ==(eq) !=(ne), 注意转义

ifconfig -- 已过时, 被 ip addr  替代

nslookup baidu.com # 查询 域名 对应 的 IP

tcpdump 可选项 协议(tcp udp icmp ip arp) 源(src dst) 类型(host net port portrange) 值
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
tcpdump ether   host  ...          # 基于 MAC 过滤
tcpdump gateway host ...          # 基于网关过滤
tcpdump ether broadcast      # 基于广播过滤
tcpdump ether multicast      # 基于多播过滤
tcpdump ip broadcast         # 基于广播过滤
tcpdump ip multicast         # 基于多播过滤

ping      www.bing.com # 使用 ICMP ping 主机
ping -c 3 www.bing.com # 使用 ICMP ping 主机, 设置测试的次数
ping -i 3 www.bing.com # 使用 ICMP ping 主机, 设置间隔的秒数
ping -w 3 www.bing.com # 使用 ICMP ping 主机, 设置耗时的上限
ping -f   www.bing.com # 使用 ICMP ping 主机, 高速率极限测试, 需要 root 权限

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

netstat  -- 已过时, 被 ss       替代

nmap             127.0.0.1 # 主机发现 -> 端口扫描, 默认扫描 1000 个端口
nmap -p  80      127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -p  80-85   127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -p  80,8080 127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -Pn         127.0.0.1 # 跳过主机发现, 直接端口扫描
nmap -sn         127.0.0.1 # 主机发现

                   # lsof -- sudo yum install lsof
lsof -iTCP         # 查看 TCP 信息
lsof -i :22        # 查看指定 端口号 的信息
lsof -i@1.2.3.4:22 # 查看是否连接到指定 IP 和 端口号上
lsof -p 1234       # 指定 进程号
lsof -d 0,1,2,3    # 指定 文件描述符
lsof -t            # 仅获取进程ID

ip a                                 # 显示网卡信息
ip addr    show                      # 显示指定网卡信息
ip address show dev   lo             # 显示指定网卡信息
ip address add 192.268.1.10 dev eth0 # 添加 IP 地址
ip address del 192.268.1.10 dev eth0 # 删除 IP 地址

ip link set dev eth0 multicast on  # 启用组播
ip link set dev eth0 multicast off # 禁用组播
ip link set dev eth0 up            # 启用网卡
ip link set dev eth0 down          # 禁用网卡
ip link set dev eth0 arp       on  # 启用 arp 解析
ip link set dev eth0 arp       off # 禁用 arp 解析
ip link set dev eth0 mtu      1500 # 设置最大传输单元
ip link set dev eth0 address  ...  # 设置 MAC 地址

ip route       # 路由信息
ip route show  # 路由信息
ip route get   # 查看指定 IP 的路由信息
ip route add   # 添加路由
ip route chage # 修改路由
ip route flush # 清空路由信息

ip neighbour  # 查看 arp 协议

ip -s link         # 查看统计信息
ip -s link ls eth0 # 查看统计信息, 指定网卡

ip maddr  # 广播
ip rule   # 路由策略, 和网卡有关
ip tunnel # 隧道

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

```
curl -I ... # 只打印头部信息
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


## 常用命令
```
c++filt  a.out    # 可以解析动态库里的符号 -- 常用

           # 定期执行命令 -- 常用
crontab -l # 查询任务表
crontab -e # 编辑任务表
           # 格式为: 分钟 小时 日 月 星期 执行的程序
           # *     : 每分钟执行
           # 1-3   : 1 到 3分钟内执行
           # */3   : 每 3 分钟执行一次
           # 1-10/3: 1-10 分钟内, 每 3 分钟执行
           # 1,3,5 : 1,3,5 分钟执行
           # crontab 不会自动执行 .bashrc, 如果需要, 需要在脚本中手动执行
crontab -r # 删除任务表

[[ "$FLOCKER" != "$0" ]] && exec env FLOCKER="$0" flock -en "$0" "$0" "$@" || : -- 常用
                # 脚本内使用, 保证脚本最多执行一次
                # 解释:
                #   1. 第一次进入脚本, 由于变量未设置, 会执行 exec
                #   2. 调用 exec, 使用 env 设置 变量名
                #   3. 执行 flock, 重新执行这个脚本, 执行完脚本后会退出, 不会执行之后的命令
                #        * 使用脚本名作为 文件锁, 脚本名使用绝对路径, 所以不会重复
                #   4. 第二次进入脚本, 由于变量已设置, 直接往下执行就可以了
                # 5. 在此期间, 如果, 有其他脚本进入, 文件锁获取失败, 就直接退出了

env          # 设置环境变量, 然后执行程序

exec &>> 1.log  # 脚本内重定向
exec ls         # 替换当前 shell, 执行后不再执行之后的命令
exec &>  1.txt  # 打开文件描述符, 然后继续执行之后的命令

g++ -0g main.cc
g++ -01 main.cc
g++ -02 main.cc
g++ -03 main.cc
g++ -g  main.cc   # 生成 gdb 的文件

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
gdb> ptype	                 # 查看变量类型

kill         pid # 通过进程ID发送信号给进程或进程组
kill -signal pid # 指定信号，默认值为 SIGTERM
kill -l          # 列出所有信号

killall             # 通过进程名称发送信号给进程或进程组, 进程名称精确匹配
killall -l          # 列出所有信号
killall -o 2m a.out # 发给 2 分钟前启动的 a.out
killall -y 2m a.out # 发给 2 分钟内启动的 a.out
killall -w    a.out # 等待进程结束

                             # 多个命令之间取或
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

pstree     [PID] # 以进程 PID 为根画进程树, 默认为 1 -- 常用
pstree  -c [PID] # 展示所有子树
pstree  -p [PID] # 展示进程ID
pstree  -g [PID] # 展示进程组ID
pstree  -n [PID] # 使用 PID 排序而不是 进程名称
pstree  -l [PID] # 使用长行, 方便写入文件

              # 多个命令之间取且
pgrep         # 使用进程名称查找, 使用扩展的正则表达式
pgrep -f  ... # 使用启动命令匹配, 默认使用进程名称匹配(最多15位)
pgrep -c  ... # 输出匹配到的进程数目           -- 常用
pgrep -d，... # 设置输出的分割符，默认是换行符 -- 常用
pgrep -i  ... # 忽略大小写
pgrep -l  ... # 列出进程名称(最多15位)         -- 常用
pgrep -a  ... # 列出启动命令                   -- 常用
pgrep -n  ... # 仅列出最新的进程
pgrep -o  ... # 仅列出最旧的进程
pgrep -g  ... # 指定进程组ID
pgrep -G  ... # 指定实际组ID
pgrep -P  ... # 指定父进程ID
pgrep -s  ... # 指定会话ID
pgrep -t  ... # 指定终端
pgrep -u  ... # 指定有效用户ID
pgrep -U  ... # 指定实际用户ID
pgrep -v  ... # 反转结果
pgrep -x  ... # 精确匹配，默认不需要完全匹配
pgrep -w  ... # 列出线程ID

pidof    # 进程名称 => PID, 精确匹配, 没有长度限制

pkill         ... # 杀死进程, 扩展的正则表达式，参数和 pgrep 类似 -- 常用
pkill -signal ... # 指定信号，默认值为 SIGTERM

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
```

## 建议
* 使用 pgrep 获取 PID, 使用 ps 列出详细信息
* 使用 etimes 可以方便计算出启动时间, 并格式化 年-月-日 时-分-秒 时区
* 一般使用进程的前 15 位即可
* 使用 pkill 发送信号

