#!/bin/bash

set -eux

path_for_clang_format_py=$(dpkg -L clang-format | grep clang-format.py)

function config_clang_format_for_vim {
cat << EOF
function! Formatonsave()
    let l:formatdiff = 1
    py3f ${path_for_clang_format_py}/clang-format.py
endfunction
autocmd BufWritePre *.h,*.cc,*.cpp call Formatonsave()"
EOF
}

config_clang_format_for_vim >> ~/.vimrc
