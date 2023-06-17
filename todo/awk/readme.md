
## 简介
* awk 以行为单位，切割成列，处理数据

## 常用命令行参数
```
awk            script 1.txt
awk -F:        script 1.txt 以字符       : 作为字段分割符
awk -F123      script 1.txt 以字符串   123 作为字段分割符
awk -F[123]    script 1.txt 以字符   1 2 3 作为字段分割符
awk -f         1.awk  1.txt 从文件中读取命令
awk -v lyb=... script 1.txt 定义变量
```

## 脚本格式
```
awk 'BEGIN   { getline     } # 读取一行
     pattern { commands    }
     END     { print "end" }' 1.txt

* awk 使用扩展的正则表达式
* BEGIN 和 END 都是可选的
* 用单引号 或 双引号 都行, 建议使用单引号, 因为如果使用双引号，使用 $ 符号时必须转义
* pattern 类型
    * 行号:
        * NR < 5        # 行号 [1,4] 的行
        * NR==1,NR==4   # 行号 [1,4] 的行
    * 正则表达式:
        * /linux/       #   包含 linux 的行
        * !/linux/      # 不包含 linux 的行
        * /start/,/end/ # [] 区间匹配
    * 字段匹配:
        * $1  ~ /123/   # 使用正则表达式匹配
        * $1 !~ /123/   # 使用正则表达式匹配, 排除匹配到的行
        * $1 ==  123    # 数值匹配, 精确匹配，> >= == < <=
        * $1 == "123"   # 字符串匹配, 精确匹配，> >= == < <=
```

## 基本语法
```
* 数字:
    * 包括整数和浮点数
    * 整数除以整数，结果可能是小数
    * int(...) 将浮点数转换为整数，将舍弃小数部分，比如 int(1.9) == 1, int(-1.9) == -1
    * + 将对数字进行相加, 即使是字符串
* 字符串：以单引号 或 双引号 包含的字符串
    * tolower() -- 小写
    * toupper() -- 大写
    * length()  -- 长度
    * sub() -- 正则查找, 替换第一处
    * gsub() -- 正则查找, 替换所有
    * gensub() -- 正则查找, 可选则替换所有还是某一个, 不修改原字符串
    * index() -- 字符串查找
    * match() -- 字符串查找(正则表达式), 并将结果保存到数组
    * split() -- 字符串 => 数组
    * 字符串连接直接使用空分开即可
* 数组：awk 使用关联数组，下标使用数字或字符串都成
    * 添加或修改元素  : arr[i] = ...
    * 删除数组中的变量: delete arr[i]
    * 遍历数组: i 为数组下标，注意返回的顺序不固定
        for (i in arr) {
            ....
        }
    * asort() -- 元素排序
    * asorti() -- 索引排序
* 变量:
    * 变量不需要声明，可以直接使用
    * 变量使用一般不用使用 $, 除非是数字型变量，为了和数字区分，需要加上 $ 符号
* 赋值：赋值号左右两边有无空格都成
* 语句使用分号分割
*       if 语句, 同 C语言
*    while 语句, 同 C语言
* do while 语句, 同 C语言
*      for 语句，同 C语言, 外加 for (i in arr) i 为索引, arr 为数组
* 时间函数
    * systime()  -- 获取当前的时间戳
    * strftime() -- 时间戳 --> 格式化
    * mktime()   -- 年月日等 --> 时间戳
* 其他常用函数
    * print    参数以逗号分割，输出的字段分割符默认为空格，结尾将输出换行符
    * printf   同 C语言
```

## 常用变量
```
$0  整行
$1  第一列
FIELDWIDTHS 由空格分隔的一列数字，定义了每个数据字段确切宽度
FS  输入字段分隔符 默认值为空字符
RS  输入记录分隔符 默认值为换行符
OFS 输出字段分隔符 默认值为空格
ORS 输出记录分隔符 默认值为换行符

           命令行参数部分, 下标从 0 开始，脚本不计入命令行参数
ARGC       当前命令行参数个数
ARGIND     当前文件在ARGV中的位置
ARGV       包含命令行参数的数组

CONVFMT    数字的转换格式（参见printf语句），默认值为%.6 g
ENVIRON    当前shell环境变量及其值组成的关联数组
ERRNO      当读取或关闭输入文件发生错误时的系统错误号
FILENAME   用作gawk输入数据的数据文件的文件名
FNR        当前数据文件中的数据行数
IGNORECASE 设成非零值时，忽略gawk命令中出现的字符串的字符大小写
NF         数据文件中的字段总数
NR         已处理的输入记录数
OFMT       数字的输出格式，默认值为%.6 g
RLENGTH    由match函数所匹配的子字符串的长度
RSTART     由match函数所匹配的子字符串的起始位置
```

## 调用其他命令
```
* awk -f 11.awk 2.txt                  -- 测试执行系统命令 -- 常用
* awk '{ system("ls")         }' 1.txt -- 执行 Bash 命令
* awk '{ print "ls" | "bash"  }' 1.txt -- 执行 Bash 命令

awk '{ print $0 }' 1.txt -- 01.awk
    -- 输出文件的每一行
awk '{ getline; print $0 }' 1.txt -- 02.awk
    -- getline 读取文件的下一行到 $0, $1...
    -- 输出文件的偶数行
awk '{ getline str; print str }' 1.txt -- 03.awk
    -- getline 读取文件的下一行到 str
    -- 输出文件的偶数行
awk '{ "ls" | getline; print $0 }' 1.txt -- 04.awk
    -- 将 ls 的结果存储到 $0, $1...
    -- 如果结果有多行的话, 将覆盖下一轮循环的 $0, $1..., 直到数据读完
    -- ls 命令只执行一次
awk '{ "ls" | getline str; print str }' 1.txt -- 05.awk
    -- 将 ls 的结果存储到 str
    -- 如果结果有多行的话, 将覆盖下一轮循环的 str, 直到数据读完
    -- ls 命令只执行一次
awk '{ "ls" | getline; close("ls"); print $0 }' 1.txt -- 06.awk
    -- 将 ls 的结果存储到 $0, $1...(只存储第一行)
    -- 关闭 ls 开启的管道
    -- ls 命令每轮循环都会执行一次
awk '{ "ls" | getline str; close("ls"); print str }' 1.txt -- 07.awk
    -- 将 ls 的结果存储到 str(只存储第一行)
    -- 关闭 ls 开启的管道
    -- ls 命令每轮循环都会执行一次
awk '{ getine     < "README"; print $0  }' 1.txt -- 08.awk # 从文件中读取, 貌似只能读取一次
awk '{ getine str < "README"; print str }' 1.txt -- 09.awk # 从文件中读取, 貌似只能读取一次
```

