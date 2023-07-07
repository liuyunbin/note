#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

cmd=$(basename $0)

function usage() {
    log_info
    log_info "说明:"
    log_info "    测试命令行参数"
    log_info "使用例如:"
    log_info "    $cmd -h     # 帮助文档"
    log_info "    $cmd -a 123 # 测试"
    log_info
    exit 0
}

while getopts ":ha:" arg; do
    case "$arg" in
    h)
        usage
        exit 0
        ;;
    a)
        log_info "a 的参数为 $OPTARG"
        ;;
    :)
        log_info "可选项要求参数 -- '$OPTARG'"
        log_erro "请使用 '$cmd -h' 获取帮助信息"
        ;;
    ?)
        log_info "非法参数 -- '$OPTARG'"
        log_erro "请使用 '$cmd -h' 获取帮助信息"
        ;;
    esac
done

shift $(($OPTIND - 1))

function test_if() {
    log_info
    v=./readme.md
    msg="测试 if 语句: "
    if [[ -d $v ]]; then
        msg=$msg" $v 是一个目录"
    elif [[ -f $v ]]; then
        msg=$msg" $v 是一个普通文件"
    else
        msg=$msg" $v 是一个其他文件"
    fi
    log_info "$msg"
}

function test_while() {
    log_info
    i=0
    msg="测试 while 语句: "
    while (( i < 5 )); do
        msg=$msg" $i"
        ((++i))
    done
    log_info "$msg"
}

function test_for() {
    log_info
    msg="测试 for 语句: "
    for (( i = 0; i < 5; ++i)); do
        msg=$msg" $i"
    done
    log_info "$msg"

    msg="测试 for 语句: "
    for i in {0..5}; do
        msg=$msg" $i"
    done
    log_info "$msg"

    msg="测试 for 语句: "
    for i in ./t*.sh; do
        msg=$msg" $i"
    done
    log_info "$msg"
}

function test1() {
    v=456
    log_info "函数内: $v";
}

function test2() {
    local v=456
    log_info "函数内: $v";
}

function test_function() {
    log_info

    v=123
    log_info "测试函数内变量修改: "

    log_info "调用函数前: $v";
    test1
    log_info "调用函数后: $v";

    log_info

    v=123
    log_info "测试函数内局部变量修改: "
    log_info "调用函数前: $v";
    test2
    log_info "调用函数后: $v";
}

function test_array() {
    log_info
    v=(1 2 3)
    v+=(7 8 9)
    log_info "测试数组添加成员 ${v[@]}"
}

test_if
test_while
test_for
test_function
test_array

log_info

#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

data="
1
2


3
4
5

"

log_info "逆序输出文件的内容"
sed -n '1!G; h; $p'        <<< "$data"

log_info "输出最后的三行"
sed    ':start; $q; N; 4,$D; b start' <<< "$data"

log_info "删除连续的空行 -- 太绕了, 能看懂即可"
sed    '/./,/^$/!d'  <<< "$data"

log_info "删除文件末尾的空行 -- 能理解即可, 太绕了"
sed    ':start; /^\n*$/{$d; N; b start}' <<< "$data"

#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

log_info
log_info "测试浮点数计算"
awk 'BEGIN { n = 0;}
     { for (i = 1; i <= NF; ++i) arr[n++] = $i }
     END {
        sum = 0
        printf("  输入的元素: ")
        for (i in arr) {
            printf("%.2lf ", arr[i]);
            sum += arr[i]
        }
        printf("\n  总和为: %.2lf\n", sum);
        printf("  平均数为: %.2lf\n", sum / n);
        printf("  测试删除数组的元素\n")
        delete arr[5]
        printf("  删除后的数组: ")
        for (i in arr) {
            printf("%.2lf ", arr[i]);
        }
        printf("\n");
    }' <<< "1.1 2.2 3.3 4.4 5.5 6.6"

data="
111 111 111
222 111 222
1.111111111111111111111111111111111111111111111111 111 111
222 222 222"

log_info
log_info "测试模式匹配: "
awk '/111/{ printf("\t%s\n", $0) }' <<< "$data"

log_info
log_info "测试字段匹配: "
awk '$1 ~ 111 { printf("\t%s\n", $0) }' <<< "$data"

log_info
log_info "测试字段非匹配: "
awk '$1 !~ 111 { printf("\t%s\n", $0) }' <<< "$data"

log_info
log_info "测试字符串匹配 -- 不同"
awk '$1 == "1.11111111111111111111111111111111111111111111111" {printf("字符串匹配: %s\n", $2) }' <<< "$data"

log_info
log_info "测试数字匹配 -- 转换成小数后近似相等"
awk '$1 ==  1.11111111111111111111111111111111111111111111111  {printf("整数匹配  : %s\n", $2) }' <<< "$data"

log_info
log_info "测试获取默认 shell"
awk 'BEGIN { FS=":"} { printf("\t%s --> %s\n", $1, $NF) }' /etc/passwd | tail -5

log_info
log_info "测试排序"

awk '{
        arr[0] = 111
        arr[1] = 333
        arr[2] = 444
        arr[3] = 222

        asort(arr)
        for (i in arr)
            printf(" %d ", arr[i])
        printf("\n")
    }' <<< "1"

log_info
log_info "测试字符串函数"
awk '{
        v1 = "abc AAA abc"
        printf("  原字符串: %s\n", v1)
        printf("大写字符串: %s\n", tolower(v1))
        printf("小写字符串: %s\n", toupper(v1))
        printf("字符串长度: %d\n", length(v1))
        printf("字符串查找: %s\n", index(v1, "AAA"))
        printf("字符串查找(正则表达式): %s\n", match(v1, "AA*"))
        printf("子字符串: %s\n", substr(v1, 4))
        v2 = v1
        printf("      原字符串: %s\n", v1)
        sub("a", "123", v2)
        printf("替换后的字符串: %s\n", v2)
        v2 = v1
        printf("      原字符串: %s\n", v1)
        gsub("a", "123", v2)
        printf("替换后的字符串: %s\n", v2)
        v2 = v1
        v2 = gensub("a", "123", "2", v1)
        printf("      原字符串: %s\n", v1)
        printf("替换后的字符串: %s\n", v2)
        v2 = "1 2 3 4 5"
        len = split(v2, a)
        printf("字符串切割后的长度: %d\n", len)
    }' <<< "1"

log_info
log_info "测试时间函数"
awk '{
        v1 = systime()
        v2 = strftime("%Y-%m-%d %H:%M:%S %z", v1)
        printf("时间戳: %s\n日期格式: %s\n", v1, v2)
    }' <<< "1"

log_info
log_info "测试自定义函数"
awk '
    function test() {
        return  1 + 2
    }

    {
        print test()
    }' <<< "1"

log_info
log_info "测试数字, 字符串相加"
awk '{
    v1 = 111
    v2 = "111"
    printf("裸数字相加: %d\n", 111 + 111);
    printf("裸字符串相加: %d\n", "111" + "111");
    printf("裸数字字符串相加: %d\n", 111 + "111");
    printf("数字相加: %d\n", v1 + v1);
    printf("字符串相加: %d\n", v2 + v2);
    printf("数字字符串相加: %d\n", v1 + v2);
    printf("字符串连接\n")
    printf("字符串连接: %d\n", 111 111);
    printf("字符串连接: %d\n", "111" 111);
    printf("字符串连接: %d\n", 111 "111");
    printf("字符串连接: %d\n", "111" "111");
    printf("字符串连接: %d\n", v1 v2);
    printf("字符串连接: %d\n", v2 v2);
}' <<< "1"

log_info
log_info "测试执行系统命令"
awk '{
    cmd = "date +\"%Y-%m-%d %H:%M:%S %z\""
    cmd | getline time
    close(cmd)
    printf("时间为: %s\n", time)
}' <<< "1"

#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

log_info
log_info "查找合法的IP: "
v='\d|[1-9]\d|1\d{2}|2[0-4]\d|25[0-5]'
grep -P -o "^\s*(($v)\.){3}($v)\s*\$" 1.txt

log_info
log_info "查找合法的IP: "

v='[0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]'
grep -E -o "^\s*(($v)\.){3}($v)\s*\$" 1.txt

log_info
log_info "测试合法的固定电话: "
grep -P -o '^\s*((\()?0\d{1,3}(?(2)\)|-))?\d{7}\s*$' 2.txt

log_info
log_info "测试合法的固定电话: "
grep -P -o '^\s*(0\d{1,3}-|\(0\d{1,3}\))\d{7}\s*$' 2.txt

