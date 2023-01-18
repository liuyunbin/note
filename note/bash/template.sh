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

function usage() {
  cat <<EOF
使用说明:
  这是一个脚本模板
  使用例如:
    $(basename $0) -h     # 帮助文档
    $(basename $0) -a 123 # 测试
EOF
  exit 0
}

while getopts ":ha:" arg; do
  case "$arg" in
    h)
      usage
      exit 0
      ;;
    a)
      val="$OPTARG"
      echo "$OPTARG"
      ;;
    :)
      echo "$(basename $0) 可选项要求参数 -- '$OPTARG'"
      echo "使用 '$(basename $0) -h' 获取帮助信息"
      exit -1
      ;;
    ?)
      echo "$(basename $0) 非法参数 -- '$OPTARG'"
      echo "使用 '$(basename $0) -h' 获取帮助信息"
      exit -1
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

