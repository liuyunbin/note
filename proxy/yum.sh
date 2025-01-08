#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

function do_test() {
    sudo yum clean all;            # 清空软件源缓存
    sudo sed -i "s|proxy=.*|proxy=$1|g" /etc/yum.conf
    sudo yum makecache;            # 新建软件源缓存
}

do_test http://host-60:8001



