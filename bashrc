

if [[ $UID == 0 ]]; then
    PS1='\[\e[1m\]$(date "+%Y-%m-%d %H:%M:%S %z") # \[\e[0m\]'
else
    PS1='\[\e[1m\]$(date "+%Y-%m-%d %H:%M:%S %z") $ \[\e[0m\]'
fi

note=~/github/note
PATH=$PATH:$note/bash

alias lsatime="    ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtu" # 以 文件访问时间     排序, 不准确
alias lsmtime="    ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrt"  # 以 文件内容修改时间 排序
alias lsctime="    ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtc" # 以 文件属性修改时间 排序
alias lsdirectory="ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtd" # 以 文件内容修改时间 排序, 只列出目录本身
alias lssize="     ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrS"  # 以 文件大小         排序
alias lsversion="  ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrv"  # 以 文件名为版本号   排序

alias c="cd $note; pwd"
alias d="certbot certificates"
alias g="g++ -g -std=c++14"
alias lastlog="tool.sh lastlog"
alias lsnet="tool.sh lsnet"
alias l=lsmtime
alias m="make"
alias p="tool.sh ps"
alias t="tool.sh test"
alias v='vim'
alias x='tar xvf'
alias z='tar acf'

