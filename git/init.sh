#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

log_info "0. 安装软件"
sudo apt -y -qq install git icdiff &> /dev/null

log_info "1. 配置用户名"
git config --global user.name "Yunbin Liu"

log_info "2. 配置邮箱"
git config --global user.email yunbinliu@outlook.com

log_info "3. 配置编辑器"
git config --global core.editor vim

log_info "4. 配置日期格式"
git config --global log.date iso

log_info "5. 配置简要命令"
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status

log_info "6. 配置日志显示格式"
git config --global alias.lg "log --pretty=format:'%ad %h %s %d %C(bold)%an%Creset' --graph"

log_info "7. 中文显示不乱码"
git config --global core.quotepath false

log_info "8. 查看配置"
git config --global --list

log_info "9. 生成秘钥"
[[ -f ~/.ssh/id_ed25519.pub ]] || ssh-keygen -t ed25519

log_info "10. 复制公钥到 GitHub, 按回车继续..."
read

log_info "11. 测试连接"
ssh -T git@github.com

