
## 简介
* ClangFormat 是一个规范代码的工具
* ClangFormat 支持的语言有: C/C++/Java/JavaScript/Objective-C/Protobuf/C#
* ClangFormat 支持的规范有: LLVM, Google, Chromium, Mozilla 和 WebKit

## 安装
```
$ sudo yum install clang-format -y
$ sudo apt install clang-format -y
```

## 作为单独的命令使用
```
$ clang-format    main.cc                                  # 预览规范后的代码
$ clang-format -i main.cc                                  # 直接在原文件上规范代码
$ clang-format -style=Google main.cc                       # 显示指明代码规范，默认为 LLVM
$ clang-format --dump-config -style=Google > .clang-format # 将代码规范配置信息写入文件 .clang-format
$ clang-format -style=file main.cc                         # 使用自定义代码规范,
                                                           # 规范位于当前目录或任一父目录的文件
                                                           # 的 .clang-format 或 _clang-format 中,
                                                           # (如果未找到文件，使用默认代码规范)
```

## 在 Vim 中使用
1. 查找文件 clang-format.py 所在的目录

        $ dpkg -L clang-format | grep clang-format.py

2. 在 .vimrc 中加入以下内容

        function! Formatonsave()
            let l:formatdiff = 1
            py3f <path-to-this-file>/clang-format.py
        endfunction
        autocmd BufWritePre *.h,*.cc,*.cpp,*.c call Formatonsave()

### 说明：
```
1. 上述的内容表示: 当使用 Vim 保存文件时,
    会按照当前目录 或 任一父目录的文件 .clang-format 或 _clang-format 指定的规范来规范代码
    (如果未找到文件，使用默认代码规范)
2. 上述 `<path-to-this-file>` 指的是 clang-format.py 的目录
3. `let l:formatdiff = 1` 的意思是只规范修改过的部分, 可以用 `let l:lines = "all"` 取代, 表示规范所有的内容
4. 在 Ubuntu 18.04 LTS 下, clang-format 的默认版本为 clang-format-6.0
   clang-format-6.0 的 clang-format.py 使用的是 Python 3
   而 Ubuntu 18.04 LTS 默认的 Python 版本为 Python 2.7, 所以上面使用的是 py3f 而不是 pyf
```

## 参考资源
* clang-format  -> https://clang.llvm.org/docs/ClangFormat.html
* clang-format  -> https://clang.llvm.org/docs/ClangFormatStyleOptions.html
* askubuntu     -> https://askubuntu.com/questions/730609/how-can-i-find-the-directory-to-clang-format
* stackoverflow -> https://stackoverflow.com/a/39781747/7671328

