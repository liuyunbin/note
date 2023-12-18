#!/bin/bash

set -eux

cat <<EOF >> ~/.vimrc
function! Formatonsave()
    let l:lines = "all"
    py3f $(dpkg -L clang-format | grep clang-format.py)
endfunction
autocmd BufWritePre *.h,*.cc,*.cpp,*.c call Formatonsave()
EOF
