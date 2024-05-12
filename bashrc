
PS1='\[\e[1m\]$(date "+%Y-%m-%d %H:%M:%S %z") \[\e[0m\]'

note=~/github/note
PATH=$PATH:$note

alias ls_atime="ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtu" # 以 文件访问时间     排序, 不准确
alias ls_mtime="ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrt"  # 以 文件内容修改时间 排序
alias ls_ctime="ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtc" # 以 文件属性修改时间 排序
alias lsd="ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtd" # 以 文件内容修改时间 排序, 只列出目录本身
alias lss="ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrS"  # 以 文件大小         排序
alias lsv="ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrv"  # 以 文件名为版本号   排序

alias c="cd $note; pwd"
alias g="g++ -g -std=c++11"
alias lastlog="tool.sh lastlog"
alias lnet="tool.sh lnet"
alias l=ls_mtime
alias m="make"
alias p="tool.sh ps"
alias t="./a.out"
alias v='vim'
alias x='tar xvf'
alias z='tar acf'

