#!/bin/bash

. ~/.bashrc

set -o nounset  # 使用未初始化的变量报错
set -o errexit  # 只要发生错误就退出
set -o pipefail # 只要管道发生错误就退出

function do_ps() {
    if [[ $# == 0 ]]; then
        ps --no-header -e -o ruser,pcpu,pmem,rsz | awk '
            {
                cpu[$1] += $2
                mem[$1] += $3
                rsz[$1] += $4
            }
            END {
            printf "%10s%10s%10s%10s\n","RUSER","%CPU","%MEM","RSZ(KB)"
                for (key in cpu)
                    printf "%10s%10s%10s%10s\n", key, cpu[key],mem[key],rsz[key]
            }'
    else
        argv=$(pgrep -d, $@ || log_err "$@ 未找到")
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

