#!/bin/bash
set -ueo pipefail

function log_info() { echo -e "\033[00m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_warn() { echo -e "\033[33m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty;          }
function log_erro() { echo -e "\033[31m$(date +'%Y-%m-%d %H:%M:%S %z') $@\033[0m" > /dev/tty; exit -1; }

cmd=$(basename $0)

function usage() {
  log_info "说明:"
  log_info "    这是一个脚本模板"
  log_info "使用例如:"
  log_info "    $cmd -h     # 帮助文档"
  log_info "    $cmd -a 123 # 测试"
  exit 0
}

while getopts ":ha:" arg; do
  case "$arg" in
    h)
      usage
      exit 0
      ;;
    a)
      log_info "a 的参数为 $OPTARG"
      ;;
    :)
      log_info "可选项要求参数 -- '$OPTARG'"
      log_erro "请使用 '$cmd -h' 获取帮助信息"
      ;;
    ?)
      log_info "非法参数 -- '$OPTARG'"
      log_erro "请使用 '$cmd -h' 获取帮助信息"
      ;;
  esac
done

shift $(($OPTIND - 1))

log_info info
log_info info
log_info info
log_info info
log_info info
log_info info
log_info info
log_warn warning
log_erro fatal

