#!/bin/bash
set -o nounset  # 使用未初始化的变量报错
set -o errexit  # 只要发生错误就退出
set -o pipefail # 只要管道发生错误就退出

function log_info() {
    echo -e "\033[00m$(date +'%F %T') $@\033[0m" > /dev/tty # 默认颜色
}

function log_warn() {
    echo -e "\033[33m$(date +'%F %T') $@\033[0m" > /dev/tty # 黄色
}

function log_erro() {
    echo -e "\033[31m$(date +'%F %T') $@\033[0m" > /dev/tty # 红色
    exit -1
}

function do_ps() {
    if [[ $# == 0 ]]; then
        printf "%10s%10s%10s%10s\n" "RUSER" "%CPU" "%MEM" "RSZ(KB)"
        ps --no-header -e -o ruser,pcpu,pmem,rsz | awk '
            {
                cpu[$1] += $2
                mem[$1] += $3
                rsz[$1] += $4
            }
            END {
                for (key in cpu)
                    printf "%10s%10s%10s%10s\n", key, cpu[key],mem[key],rsz[key]
            }' | sort -k 4 -h
    else
        argv=$(pgrep -d, $@ || log_erro "未找到进程 $@")
        ps -o comm,pid,ppid,ruser,pcpu,pmem,rsz,nlwp,etime,etimes --sort=-etime -p $argv | awk '
            BEGIN {
                getline
                printf "%-15s %s\n","启动时间",$0
            }

            {
                run_time=$NF
                now=systime();
                start_time = strftime("%Y-%m-%d %H:%M:%S", now-$NF);
                printf "%-19s %s\n",start_time,$0
            }'
    fi
}

cmd=$1
shift
do_$cmd $@

