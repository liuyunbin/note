#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

function do_build() {
    mkdir -p build
    cd build
    cmake ..
    make
    # make test
    cd ..
    rm -r build
}

function do_test() {
    local file_name=test.cc

    if [[ $# != "0" ]]; then
        file_name=$@
    fi

    g++ -std=c++11 $file_name && ./a.out
}

function do_install_command() {
    sudo apt install -y clang-format
    sudo apt install -y cmake
    sudo apt install -y g++
    sudo apt install -y vim
    sudo apt install -y jq

    #sudo apt install -y icdiff
    #sudo apt install -y libgoogle-glog-dev
    #sudo apt install -y libgtest-dev
}

function do_install_dependency() {
    sudo apt install -y cmake
    sudo apt install -y g++
    sudo apt install -y libreadline-dev

    ##sudo apt install libevent-dev -y
    #
    #sudo apt install libgoogle-glog-dev -y
    #
    #sudo apt install libgtest-dev -y
    #
    ##sudo apt install libncurses5-dev libncursesw5-dev -y
    #
    ##sudo apt install libprotobuf-dev -y
    #
    ##sudo apt install protobuf-compiler -y
}

function do_lastlog() {
    lastlog $@ | awk '
        NR > 1 && NF > 6 {
            user = $1
            time = $(NF-5) FS $(NF-4) FS $(NF-3) FS $(NF-2) FS $(NF-1) FS $NF
            cmd = "date -d\""time"\" +\"%Y-%m-%d %H:%M:%S %z\""
            cmd | getline time
            close(cmd)
            printf("%s => %s\n", time, user)
        }' | sort
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
            printf("%s %10s %6s %4s => %s\n", $1, $2, $3, $4, cmd)
        }'
}

cmd=$1
shift
do_$cmd $@

