#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

bashrc_path=$(ls ~/github/note/bash/bashrc)

log_info "1. 配置 bashrc"
grep -q $bashrc_path ~/.bashrc ||  echo ". $bashrc_path" >> ~/.bashrc

log_info "2. 请执行 '. ~/.bashrc'"

