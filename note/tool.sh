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

function do_ps_sum() {
    if [[ $# == 1 ]]; then
        argv="-e"
    else
        argv="-p $2"
    fi
    printf "%16s%10s%10s%10s%10s\n" "KEY" "%CPU" "%MEM" "RSZ(KB)" "NLWP"
    ps --no-header -o $1,pcpu,pmem,rsz,nlwp $argv | awk '
        {
             cpu[$1] += $2
             mem[$1] += $3
             rsz[$1] += $4
            nlwp[$1] += $5
        }
        END {
            for (key in cpu)
                printf "%16s%10s%10s%10s%10s\n",key,cpu[key],mem[key],rsz[key],nlwp[key]
        }' | sort -k 4 -h
}

function do_ps() {
    if [[ $# == 0 ]]; then
        do_ps_sum ruser
    else
        argv=
        for key in $@; do
            [[ "$argv" != "" ]] && argv=${argv},
            argv=$argv$(pgrep -d, $key || log_erro "未找到进程 $key")
        done

        ps -o comm,pid,ppid,ruser,pcpu,pmem,rsz,nlwp,etime:10,etimes:10 --sort=-etime -p $argv | awk '
            BEGIN {
                getline
                printf "%s %23s\n", $0, "启动时间"
            }

            {
                run_time=$NF
                now=systime();
                start_time = strftime("%Y-%m-%d %H:%M:%S", now-$NF);
                printf "%s %19s\n", $0, start_time
            }'
        echo "-------------------------------------------------------------"
        do_ps_sum comm $argv
    fi
}

cmd=$1
shift
do_$cmd $@

