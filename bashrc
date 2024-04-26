
PS1='\[\e[1m\]$(date "+%Y-%m-%d %H:%M:%S %z") \[\e[0m\]'

note=~/github/note
PATH=$PATH:$note

alias c="cd $note; pwd"
alias g="g++ -g -std=c++11"
alias lastlog="tool.sh lastlog"
alias l="ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrt"
alias m="make"
alias p="tool.sh ps"
alias t="./a.out"
alias v='vim'
alias x='tar xvf'
alias z='tar acf'

