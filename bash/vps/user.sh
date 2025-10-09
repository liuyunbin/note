#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

USERNAME=lyb
PASSWORD=654321

log_info "1. 添加用户"
useradd -m -s /bin/bash $USERNAME || true

log_info "2. 设置密码"
echo $USERNAME:$PASSWORD | chpasswd

log_info "3. 赋予 sudo 权限"
chmod +w /etc/sudoers
grep -q $USERNAME /etc/sudoers || echo "$USERNAME ALL=(ALL:ALL) ALL" >> /etc/sudoers
chmod -w /etc/sudoers

log_info "4. 禁止用户使用 ssh 登录"
grep -q $USERNAME /etc/ssh/sshd_config || echo "DenyUsers $USERNAME" >> /etc/ssh/sshd_config
systemctl restart ssh

log_info "5. 切换用户"
su - $USERNAME

