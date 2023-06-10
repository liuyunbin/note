#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

lyb="123
456
"

echo "$lyb"
