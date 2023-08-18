
# 计算机语言-Bash
## 简介
* Bash 是脚本, 一门编程语言

## 特殊字符 -- 要使用原字符必须转义
```
* 没引号包含
    * {} # 变量分割符 或 块语句
    * [] # 通配符 或 数字计算等等
    * () # 子shell
    * $  # 读取变量, 无值时默认忽略
    * !  # 一些快捷的方式获取命令或参数
    * ;  # 命令的分割符
    * #  # 注释
    * -  # 字符串以 - 开头表示是可选参数
    * -- # 后面的字符串都不是可选参数
    * '  # 单引号
    * "  # 双引号
    * &  # 后台运行
* 单引号包含:
    * '  # 单引号, 需要在字符串开头加上 $ 符号
* 双引号包含:
    * $  # 读取变量, 无值时默认忽略
    * !  # 一些快捷的方式获取命令或参数
    * "  # 双引号
```

## 特殊变量
```
$HOME  # 主目录
$IPS   # 默认分隔符, 默认为: " \t\n", 包含转义字符时, 需要在开头添加 $, IFS=$'\n'
$PATH  # 命令路径
$PS1   # 提示符
$PWD   # 当前工作目录
$SHELL # 当前 shell
$?     # 上一命令执行是否成功
$$     # shell ID
$_     # 上一命令的最后一个参数
$!     # 后台最后一个进程的进程 ID
$0     # shell 名称
$-     # shell 启动参数
```

## 字符串(包括数字)
```
v=...   #   解析变量和转义字符
v="..." #   解析变量和转义字符
v='...' # 不解析变量和转义字符
v="...
...
"       # 字符串跨行
v='...
...
'       # 字符串跨行

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
```

## 索引数组
```
* v=(1 2 3)  # 初始化数组, 以空字符分割多个元素
* ${v[1]}    # 数组中指定元素的值
* ${v[-1]}   # 数组中最后一个元素的值
* ${v[@]}    # 数组中所有元素的值, "1" "2" "3"
* ${#v[@]}   # 数组中元素的个数
* ${!v[@]}   # 获取所有的 key
* v+=(1 2 3) # 添加数组元素
```

## 关联数组
```
* declare -A v # 声明
* v[a]=a       # 赋值
* v[-1]=b      # 以 -1 作为 key
               # 其他同索引数组
```

## 模拟命令的标准输入
```
解释变量
cat << EOF
    $lyb
EOF

解释变量
cat << "EOF"
    $lyb
EOF

不解释变量
cat << 'EOF'
    $lyb
EOF

cat <<<  $lyb  #   解释变量
cat <<< "$lyb" #   解释变量
cat <<< '$lyb' # 不解释变量
```

## 括号 -- 只列举常用的情况
```
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
    * [[ "111" =~ 1{1,3} ]] # 扩展的正则表达式匹配
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
```

## 脚本
```
$0 # 脚本名称
$1 # 第一个参数
$@ # 参数序列
$# # 参数个数

if for while

function

函数内建议使用 local 局部变量, 声明和使用放到不同的行
```

测试文件: [301-01.sh](./301-01.sh)

## 通配符
```
* ~           # 用户主目录
* ~lyb        # 用户 lyb 的主目录, 匹配失败的话, 不扩展
* ~+          # 当前目录
* ?           # 任意单个字符, 匹配失败的话, 不扩展
* *           # 任意多个字符, 匹配失败的话, 不扩展
* [123]       # [1,3] 中任意一个, 匹配失败的话, 不扩展
* [1-5]       # [1,5] 中任意一个, 匹配失败的话, 不扩展
* [!a]        # 非 a, 匹配失败的话, 不扩展
* [^a]        # 非 a, 匹配失败的话, 不扩展
* {1,2,3}     # [1,3] 匹配失败, 也会扩展
* {,1}        # 空 或 1, 匹配失败, 也会扩展
* {1..10}     # 匹配失败, 也会扩展
* {01..10}    # 匹配失败, 也会扩展(保证两位数)
* {1..10..3}  # 匹配失败, 也会扩展
```

## 常用快捷键
```
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
```

## 常用命令
```
!!    # 上一条命令
!l    # 执行最近使用的以 l 打头的命令
!l:p  # 输出最近使用的以 l 打头的命令
!num  # 执行历史命令列表的第 num 条命令
!$    # 上一条命令的最后一个参数
!*    # 上一条命令的所有参数
^1^2  # 将前一条命令中的 1 变成 2

\command # 忽略别名

basename $(readlink -f $0) # 获取脚本的名称
dirname  $(readlink -f $0) # 获取脚本的目录

bash file-name # 执行文件内的命令
bash -c "ls"   # 将字符串的内容交由 bash 执行, 字符串里可包含重定向和管道

bc <<< "scale=2; 10/2" # 使用两位小数, 输出: 5.00
bc <<< "ibase=2;  100" # 输入使用二进制, 输出: 4
bc <<< "obase=2;   10" # 输出使用二进制, 输出: 1010

bg %jobspec # 后台暂停 --> 后台运行, 有无 % 都成
fg %jobspec # 后台     --> 前台运行, 有无 % 都成

c++filt  a.out    # 可以解析动态库里的符号


clang-format    main.cc                                  # 预览规范后的代码
clang-format -i main.cc                                  # 直接在原文件上规范代码
clang-format -style=Google main.cc                       # 显示指明代码规范，默认为 LLVM
clang-format --dump-config -style=Google > .clang-format # 将代码规范配置信息写入文件 .clang-format
clang-format -style=file main.cc                         # 使用自定义代码规范,
                                                         # 规范位于当前目录或任一父目录的文件
                                                         # 的 .clang-format 或 _clang-format 中，
                                                         # (如果未找到文件，使用默认代码规范)
# 参考资源:
# clang-format  -> https://clang.llvm.org/docs/ClangFormat.html
# clang-format  -> https://clang.llvm.org/docs/ClangFormatStyleOptions.html
# askubuntu     -> https://askubuntu.com/questions/730609/how-can-i-find-the-directory-to-clang-format
# stackoverflow -> https://stackoverflow.com/a/39781747/7671328

           # 定期执行命令
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

curl -I ... # 只打印头部信息
                                      # 文件如果是符号链接, 将使用符号链接对应的文件
dd if=/dev/zero of=junk.data bs=1M count=1
dd if=/dev/zero bs=1M count=1000 | nc 127.0.0.1 9999 # 测速-客户端

df   -Th    # 文件系统挂载情况

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

dos2unix 1.txt # \r\n (windows) => \n (Linux/iOS)
unix2doc 1.txt # \n (Linux/iOS) => \r\n (windows)

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

env          # 设置环境变量, 然后执行程序

exec &>> 1.log  # 脚本内重定向
exec ls         # 替换当前 shell, 执行后不再执行之后的命令
exec &>  1.txt  # 打开文件描述符, 然后继续执行之后的命令

flock    1.c ls # 设置文件互斥锁 执行命令, 设置锁失败, 等待
flock -n 1.c ls # 设置文件互斥锁 执行命令, 设置锁失败, 退出

[[ "$FLOCKER" != "$0" ]] && exec env FLOCKER="$0" flock -en "$0" "$0" "$@" || :
                # 脚本内使用, 保证脚本最多执行一次
                # 解释:
                #   1. 第一次进入脚本, 由于变量未设置, 会执行 exec
                #   2. 调用 exec, 使用 env 设置 变量名
                #   3. 执行 flock, 重新执行这个脚本, 执行完脚本后会退出, 不会执行之后的命令
                #        * 使用脚本名作为 文件锁, 脚本名使用绝对路径, 所以不会重复
                #   4. 第二次进入脚本, 由于变量已设置, 直接往下执行就可以了
                # 5. 在此期间, 如果, 有其他脚本进入, 文件锁获取失败, 就直接退出了

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

free -h     # 内存使用情况

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
gdb> p/x var                 # 按十六进制格式显示变量
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

history

iconv -f gbk -t utf-8 1.txt -o 1.txt

id        # 输出实际或有效的用户和组信息

ifconfig -- 已过时, 被 ip addr  替代

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

jobs          # 列出后台作业
jobs %jobspec # 作业号有无 % 都成
jobs -l       #   列出后台作业的 PID
jobs -p       # 只列出后台作业的 PID
jobs -n       # 只列出进程改变的作业
jobs -s       # 只列出停止的作业
jobs -r       # 只列出运行中的作业

kill         pid # 通过进程ID发送信号给进程或进程组
kill -signal pid # 指定信号，默认值为 SIGTERM
kill -l          # 列出所有信号

killall             # 通过进程名称发送信号给进程或进程组, 进程名称精确匹配
killall -l          # 列出所有信号
killall -o 2m a.out # 发给 2 分钟前启动的 a.out
killall -y 2m a.out # 发给 2 分钟内启动的 a.out
killall -w    a.out # 等待进程结束

pkill         ... # 杀死进程, 扩展的正则表达式，参数和 pgrep 类似 -- 常用
pkill -signal ... # 指定信号，默认值为 SIGTERM

less # 空格   : 下一页
     # ctrl+F : 下一页
     # b      : 上一页
     # ctrl+b : 上一页
     # 回车   : 下一行
     # =      : 当前行号
     # y      : 上一行

ln -s target symbolic_link_name # 创建符号链接

ls -a        # 列出当前目录中的元素, 包括隐藏的文件
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
ls -clt      # 使用 ctime 排序和展示, 新 -> 旧
ls -tl       # 使用 mtime 排序和展示, 新 -> 旧
ls -ult      # 使用 atime 排序和展示, 新 -> 旧

ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtu # 以 文件访问时间     排序, 不准确
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtc # 以 文件属性修改时间 排序
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrt  # 以 文件内容修改时间 排序
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtd # 以 文件内容修改时间 排序, 只列出目录本身
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrS  # 以 文件大小         排序
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrv  # 以 文件名为版本号   排序

ls &> /dev/null # 重定向

                   # lsof -- sudo yum install lsof
lsof -iTCP         # 查看 TCP 信息
lsof -i :22        # 查看指定 端口号 的信息
lsof -i@1.2.3.4:22 # 查看是否连接到指定 IP 和 端口号上
lsof -p 1234       # 指定 进程号
lsof -d 0,1,2,3    # 指定 文件描述符
lsof -t            # 仅获取进程ID

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

nohup sleep 1000 & # 脱离终端, 在后台运行, 忽略信号 SIGHUP

nslookup baidu.com # 查询 域名 对应 的 IP

ntpdate -s time-b.nist.gov          # 使用时间服务器更新时间

patch     1.txt diff.pathc  # 恢复文件
patch -p1 1.txt diff.pathc  # 恢复文件, 忽略 diff.pathc 的第一个路径

ping      www.bing.com # 使用 ICMP ping 主机
ping -c 3 www.bing.com # 使用 ICMP ping 主机, 设置测试的次数
ping -i 3 www.bing.com # 使用 ICMP ping 主机, 设置间隔的秒数
ping -w 3 www.bing.com # 使用 ICMP ping 主机, 设置耗时的上限
ping -f   www.bing.com # 使用 ICMP ping 主机, 高速率极限测试, 需要 root 权限

                             # 多个命令之间取或
ps -U RUID -G RGID           # 实际的用户和组
ps -u EUID -g EGID           # 有效的用户和组
ps -p PID                    # 进程ID, 多个进程可以重复使用 -p 或者参数以分号分割 -- 常用
ps -s SID                    # 会话ID
ps --ppid PPID               # 父进程ID
ps -t ...                    # 终端
ps -C vim                    # 进程名称, 全名称 或 前 15 位

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

pstree     [PID] # 以进程 PID 为根画进程树, 默认为 1
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
pwdx pid # 列出进程的当前工作目录

read name     # 读取, 如果参数值小于字段数, 多余的值放入最后一个字段

readlink    1.c.link  # 读取符号链接
readlink -f 1.c.link  # 读取符号链接, 递归

redis flushdb # 清空数据
redis -c ...  # 集群时需要使用 -c 启动, 否则查不到数据

rm -r  a    # 递归删除
rm -rf a    # 强行删除, 文件不存在时, 忽略

route    -- 已过时, 被 ip route 替代

rz          #  windows 向 虚拟机  发送数据

sed    "p"                 1.txt #   正常使用
sed -e "p"                 1.txt #   使用 -e 添加脚本, -e 支持多次使用
sed -n "p"                 1.txt #   不输出模式空间的内容
sed -i "p"                 1.txt #   直接在原文件上修改
sed -r "p"                 1.txt #   使用扩展的正则表达式，默认使用基础的正则表达式 -- 推荐使用
sed -z "p"                 1.txt #   输入行以 \0 区分, 而不是 \n
sed -f 1.sed               1.txt #   从文件中读取脚本
sed -n "p"                 1.txt #   输出整个文件
sed -n "2p"                1.txt #   输出第二行
sed -n "2!p"               1.txt # 不输出第二行
sed -n "2,5p"              1.txt #   输出 [2,5] 行
sed -n "2,+4p"             1.txt #   输出 [2,6] 行
sed -n "$p"                1.txt #   输出最后一行
sed -n "/11/p"             1.txt #   输出匹配到 111 的行, 支持正则
sed -n "\c11cp"            1.txt #   输出匹配到 11 的行, c 可以使用任意字符, 便于处理包含 / 的情况
sed -n "/111/,/222/p"      1.txt #   输出匹配到 111 的行, 到匹配到 222 的行(包含)
                                 #       222 未匹配到时表示文件末尾
                                 #       开始匹配使用正则表达式时, 不能匹配同一行
sed -n "/111/,+4p          1.txt #   输出匹配到 111 的行以及接下来四行, 共五行
sed -n "0,/111/p"          1.txt #   输出文件开头到匹配到 111 的行
                                 #       如果 /111/ 可以匹配第一行，将输出第一行
sed -n "1,/111/p"          1.txt #   输出第一行到匹配到 111 的行
                                 #       /111/ 不会匹配第一行
sed -n ": ..."             1.txt # 定义标签
sed -n "="                 1.txt # 输出行号
sed -n "a ..."             1.txt # 行后插入
sed -n "b ..."             1.txt # 跳到标签处，如果标签未指定时，跳到脚本末尾
sed -n "c ..."             1.txt # 取代所选择的行
sed -n "d"                 1.txt # 删除模式空间的内容, 并进入下一循环
sed -n "D"                 1.txt # 删除模式空间的第一行内容
                                 #     如果模式空间变为空，开始下一循环
                                 #     否则，跳到脚本开始处继续
sed -n "g"                 1.txt # 将保持空间复制到模式空间
sed -n "G"                 1.txt # 将保持空间附加到模式空间
sed -n "h"                 1.txt # 将模式空间复制到保持空间
sed -n "H"                 1.txt # 将模式空间附加到保持空间
sed -n "i ..."             1.txt # 行前插入
sed -n "l"                 1.txt # 列出当前行，标明不可见字符
sed -n "n"                 1.txt # 读取下一行到模式空间
sed -n "N"                 1.txt # 将下一行添加到模式空间内容后
sed -n "p"                 1.txt # 打印模式空间的内容
sed -n "P"                 1.txt # 打印模式空间的第一行内容
sed -n "2q"                1.txt # 输出第一行，第二行后退出
sed -n "2Q"                1.txt # 输出第一行后退出
sed -n "r..."              1.txt # 每一行后添加文件的内容
                                 #     貌似无法在文件开头添加另一文件的内容
sed    "R2.txt"            1.txt # 第一行后插入 2.txt 的第一行
                                 # 第二行后插入 2.txt 的第二行, 如果 2.txt 已读完，则不插入
sed    "s/123/456/"        1.txt # 替换第一处
sed    "s/123/456/2"       1.txt # 替换第二处
sed    "s/123/456/2g"      1.txt # 替换第二处及以后
sed    "s/123/456/g"       1.txt # 替换所有
sed -n "s/123/456/gp"      1.txt # 打印替换后的结果
sed -n "s/123/456/gw2.txt" 1.txt # 替换后的结果写入文件 2.txt
sed    "s|123|456|"        1.txt # 使用不同的分割符
sed    "s/.*/[&]/"         1.txt # & 用于表示所匹配到的内容
sed    "s/\(1\)/[\1]/"     1.txt # \1 表示第一个字串
sed -r "s/(1)/[\1]/"       1.txt # \1 表示第一个字串
sed    "s/1/a \t b/"       1.txt # 可以包含 \n \t
sed -n "t abc              1.txt # 前一个 s 命令成功会跳转到指定标签   -- 这个一般用不上
sed -n "T abc              1.txt # 前一个 s 命令未成功会跳转到指定标签 -- 这个一般用不上
sed -n "w ..."             1.txt # 写模式空间的内容到文件
sed -n "W ..."             1.txt # 写模式空间的第一行的内容到文件
sed -n "x"                 1.txt # 交换模式空间和保持空间的内容
sed -n "y/123/456/"        1.txt
sed -n "y/1-3/456/"        1.txt
sed -n "y/123/4-6/"        1.txt
sed -n "y/1-3/4-6/"        1.txt
                                 # 测试 301-03.sh

set -o nounset  # 使用未初始化的变量报错, 同 -u
set -o errexit  # 只要发生错误就退出, 同 -e
set -o pipefail # 只要管道发生错误就退出
set -o errtrace # 函数报错时, 也处理 trap ERR, 同 set -E
set -o  xtrace  # 执行前打印命令, 同 -x
set -o verbose  # 读取前打印命令, 同 -v
set -o vi       # 使用 vi 快捷键
set -- ....     # 重新排列参数
                # 建议使用: set -ueo pipefail

sleep 30   # 前台运行
sleep 30 & # 后台运行

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

               # 查看文件时间
stat       1.c # 列出 birth atime mtime ctime
stat -L    1.c # 符号链接所指向的文件, 而不是符号链接本身
stat -c %w 1.c # 列出 birth 人类可读形式
stat -c %W 1.c # 列出 birth 距离 Epoch 的秒数
stat -c %x 1.c # 列出 atime 人类可读形式
stat -c %X 1.c # 列出 atime 距离 Epoch 的秒数
stat -c %y 1.c # 列出 mtime 人类可读形式
stat -c %Y 1.c # 列出 mtime 距离 Epoch 的秒数
stat -c %z 1.c # 列出 ctime 人类可读形式
stat -c %Z 1.c # 列出 ctime 距离 Epoch 的秒数

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

su        # 切到 root
su -      # 切到 root, 更新主目录, 环境变量等, 相当于重新登录
su   lyb  # 切到 lyb

sudo                                          # 权限管理文件: /etc/sudoers, 使用 visudo 编辑
sudo -u USERNAME COMMAND                      # 指定用户执行命令
sudo -S date -s "20210722 10:10:10" <<< "123" # 脚本中免密码使用

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

tee    1.txt # 管道中把文件拷贝到文件
tee -a 1.txt # 管道中把文件添加到文件

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
        #   M 内存排序
        #   P CPU 排序
        #   T 时间排序
top -n 1   # 刷新次数
top -b     # 方便写入文件
top -c     # 显示完整命令行
top -p ... # 指定 PID
top -u lyb # 指定用户

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

trap ... ERR  # 发生错误退出时, 执行指定命令
trap ... EXIT # 任意情况退出时, 执行指定命令

tree -p "*.cc"       # 只显示  匹配到的文件
tree -I "*.cc"       # 只显示没匹配到的文件
tree -H . -o 1.html  # 指定目录生成 html 文件

ulimit              # 限制资源使用, 包括:
                    #   内存, 虚拟内存, CPU
                    #   进程数, 线程数
                    #   文件锁数, 文件描述符数, 写入文件大小
                    #   待处理的信号数
                    #   core 文件大小
                    # 也可指定是硬限制还是软限制
ulimit -a           # 列出资源的限制
ulimit -c unlimited # 允许 core 文件

uname -a # 全部信息
uname -m # x86_64 等
uname -r # 内核版本

uniq    # 删除重复的行
uniq -c # 输出统计的次数
uniq -d # 只输出重复的行, 重复的项只输出一次
uniq -D # 只输出重复的行, 重复的项输出多次
uniq -i # 忽略大小写
uniq -u # 只输出没重复的行

uptime -s # 列出系统启动时间

cat lyb | xargs -i vim {} # 以此编辑 lyb 中的每一个文件

wc    # 输出 换行符数 字符串数 字节数
wc -l #   行数
wc -w # 字符串数
wc -c # 字节数
wc -m # 字符数

## 建议
* 使用 pgrep 获取 PID, 使用 ps 列出详细信息
* 使用 etimes 可以方便计算出启动时间, 并格式化 年-月-日 时-分-秒 时区
* 一般使用进程的前 15 位即可
* 使用 pkill 发送信号
```
