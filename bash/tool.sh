#!/bin/bash
set -o nounset  # 使用未初始化的变量报错
set -o errexit  # 只要发生错误就退出
set -o pipefail # 只要管道发生错误就退出

function log_info() {
    echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty # 默认颜色
}

function log_warn() {
    echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty # 黄色
}

function log_erro() {
    echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty # 红色
    exit -1
}

function do_ps() {
    : ${1:?use $0 pattern}
    argv=
    for key in $@; do
        [[ "$argv" != "" ]] && argv=${argv},
        argv=$argv$(pgrep -d, $key || log_erro "未找到进程 $key")
    done

    ps -o etimes,ruser:10,pid,nlwp,cmd --sort=-etime --no-headers -p $argv | awk '
        {
            $1 = strftime("%Y-%m-%d %H:%M:%S %z", systime() - $1)
            cmd = ""
            for (i = 5; i <= NF; ++i)
                cmd=cmd" "$i
            printf "%s %10s %6s %4s => %s\n", $1, $2, $3, $4, cmd
        }'
}

function do_lastlog() {
    lastlog $@ | awk '
        NR > 1 && NF > 6 {
            user = $1
            time = $(NF-5) FS $(NF-4) FS $(NF-3) FS $(NF-2) FS $(NF-1) FS $NF
            cmd = "date -d\""time"\" +\"%Y-%m-%d %H:%M:%S %z\""
            cmd | getline time
            close(cmd)
            printf "%s => %s\n", time, user
        }' | sort
}


cmd=$1
shift
do_$cmd $@

