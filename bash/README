
## Bash 常用参数
* bash 文件名: 执行文件内的命令
* bash -c "ls": 将字符串的内容交由 bash 执行

## 重定向

## 定时任务: 只执行一次

## 定时任务: 周期新执行

## 解析命令行参数


## set


## 括号


## 字段分隔符


## touch 时间


## tree html


## 常用命令

## Bash 常用快捷键

Ctrl+A             # 将光标移到行首
Ctrl+B             # 将光标向左移动一个字符
Ctrl+C             # 向前台进程组发送 SIGINT, 默认终止进程
Ctrl+D             # 删除光标前的字符 或 产生 EOF 或 退出终端
Ctrl+E             # 将光标移到行尾
Ctrl+F             # 将光标向右移动一个字符
Ctrl+G             # 退出当前编辑
Ctrl+H             # 删除光标前的一个字符
Ctrl+K             # 删除光标处到行尾的字符
Ctrl+L             # 清屏
Ctrl+N             # 查看历史命令中的下一条命令
Ctrl+O             # 类似回车，但是会显示下一行历史
Ctrl+P             # 查看历史命令中的上一条命令
Ctrl+Q             # 解锁终端
Ctrl+R             # 历史命令反向搜索, 使用 Ctrl+G 退出搜索
Ctrl+S             # 锁定终端 或 历史命令正向搜索, 使用 Ctrl+G 退出搜索
Ctrl+T             # 交换前后两个字符
Ctrl+U             # 删除光标处到行首的字符
Ctrl+V                          # 输入字符字面量，先按 Ctrl+V 再按任意键 ?
Ctrl+W             # 删除光标左边的一个单词
Ctrl+X                          # 列出可能的补全 ?
Ctrl+Y             # 粘贴被删除的字符
Ctrl+Z             # 暂停前台进程返回 bash，需要时可用 fg 将其切换回前台
Ctrl+/             # 撤销之前的操作
Ctrl+\             # 产生 SIGQUIT, 默认杀死进程, 并生成 core 文件

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

!!                 # 执行上一条命令
!l                 # 执行最近使用的以 l 打头的命令
!l:p               # 输出最近使用的以 l 打头的命令
!num               # 执行历史命令列表的第 num 条命令
!$                 # 表示上一条命令的最后一个参数

Esc+.              # 获取上一条命令的最后的部分

v=(1 2 3)         # 定义数组
echo ${v[1]}      # 输出数组中指定元素的值
echo ${v[*]}      # 输出数组中所有元素的值
echo ${#v[*]}     # 输出数组中所有元素的个数
echo ${v[@]}      # 输出数组中所有元素的值
v=$[1+3]          # 定义变量，包括数学运算
ls -l `which ls`    # 命令替换，首先执行 which ls
ls -l $(which ls)   # 命令替换，首先执行 which ls
ls -l "$(which ls)" # 命令替换，首先执行 which ls, 保留换行符

declare -A v=(["a"]="a" ["b"]="b") # map
v[a]=a
v[b]=b

${v[*]}  # 获取值
${v[@]}
${!v[*]} # 获取 key
${!v[@]}
${#v[*]}  # 获取长度
${#v[@]}

length=${#val}    # 输出字符串的长度
${val:起始位置:长度} # 获取字串

${var}   # 取变量的值
$[1+2]   # 计算
$(ls -l) # 命令替换

IFS=$'\n' # 将字段分割符改成 '\n'
IFS=:     # 将字段分割符改成 :

问号（?）代表一个字符；
星号（*）代表零个或多个字符。
[123]
[1-5]
[!a]

  ()        # 子 shell, 初始化数组
 $()        # 变量替换, 返回变量执行的结果
 <()        # 将命令 或 函数的输出做为 文件, 命令要有打开 文件 的动作
 (())       # 数字表达式求值, 返回 0 或 1
$(())       # 数字表达式求值, 返回 求值的结果
[[]]        # 字符串 处理
{1..10..2}  # 获取字符序列
${}         # 获取变量的值

Esc+.              # 获取上一条命令的最后的部分

ls -l  $(which ls)  # 命令替换
ls -l "$(which ls)" # 命令替换, 保留换行符

v=(1 2 3)           # 定义数组
declare -A v        # 定义字典
v[a]=a
v[b]=b

${v[@]}  # 获取所有元素的值
${!v[@]} # 获取所有的 key
${#v[@]} # 获取元素个数

length=${#val}       # 输出字符串的长度
${val:起始位置:长度} # 获取字串

${var}          # 取变量的值
${var:-word}    # 如果 var 存在, 且不为空, 返回 var 的值, 否则, 返回 word
${var:=word}    # 如果 var 存在, 且不为空, 返回 var 的值, 否则, 设置 var=word, 然后返回 word
${var:+word}    # 如果 var 存在, 且不为空, 则返回 word 的值, 否则, 返回 空
${var:?message} # 如果 var 存在, 且不为空, 返回 var 的值, 否则, 返回 输出 message, 并退出

IFS=$'\n' # 将字段分割符改成 '\n'
IFS=:     # 将字段分割符改成 :

lyb=123.456.txt
lyb=${lyb%.*}  # 后缀非贪婪匹配, lyb 为 123.456
lyb=${lyb%%.*} # 后缀  贪婪匹配, lyb 为 123
lyb=${lyb#*.}  # 前缀非贪婪匹配, lyb 为 txt
lyb=${lyb##*.} # 前缀  贪婪匹配, lyb 为 456.txt

问号（?）代表一个字符
星号（*）代表零个或多个字符
[123]
[1-5]
[!a]

 >   1.txt  # 将标准输出重定向到文件
1>   1.txt  # 将标准输出重定向到文件
2>   1.txt  # 将标准错误重定向到文件
2>&1 1.txt  # 将标准输出和标准错误重定向到文件
&>   1.txt  # 将标准输出和标准错误重定向到文件

\command # 忽略别名


$0 脚本名称
$1 第一个参数
$* 所有参数拼成一个字符串
$@ 参数序列
$# 参数个数

## Linux 常用命令

apt show    vim # 列出软件包的信息
apt install vim # 安装软件包
apt remove  vim # 卸载软件包
apt purge   vim # 卸载软件包, 删除数据和配置文件
apt update      # 更新软件源
apt upgrade     # 更新软件

source .bashrc # 当前 shell 执行, 变量等会影响当前 shell
./bin.sh       # 在子 shell 中执行, 变量等不会影响当前 shell
exec ls        # 替换当前 shell, 执行后不再执行之后的命令
exec 3<>1.txt  # 生成文件描述符, 会继续执行之后的命令

env # 设置环境变量, 然后执行程序

bc              #
scale=2         # 设置使用两位小数
ibase=2         # 输入使用二进制
obase=2         # 输出使用二进制

chmod u=rwx g=rw o=r filename # 修改文件权限
chmod a+x filename
chmod  +x filename
chmod  -x filename
chmod 777 filename
chmod a+t directory_name  # 设置粘滞位, 只有目录的所有者才能够删除目录中的文件
chmod +s executable_file  # 设置 setuid权限, 允许其他用户以文件所有者的身份来执行文件

chown lyb:lyb  filename # 修改文件所属的用户和组

chattr +i file # 设置文件不可修改
chattr -i file # 取消文件不可修改的属性

docker run ubuntu:15.10    /bin/echo "Hello world"  # 启动 docker 并执行命令 echo
docker run ubuntu:15.10 -i /bin/echo "Hello world"  # 
docker run ubuntu:15.10 -t  /bin/bash               # 这个感觉没啥用, 不会回写输出到本机上
docker run ubuntu:15.10 -it /bin/bash               # 使用交互式终端
docker run ubuntu:15.10 -i /bin/bash                # 使用交互式终端
docker run ubuntu:15.10 -it /bin/bash               # 使用交互式终端
docker run ubuntu:15.10 -d                          # 使用后台模式, 返回容器 ID
docker run ubuntu:15.10 -d --name "lyb"             # 给 docker 起一个名字
docker run ubuntu:15.10 -d --net=host               # 主机和 docker 共享 IP 和 端口号
docker run ubuntu:15.10 -d -P                       # docke 内使用随机端口映射主机端口
docker run ubuntu:15.10 -d -p 2000:3000             # 将本机的端口号 2000 绑定到docker 的 3000
docker run ubuntu:15.10 -d -v /home/123:/home/456   # 将本机目录 /home/123 绑定到 docker 的 /home/456

docker port     容器ID                              # 查看端口号映射
docker ps                                           # 列出当前运行的容器
docker ps -a                                        # 列出所有容器
docker logs     容器ID                              # 查看容器的输出
docker start    容器ID                              # 启动容器
docker stop     容器ID                              # 停止容器
docker restart  容器ID                              # 重新启动容器
docker rm -f    容器ID                              # 删除容器
docker attach   容器ID                              # 进入在后台运行的容器
docker exec -it 容器ID /bin/bash                    # 对于在后台运行的容器, 开启交互式终端, 终端退出, docker 不会终止
docker exec     容器ID ls                           # 对于在后台运行的容器, 执行命令
 
echo       "123"    # 输出 123, 然后换行
echo    -n "123"    # 输出 123
echo -e -n "123\n"  # 输出 123,然后换行, 换行由字符串内的 \n 产生

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

comm 1.txt 2.txt       | tr -d '\t' # 求两个文件的全集
comm 1.txt 2.txt -1 -2 | tr -d '\t' # 求两个文件的交集
comm 1.txt 2.txt -1 -2              # 同上
comm 1.txt 2.txt -3    | tr -d '\t' # 求不同时出现在两个文件中的部分
comm 1.txt 2.txt -1 -3              # B - A
comm 1.txt 2.txt -2 -3              # A - B

crontab -l # 查询任务表
crontab -e # 编辑任务表
crontab -r # 删除任务表
f1 f2 f3 f4 f5 exe # 分别表示 分钟(0-59), 小时(0-23), 日(1-31),
                   #          月(1-12), 星期几(0-6, 星期天为 0), 执行的程序
                   # * 表示每分钟等都执行
                   # 1-3 表示 1 到 3分钟内执行
                   # */3 表示每 3 分钟执行一次
                   # 1-10/3 表示 1-10 分钟内, 每 3 分钟执行一次
                   # 1,3,5 表示 1,3,5 分钟执行

curl -I ... # 只打印头部信息

cut -f 1,2  # 按列切割
cut -d ":"  # 设置分割符

date -s "20200202 10:10:10" # 更新系统时间, 需要 root 权限
date "+%Y-%m-%d %H:%M:%S"   # 指定输出的格式, 年-月-日 时-分-秒
date "+%F %T"               # 同上
date "+%Y-%m-%d %H:%M"      # 指定输出的格式, 年-月-日 时-分
date "+%F %R"               # 同上
date "+%s"                  # 使用纪元
date -d "20200202 01:01:01" # 指定输入日期

ntpdate -s time-b.nist.gov # 使用时间服务器更新时间

diff    1.txt 2.txt              # 比较两个文件的不同
diff -u 1.txt 2.txt              # 一体化输出, 比较两个文件的不同
diff    1.txt 2.txt > diff.pathc
patch   1.txt diff.pathc         # 恢复文件 2.txt

dpkg -L vim        # 列出 vim 软件包安装的全部文件
dpkg --search /... # 查看该文件是哪个软件包安装的, 使用绝对路径

df -Th # 所挂载的系统的使用情况
du -sh # 某一目录的使用大小

find . -name  lyb                     # 以文件名 或 通配符 查找文件
find . -iname lyb                     # 以文件名 或 通配符 查找文件, 忽略大小写
find . -regex ".*p+"                  # 以文件名 或 正则表达式 查找文件, 忽略大小写
find . -type  f                       # 以类型查找文件
find . \( -type f -and -name lyb \)   # 且, 多个条件必须同时成立
find . \( -type f -a   -name lyb \)   # 同上
find .    -type f      -name lyb      # 同上
find . \( -type f -or  -name lyb \)   # 或, 多个条件成立一个即可
find . \( -type f -o   -name lyb \)   # 同上
find . ! -type f -o   -name lyb       # ! 只否定最近的条件
find . -name '.git' -prune -o -type f # 忽略 .git 目录

firewall-cmd --zone=public --list-ports                       查看所有打开的端口
firewall-cmd --zone=public --get-services                     查看所有的服务
firewall-cmd --zone=public --permanent --add-service=http     添加服务, 永久生效
firewall-cmd --zone=public --permanent --add-service=https    添加服务, 永久生效
firewall-cmd --zone=public             --add-service=https    添加服务
firewall-cmd --zone=public             --remove-service=http  移除服务
firewall-cmd --zone=public --permanent --add-port=8080/tcp    添加端口, 永久生效
firewall-cmd --zone=public             --add-port=8080/tcp    添加端口
firewall-cmd --zone=public             --remove-port=8080/tcp 移除端口
firewall-cmd --reload                                         重新加载配置

flock    123.txt ls # 使用 123.txt 设置文件互斥锁 并执行命令, 如果获取锁失败, 将等待
flock -n 123.txt ls # 使用 123.txt 设置文件互斥锁 并执行命令, 如果获取锁失败, 将退出
flock -e 123.txt ls # 使用 123.txt 设置文件共享锁 并执行命令, 默认为互斥锁

gcc -0g main.cc
gcc -01 main.cc
gcc -02 main.cc
gcc -03 main.cc

grep -v          # 输出不匹配的内容
grep -c          # 输出匹配的行的次数
grep -o          # 只输出匹配的内容
grep -n          # 输出匹配的行号
grep -l          # 输出匹配的文件
grep -i          # 忽略大小写
grep -h          # 不输出文件名
grep -q          # 静默输出
grep -A 5        # 输出之前的行
grep -B 5        # 输出之后的行
grep -C 5        # 输出之前之后的行
grep -e .. -e .. # 多个模式取或
grep ... --inclue "*.c" # 指定文件
grep ... --exclue "*.c" # 忽略文件
grep ... --exclue src   # 忽略目录

ln -s target symbolic_link_name # 创捷符号链接
readlink symbolic_link_name     # 读取符号链接

ls     # 列出当前目录中的元素
ls -a  # 列出当前目录中的元素（包括隐藏的文件）
ls -l  # 列出当前目录中的元素的详细信息
ls -F  # 在目录后添加 /，在可执行文件后添加 *
ls -d  # 只列出目录本身，而不列出目录内元素
ls -r  # 逆序列出当前目录中的元素
ls -R  # 递归列出当前目录中的元素
ls -1  # 在每一行列出文件名

lsof               # sudo yum install lsof
lsof -iTCP         # 查看 TCP 信息
lsof -i :22        # 查看指定 端口号 的信息
lsof -i@1.2.3.4:22 # 查看是否连接到指定 IP 和 端口号上
lsof -p 1234       # 查看 进程 1234 打开的文件信息
lsof -t            # 仅获取进程ID


pgrep vim         # 列出 使用 vim 的进程号
pgrep vim  -l     # 列出 使用 vim 的进程号和进程名称
pgrep vim  -a     # 列出 使用 vim 的进程号和全路径的完整的进程名称
pgrep vim  -f     # 只要完整进程路径匹配到即可, 而不是进程名的前缀匹配
pgrep vim  -u lyb # 列出有效用户ID 是 lyb 的进程 ID
pgrep vim  -U lyb # 列出真正用户ID 是 lyb 的进程 ID

ps -ef                  # 显示所有进程的详细信息
ps -o pid,ppid,command  # 按指定格式显示进程的信息
ps -f 123               # 显示指定进程的信息

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

tee    1.txt # 管道中把文件拷贝到文件
tee -a 1.txt # 管道中把文件添加到文件

tr    'a-z' 'A-Z' # 小写转大写
tr -d 'a-z'       # 删除字符
tr -s ' '         # 压缩字符

sort       # 排序
sort -k 4  # 指定排序的列字段
sort -t :  # 指定列的分割符
sort -n    # 以数字进行排序
sort -r    # 逆序
sort -f    # 忽略大小写
sort -u    # 重复项只输出一次
sort lyb -o lyb # 排序并存入原文件

#ssh
ssh -D # TODO
ssh -L # TODO
ssh -N # TODO
ssh -R # TODO
ssh -X # TODO
ssh -p port
ssh -q             # 不输出任何警告信息
ssh -l lyb 1.2.3.4
ssh     1.2.3.4
ssh lyb@1.2.3.4
ssh -i ~/.ssh/id_rsa lyb # 指定私钥文件名

## 配置: ~/.ssh/config
Host *
    Port 2222

Host 123
    HostName 1.2.3.4
    User lyb
    Port 2222
    IdentityFile ~/.ssh/id.rsa # 密钥文件

使用 ssh 123 相当于使用 ssh -p 2222 lyb@1.2.3.4

## 免密码登录
* ssh-keygen -t rsa # 生成密钥对, 一路回车即可
* 将生成的公钥 ~/.ssh/id_rsa.pub 添加到服务器的文件中 ~/.ssh/authorized_keys
* 可使用 ssh-copy-id -i 公钥文件 lyb@1.2.3.4 添加公钥到服务器中

systemctl start      nginx   启动 nginx
systemctl stop       nginx   停止 nginx
systemctl restart    nginx   重启 nginx
systemctl status     nginx   查看 nginx 状态
systemctl enable     nginx   开机自动启动 nginx
systemctl disable    nginx   开机禁止启动 nginx
systemctl is-active  nginx   查看 nginx 是否已启动
systemctl is-enabled nginx   查看 nginx 是否开机启动
systemctl list-unit-files    列出所有可用单元

uniq    # 删除重复的行
uniq -c # 输出统计的次数
uniq -d # 只输出重复的行, 重复的项只输出一次
uniq -D # 只输出重复的行, 重复的项只输出多次
uniq -i # 忽略大小写
uniq -u # 只输出没重复的行

sed    "s/123/456/g"        1.txt
sed -i "s/123/456/g"        1.txt   # 直接在原文件上修改
sed -i "s|123|456|g"        1.txt   # 使用不同的分割符
sed -i "/^$/d"              1.txt   # 删除空行
sed -i "s/.*/[&]/g"         1.txt   # & 用于表示所匹配到的内容
sed -i "s/\([0-9]*\).*/\1/g" 1.txt  # \1 表示第一个字串
sed -i "s/\([0-9]\+\).*/\1/g" 1.txt # \1 表示第一个字串, 为什么 + 要转义 * 不用

awk 'BEGIN{ print "start" } pattern { commands } END{ print "end" }' file
* BEGIN 和 END 都是可选的
* print 以逗号分割
* NR 当前行号
*NF 字段数量
* $0 当前记录的内容
*$1 第一个字段的内容
*$2 第二个字段的内容
* getline 读取一行
* ls | getline 从命令中读取
* -F: 或 FS=":" 或 OFS=":" # 设置分割符
awk 'NR < 5'      # 行号小于5的行
awk 'NR==1,NR==4' # 行号在 1 到 5 之间的行
awk '/linux/'     # 包含模式为linux的行
awk '!/linux/'    # 不包含模式为linux的行
awk -v lyb=$SHELL ... # 将外部变量的值传给 awk
awk ..... lyb=$SHELL  # 将外部变量的值传给 awk
awk '/start_pattern/, /end_pattern/' filename

su              # 切换 root, 输入 root 密码
su root         # 同 su
su -            # 切换 root, 更新主目录, 环境变量等等
su -l           # 同 su -
su - root       # 同 su -
su - root -c ls # 使用 root 执行命令 ls

sudo                                                 # 权限管理文件: /etc/sudoers, 使用 visudo 编辑
                                                     # 使用当前用户的密码
sudo -u USERNAME COMMAND                             # 指定用户执行命令
echo "654321" | sudo -S date -s "20210722 10:10:10"  # 脚本中免密码使用

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

#### Linux 的三个特殊权限
set-user-ID  (SUID) # 可执行文件执行时将拥有程序所有者的权限
set-group-ID (SGID) # 可执行文件执行时将拥有程序所属的组的权限
sticky              # 此目录下的文件只有文件作者 或 root 可以删除

#### 查看 Linux 端口号的范围
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


## Linux 常用命令

apt show    vim # 列出软件包的信息
apt install vim # 安装软件包
apt remove  vim # 卸载软件包
apt purge   vim # 卸载软件包, 删除数据和配置文件
apt update      # 更新软件源
apt upgrade     # 更新软件

bc              #
scale=2         # 设置使用两位小数
ibase=2         # 输入使用二进制
obase=2         # 输出使用二进制

echo       "123"    # 输出 123, 然后换行
echo    -n "123"    # 输出 123
echo -e -n "123\n"  # 输出 123,然后换行, 换行由字符串内的 \n 产生

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

comm 1.txt 2.txt       | tr -d '\t' # 求两个文件的全集
comm 1.txt 2.txt -1 -2 | tr -d '\t' # 求两个文件的交集
comm 1.txt 2.txt -1 -2              # 同上
comm 1.txt 2.txt -3    | tr -d '\t' # 求不同时出现在两个文件中的部分
comm 1.txt 2.txt -1 -3              # B - A
comm 1.txt 2.txt -2 -3              # A - B

cut -f 1,2  # 按列切割
cut -d ":"  # 设置分割符

date -s "20200202 10:10:10" # 更新系统时间, 需要 root 权限
date "+%Y-%m-%d %H:%M:%S"   # 指定输出的格式, 年-月-日 时-分-秒
date "+%F %T"               # 同上
date "+%Y-%m-%d %H:%M"      # 指定输出的格式, 年-月-日 时-分
date "+%F %R"               # 同上
date "+%s"                  # 使用纪元
date -d "20200202 01:01:01" # 指定输入日期

ntpdate -s time-b.nist.gov # 使用时间服务器更新时间

diff    1.txt 2.txt              # 比较两个文件的不同
diff -u 1.txt 2.txt              # 一体化输出, 比较两个文件的不同
diff    1.txt 2.txt > diff.pathc
patch   1.txt diff.pathc         # 恢复文件 2.txt

dpkg -L vim        # 列出 vim 软件包安装的全部文件
dpkg --search /... # 查看该文件是哪个软件包安装的, 使用绝对路径

df -Th # 所挂载的系统的使用情况
du -sh # 某一目录的使用大小

find . -name  lyb                     # 以文件名 或 通配符 查找文件
find . -iname lyb                     # 以文件名 或 通配符 查找文件, 忽略大小写
find . -regex ".*p+"                  # 以文件名 或 正则表达式 查找文件, 忽略大小写
find . -type  f                       # 以类型查找文件
find . \( -type f -and -name lyb \)   # 且, 多个条件必须同时成立
find . \( -type f -a   -name lyb \)   # 同上
find .    -type f      -name lyb      # 同上
find . \( -type f -or  -name lyb \)   # 或, 多个条件成立一个即可
find . \( -type f -o   -name lyb \)   # 同上
find . ! -type f -o   -name lyb       # ! 只否定最近的条件
find . -name '.git' -prune -o -type f # 忽略 .git 目录

firewall-cmd --zone=public --list-ports                       查看所有打开的端口
firewall-cmd --zone=public --get-services                     查看所有的服务
firewall-cmd --zone=public --permanent --add-service=http     添加服务, 永久生效
firewall-cmd --zone=public --permanent --add-service=https    添加服务, 永久生效
firewall-cmd --zone=public             --add-service=https    添加服务
firewall-cmd --zone=public             --remove-service=http  移除服务
firewall-cmd --zone=public --permanent --add-port=8080/tcp    添加端口, 永久生效
firewall-cmd --zone=public             --add-port=8080/tcp    添加端口
firewall-cmd --zone=public             --remove-port=8080/tcp 移除端口
firewall-cmd --reload                                         重新加载配置

gcc -0g main.cc
gcc -01 main.cc
gcc -02 main.cc
gcc -03 main.cc

grep -v          # 输出不匹配的内容
grep -c          # 输出匹配的行的次数
grep -o          # 只输出匹配的内容
grep -n          # 输出匹配的行号
grep -l          # 输出匹配的文件
grep -i          # 忽略大小写
grep -h          # 不输出文件名
grep -q          # 静默输出
grep -A 5        # 输出之前的行
grep -B 5        # 输出之后的行
grep -C 5        # 输出之前之后的行
grep -e .. -e .. # 多个模式取或

ls     # 列出当前目录中的元素
ls -a  # 列出当前目录中的元素（包括隐藏的文件）
ls -l  # 列出当前目录中的元素的详细信息
ls -F  # 在目录后添加 /，在可执行文件后添加 *
ls -d  # 只列出目录本身，而不列出目录内元素
ls -r  # 逆序列出当前目录中的元素
ls -R  # 递归列出当前目录中的元素
ls -1  # 在每一行列出文件名

lsof               # sudo yum install lsof
lsof -iTCP         # 查看 TCP 信息
lsof -i :22        # 查看指定 端口号 的信息
lsof -i@1.2.3.4:22 # 查看是否连接到指定 IP 和 端口号上
lsof -p 1234       # 查看 进程 1234 打开的文件信息
lsof -t            # 仅获取进程ID


pgrep vim         # 列出 使用 vim 的进程号
pgrep vim  -l     # 列出 使用 vim 的进程号和进程名称
pgrep vim  -a     # 列出 使用 vim 的进程号和全路径的完整的进程名称
pgrep vim  -f     # 只要完整进程路径匹配到即可, 而不是进程名的前缀匹配
pgrep vim  -u lyb # 列出有效用户ID 是 lyb 的进程 ID
pgrep vim  -U lyb # 列出真正用户ID 是 lyb 的进程 ID

ps -ef                  # 显示所有进程的详细信息
ps -o pid,ppid,command  # 按指定格式显示进程的信息
ps -f 123               # 显示指定进程的信息

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

tee    1.txt # 管道中把文件拷贝到文件
tee -a 1.txt # 管道中把文件添加到文件

tr    'a-z' 'A-Z' # 小写转大写
tr -d 'a-z'       # 删除字符
tr -s ' '         # 压缩字符

sort       # 排序
sort -k 4  # 指定排序的列字段
sort -t :  # 指定列的分割符
sort -n    # 以数字进行排序
sort -r    # 逆序
sort -f    # 忽略大小写
sort -u    # 重复项只输出一次
sort lyb -o lyb # 排序并存入原文件

systemctl start      nginx   启动 nginx
systemctl stop       nginx   停止 nginx
systemctl restart    nginx   重启 nginx
systemctl status     nginx   查看 nginx 状态
systemctl enable     nginx   开机自动启动 nginx
systemctl disable    nginx   开机禁止启动 nginx
systemctl is-active  nginx   查看 nginx 是否已启动
systemctl is-enabled nginx   查看 nginx 是否开机启动
systemctl list-unit-files    列出所有可用单元

uniq    # 删除重复的行
uniq -c # 输出统计的次数
uniq -d # 只输出重复的行, 重复的项只输出一次
uniq -D # 只输出重复的行, 重复的项只输出多次
uniq -i # 忽略大小写
uniq -u # 只输出没重复的行

sed    "s/123/456/g"        1.txt
sed -i "s/123/456/g"        1.txt   # 直接在原文件上修改
sed -i "s|123|456|g"        1.txt   # 使用不同的分割符
sed -i "/^$/d"              1.txt   # 删除空行
sed -i "s/.*/[&]/g"         1.txt   # & 用于表示所匹配到的内容
sed -i "s/\([0-9]*\).*/\1/g" 1.txt  # \1 表示第一个字串
sed -i "s/\([0-9]\+\).*/\1/g" 1.txt # \1 表示第一个字串, 为什么 + 要转义 * 不用

su              # 切换 root, 输入 root 密码
su root         # 同 su
su -            # 切换 root, 更新主目录, 环境变量等等
su -l           # 同 su -
su - root       # 同 su -
su - root -c ls # 使用 root 执行命令 ls

sudo                                                 # 权限管理文件: /etc/sudoers, 使用 visudo 编辑
                                                     # 使用当前用户的密码
sudo -u USERNAME COMMAND                             # 指定用户执行命令
echo "654321" | sudo -S date -s "20210722 10:10:10"  # 脚本中免密码使用

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

#### Linux 的三个特殊权限
set-user-ID  (SUID) # 可执行文件执行时将拥有程序所有者的权限
set-group-ID (SGID) # 可执行文件执行时将拥有程序所属的组的权限
sticky              # 此目录下的文件只有文件作者 或 root 可以删除

#### 查看 Linux 端口号的范围
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

