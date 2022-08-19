#!/bin/bash
set -o nounset  # 使用未初始化的变量报错, 同 -u
set -o errexit  # 只要发生错误就退出 -e
set -o pipefail # 只要管道发生错误就退出
set -E          # 即使意外退出, 也会执行 trap 命令

#set -o xtrace   # 执行前打印命令 同 -x

function log_info() {
  # 黑色
  echo -e "\033[37;1m[$(date +'%Y-%m-%d %H:%M:%S') info]: $@\033[0m"
}

function log_warn() {
  # 黄色
  echo -e "\033[33;1m[$(date +'%Y-%m-%d %H:%M:%S') warn]: $@\033[0m"
}

function log_fatal() {
  # 红色
  echo -e "\033[31;1m[$(date +'%Y-%m-%d %H:%M:%S') fatal]: $@\033[0m"
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
log_fatal fatal

