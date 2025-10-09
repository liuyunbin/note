#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

log_info "0. 安装 vim"
sudo apt -y -qq install vim &> /dev/null

log_info "1. 配置 vimrc"
cp ~/github/note/vim/vimrc ~/.vimrc

