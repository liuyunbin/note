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
    if [[ $# == 0 ]]; then
        local key=ruser
        local argv="-e"
    else
        local key=comm
        local argv="-p $1"
    fi

    printf "%16s%10s%10s%10s%10s\n" "KEY" "NLWP" "%CPU" "%MEM" "RSZ(KB)"
    ps --no-header -o $key,nlwp,pcpu,pmem,rsz $argv | awk '
        {
            nlwp[$1] += $2
             cpu[$1] += $3
             mem[$1] += $4
             rsz[$1] += $5
        }
        END {
            for (key in cpu)
                printf "%16s%10s%10s%10s%10s\n",key,nlwp[key],cpu[key],mem[key],rsz[key]
        }' | sort -k 5 -h
}

function do_ps_comm() {
    if [[ $# == 1 ]]; then
        local argv="-e"
    else
        local argv="-p $2"
    fi

    ps -o comm,pid,ppid,ruser,pcpu,pmem,rsz,nlwp,state,etime:13,etimes:10 --sort=-$1 $argv | awk '
        BEGIN {
            getline
            printf "%s %15s\n", $0, "启动时间"
        }

        {
            run_time=$NF
            now=systime();
            start_time = strftime("%Y-%m-%d %H:%M:%S", now-$NF);
            printf "%s %19s\n", $0, start_time
        }'
}

function do_ps() {
    if [[ $# == 0 ]]; then
        echo "--------------------------耗 CPU最多的3个进程---------------------------"
        do_ps_comm pcpu | head -4
        echo "--------------------------耗内存最多的3个进程---------------------------"
        do_ps_comm pmem | head -4
        echo "--------------------------用户数据汇总----------------------------------"
        do_ps_sum
    else
        argv=
        for key in $@; do
            [[ "$argv" != "" ]] && argv=${argv},
            argv=$argv$(pgrep -d, $key || log_erro "未找到进程 $key")
        done

        echo "--------------------------进程数据详情----------------------------------"
        do_ps_comm etime $argv
        echo "--------------------------进程数据汇总----------------------------------"
        do_ps_sum $argv
    fi
}

function do_last_login() {
    lastlog $@ | awk '
        BEGIN {
            max_user_len = 0
        }

        NR > 1 && NF > 6 {
            user = $1
            user_len = length(user)
            if (user_len > max_user_len)
               max_user_len = user_len
            time = $(NF-5) FS $(NF-4) FS $(NF-3) FS $(NF-2) FS $(NF-1) FS $NF
            cmd = "date -d\""time"\" +\"%F %T\""
            cmd | getline time
            close(cmd)
            arr[user] = time
        }

        END {
            for (user in arr)
                printf "%*s\t%s\n", max_user_len + 1, user, arr[user]
        }' | sort -k 2,3
}

cmd=$1
shift
do_$cmd $@

