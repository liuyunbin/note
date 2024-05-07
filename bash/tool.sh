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

function do_lnet() {
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

cmd=$1
shift
do_$cmd $@

