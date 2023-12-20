
## 最佳实践
1. 文件名称建议: 由大小写字母 数字 短横线(-) 下横线(_) 点(.) 构成
2. 明确是目录的时候, 添加斜杠, 以避免出现目录不存在的情况造成歧义

## 常见命令
```
bc <<< "scale=2; 10/2" # 使用两位小数,   输出: 5.00
bc <<< "ibase=2;  100" # 输入使用二进制, 输出: 4
bc <<< "obase=2;   10" # 输出使用二进制, 输出: 1010

cat    1.txt      # 输出 1.txt 的内容
cat -n 1.txt      # 显示行号
cat -b 1.txt      # 显示行号, 行号不包括空行
cat -s 1.txt      # 去掉多余的连续的空行
cat -T 1.txt      # 显示 TAB

tac               # 最后一行 => 第一行

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

basename ... # 获取文件名
dirname  ... # 获取目录名

cut                        -b 2   1.c # 按字节切割, 输出第 2 个字节
cut                        -c 2-  1.c # 按字符切割, 输出 [2, 末尾] 字符
cut                        -f 2-5 1.c # 按列切割,   输出 [2,5] 列                               -- 常用
cut -d STR                 -f 2,5 1.c # 设置输入字段的分隔符, 默认为 TAB, 输出 第 2 列和第 5 列 -- 常用
cut -s                     -f  -5 1.c # 不输出不包含字段分隔符的列, 输出 [开头, 5] 的列
cut --output-delimiter=STR -f  -5 1.c # 设置输出的字段分隔符, 默认使用输入的字段分隔符

df   -Th                # 查看磁盘挂载情况

du                      # 列出目录大小
du -0                   # 输出以 \0 分割, 默认是换行符
du -a                   # 列出目录和文件大小
du -d 1                 # 最大目录深度
du -sh                  # 只列出整体使用大小
du --exclude="*.txt"    # 忽略指定文件, 支持通配符

free -h                 # 内存使用情况

diff    1.txt 2.txt # 比较两个文件的不同
diff -u 1.txt 2.txt # 一体化输出, 比较两个文件的不同

dd if=/dev/zero of=junk.data bs=1M count=1
dd if=/dev/zero bs=1M count=1000 | nc 127.0.0.1 9999 # 测速-客户端

dos2unix 1.txt
unix2dos 1.txt

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
find . -empty                         # 查找空文件

getopts # 处理参数, -- 表示可选参数的终止

grep -v                   # 输出不匹配的内容
grep -c                   # 输出匹配的行的次数, 同一行只输出一次
grep -o                   # 只输出匹配的内容
grep -n                   # 输出匹配的行号
grep -l                   # 输出匹配的文件
grep -f                   # 从文件中读取匹配模式
grep -i                   # 忽略大小写
grep -I                   # 跳过二进制文件
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

iconv -f gbk -t utf-8 1.txt -o 1.txt

less # 空格   : 下一页
     # ctrl+F : 下一页
     # b      : 上一页
     # ctrl+b : 上一页
     # 回车   : 下一行
     # =      : 当前行号
     # y      : 上一行

ln -s 1.cc 1.cc.link --- 创建符号链接

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

mkdir    abc   # 创建单层目录, 存在时报错
mkdir -p a/b/c # 递归创建目录, 存在时不报错

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

paste # 按列合并文件

patch     1.txt diff.pathc  # 恢复文件
patch -p1 1.txt diff.pathc  # 恢复文件, 忽略 diff.pathc 的第一个路径

read name     # 读取, 如果参数值小于字段数, 多余的值放入最后一个字段

readlink    1.c.link  # 读取符号链接
readlink -f 1.c.link  # 读取符号链接, 递归

rm -r  a    # 递归删除
rm -rf a    # 强行删除, 文件不存在时, 忽略

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

split          # 分割文件
csplit         # 分割文件

sz          #  虚拟机  向 windows 发送数据

tail -f * # 动态查看新增内容

tee    1.txt # 管道中把文件拷贝到文件
tee -a 1.txt # 管道中把文件添加到文件

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

tree -p "*.cc"       # 只显示  匹配到的文件
tree -I "*.cc"       # 只显示没匹配到的文件
tree -H . -o 1.html  # 指定目录生成 html 文件

uniq    # 删除重复的行
uniq -c # 输出统计的次数
uniq -d # 只输出重复的行, 重复的项只输出一次
uniq -D # 只输出重复的行, 重复的项输出多次
uniq -i # 忽略大小写
uniq -u # 只输出没重复的行

cat lyb | xargs -i vim {} # 以此编辑 lyb 中的每一个文件
                -I ...    # 指定替换使用的字符串
                -d ...    # 指定输入分割符
                -n 3      # 指定每次使用的参数的个数

uname -a # 全部信息
uname -m # x86_64 等
uname -r # 内核版本

uptime -s # 列出系统启动时间
```

## 网络相关的命令
```
netstat -i  # 网络接口的信息
netstat -in # 网络接口的信息, 使用数字
netstat -rn # 路由表

route    -n  # 路由表

ss       # 显示已连接的 UDP, TCP, unix domain sockets
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

                   # lsof -- sudo yum install lsof
lsof -iTCP         # 查看 TCP 信息
lsof -i :22        # 查看指定 端口号 的信息 -- 常用
lsof -i@1.2.3.4:22 # 查看是否连接到指定 IP 和 端口号上
lsof -p 1234       # 指定 进程号
lsof -d 0,1,2,3    # 指定 文件描述符
lsof -t            # 仅获取进程ID

ip a                                 # 显示网卡信息
ip addr    show                      # 显示指定网卡信息
ip address show dev   lo             # 显示指定网卡信息
ip address add 192.268.1.10 dev eth0 # 添加 IP 地址
ip address del 192.268.1.10 dev eth0 # 删除 IP 地址

ifconfig                                         # 查看网卡信息
ifconfig ens33 192.168.1.1                       # 设置 IP
ifconfig ens33 192.168.1.1 netmask 255.255.252.0 # 设置 IP 和子网掩码
ifconfig ens33 hw ether ...                      # 设置硬件地址

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

wget ... -O ...                    # 指定文件名称
wget ... -o ...                    # 指定日志文件
wget ... -c                        # 断点续传
wget ... -t ...                    # 指定重试的次数
wget ... -t 0                      # 不停重试
wget ... --mirror --convert-links  # 镜像下载, 递归, 并转换为本地 url
wget ... --user ... --password ... # 指定用户名和密码
wget ... --limit-rate ...          # 限制下载速度
wget ... --quota      ...          # 限制最大下载量

curl ...                    # 下载到标准输出
curl ... -O                 # 下载到文件, 文件名称从 url 中获取
curl ... -o ...             # 下载到文件
curl ... --silent           # 不显示进度信息
curl ... -C -               # 断点续传
curl ... --referer ...      # 表明客户端是从哪儿跳过来的
curl ... --cookie  ...      # 指明 cookie
curl ... --cookie-jar ...   # 指明 cookie, 使用文件
curl ... --user-agent ...   # 指明用户的客户端
curl ... -H ...             # 指明请求头部信息
curl ... -d ...             # 发送post请求
curl ... --limit-rate ...   # 限制下载速度
curl ... --max-filesize ... # 限制最大下载量
curl ... -u user:pass       # 指定用户名和密码
curl ... -I                 # 只打印 http 头部信息
curl ... --head             # 只打印 http 头部信息

ping      www.bing.com #
ping -c 3 www.bing.com # 设置测试的次数
ping -i 3 www.bing.com # 设置间隔的秒数
ping -I 3 www.bing.com # 设置发送的接口, 自身的 IP
ping -w 3 www.bing.com # 设置耗时的上限
ping -t 3 www.bing.com # 设置使用的 TTL 大小
ping -f   www.bing.com # 高速率极限测试, 需要 root 权限
ping -r   www.bing.com # 跳过路由表

traceroute ... # 查看数据包经过的路径

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

systemctl start      nginx   # 启动 nginx
systemctl stop       nginx   # 停止 nginx
systemctl restart    nginx   # 重启 nginx
systemctl status     nginx   # 查看 nginx 状态
systemctl enable     nginx   # 开机自动启动 nginx
systemctl disable    nginx   # 开机禁止启动 nginx
systemctl is-active  nginx   # 查看 nginx 是否启动成功
systemctl is-failed  nginx   # 查看 nginx 是否启动失败
systemctl is-enabled nginx   # 查看 nginx 是否开机启动

host     ...       #
nslookup baidu.com # 查询 域名 对应 的 IP

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
```

