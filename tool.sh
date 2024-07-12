#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_warn() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

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
        argv=$argv$(pgrep -d, $key || log_erro "not find $key")
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

function do_lsnet() {
     sudo ss -Htlnp | \
         awk '{print $4, $6}' | \
         awk '{
             sub(/users.*pid=/, "");
             sub(/,fd.*/, "");
             sub(/.*:/, "");
             print
         }' | sort -n | uniq | awk '{
                 cmd = "ps -o pid,user,comm --no-headers -p " $2;
                 cmd | getline detail;
                 close(cmd);
                 print $1, detail }' | column -t
}

function do_init_git() {
    log_info "配置 Git"
    git config --global user.name "Yunbin Liu"
    git config --global user.email yunbinliu@outlook.com
    git config --global core.editor vim
    git config --global log.date iso
    git config --global alias.lg "log --pretty=format:'%ad %h %s %d %C(bold)%an%Creset' --graph"
    git config --global core.quotepath false
#    log_info "查看 Git 配置"
#    git config --global --list
    log_info "生成密钥"
    [[ -f ~/.ssh/id_rsa.pub ]] || ssh-keygen -t rsa
    cat ~/.ssh/id_rsa.pub
    read -p "复制上述公钥到 GitHub, 然后按回车继续"
    log_info "测试是否成功"
    ssh -T git@github.com
}

# 一般没人看到吧
DOMAIN=yunbinliu.com
USER=yunbinliu
PASS=lyb2636196546
PORT=443
SERVICE=https

function handle_certbot() {
    log_info "安装 certbot..."
    if ! which certbot &> /dev/null; then
        apt install snapd &> /dev/null
        snap install --classic certbot &> /dev/null
        ln -s /snap/bin/certbot /usr/bin/certbot
    fi
#    log_info "签证书: $DOMAIN"
    if ! certbot certificates 2> /dev/null | grep "$DOMAIN" &> /dev/null;then
        certbot certonly --standalone -d "$DOMAIN" &> /dev/null
    fi
}

function handle_docker() {
    log_info "安装 docker..."
    if ! which docker &> /dev/null; then
        curl -fsSL https://get.docker.com -o get-docker.sh &> /dev/null
        sh get-docker.sh &> /dev/null
        rm -rf get-docker.sh
    fi
    systemctl start  docker &> /dev/null || true
    systemctl enable docker &> /dev/null
}

function handle_gost() {
    log_info "安装 gost..."
    if ! docker ps -a --format "{{.Names}}" | grep gost &> /dev/null; then
        BIND_IP=0.0.0.0
        CERT_DIR=/etc/letsencrypt
        CERT=${CERT_DIR}/live/${DOMAIN}/fullchain.pem
        KEY=${CERT_DIR}/live/${DOMAIN}/privkey.pem

        docker run -d \
            --name gost \
            -v ${CERT_DIR}:${CERT_DIR}:ro \
            --net=host ginuerzh/gost \
            -L "http2://${USER}:${PASS}@${BIND_IP}:${PORT}?cert=${CERT}&key=${KEY}&probe_resist=code:400&knock=www.google.com"
    fi

    log_info "启动 gost..."
    if ! docker ps --format "{{.Names}}" | grep gost &> /dev/null; then
        docker start gost &> /dev/null
    fi
}

function handle_firewalld() {
    log_info "处理防火墙..."
    apt install -y   firewalld &> /dev/null
    systemctl start  firewalld &> /dev/null || true
    systemctl enable firewalld &> /dev/null
    firewall-cmd --add-service=${SERVICE} --permanent --zone=public &> /dev/null
    firewall-cmd --reload > /dev/null
}

function handle_crontab() {
    log_info "添加定时任务: 更新证书..."
    cmd="certbot renew --force-renewal"
    if ! crontab -l 2> /dev/null | grep "$cmd" &>/dev/null; then
        echo "0 0 1 * * $cmd" >> /var/spool/cron/crontabs/root
    fi

    log_info "添加定时任务: 重启 gost..."
    cmd="docker restart gost"
    if ! crontab -l 2> /dev/null | grep "$cmd" &>/dev/null; then
        echo "5 0 1 * * $cmd" >> /var/spool/cron/crontabs/root
    fi
}

function do_init_vps() {
    log_info "更新系统..."
    apt -y update  &> /dev/null
    apt -y upgrade &> /dev/null
    log_info "安装常用软件..."
    apt install -y git vim &> /dev/null

    handle_certbot
    handle_docker
    handle_gost
    handle_firewalld
    handle_crontab

#    apt install -y man-db
#    unminimize -y
    log_info "完成"
}

cmd=$1
shift
do_$cmd $@

