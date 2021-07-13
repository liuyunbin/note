
tar -cvf  /path/to/foo.tar --exclude=\*.o /path/to/foo/ # foo         --> foo.tar, 忽略 .o 文件
tar -cvf  /path/to/foo.tar                /path/to/foo/ # foo         --> foo.tar
tar -czvf /path/to/foo.tgz                /path/to/foo/ # foo         --> foo.tgz
tar -czvf /path/to/foo.tar.gz             /path/to/foo/ # foo         --> foo.tar.gz
tar -cjvf /path/to/foo.tar.bz2            /path/to/foo/ # foo         --> foo.tar.bz2
tar -xvf  /path/to/foo.tar                              # foo.tar     --> foo
tar -xzvf /path/to/foo.tgz                              # foo.tgz     --> foo
tar -xzvf /path/to/foo.tar.gz                           # foo.tar.gz  --> foo
tar -xjvf /path/to/foo.tar.bz2                          # foo.tar.bz2 --> foo
tar -xjvf /path/to/foo.tar.bz2 -C /path/to/destination/ # foo.tar.bz2 --> foo, 指定工作目录

