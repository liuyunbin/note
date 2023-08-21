
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

