
## 常用命令
```
c++filt  a.out    # 可以解析动态库里的符号 -- 常用

g++ -0g main.cc
g++ -01 main.cc
g++ -02 main.cc
g++ -03 main.cc
g++ -g  main.cc   # 生成 gdb 的文件

g++ -fPIC -shared test.cc -o libtest.so

gdb [a.out] [pid]            # 启动 gdb               -- 常用
gdb> file a.out              # 设置可执行文件         -- 常用
gdb> set args	             # 设置程序启动命令行参数 -- 常用
gdb> show args	             # 查看设置的命令行参数
gdb> run [arguments]         # 运行程序(r)            -- 常用
gdb> attach pid              # gdb 正在运行的程序     -- 常用
gdb> info breakpoints        # 列出断点信息(i)        -- 常用
gdb> break file:line         # 在指定行设置断点(b)    -- 常用
gdb> break function          # 在制定函数设置断点(b)
gdb> break function if b==0  # 根据条件设置断点(b)
gdb> tbreak file:line        # 在指定行设置临时断点(tb)
gdb> disable breakpoints num # 禁用断点 num          -- 常用
gdb>  enable breakpoints num # 启用断点 num          -- 常用
gdb>  delete breakpoints num # 删除断点 num
gdb> clear   line            # 清除指定行的断点
gdb> continue [num]          # 继续运行到指定断点(c) -- 常用
gdb> until     line          # 运行到指定行(u)       -- 常用
gdb> jump      line          # 跳转到指定行(j), 和 until 的区别是跳过的代码不会执行
gdb> next     [num]          # 继续运行多次(n)       -- 常用
gdb> step                    # 进入函数(s)           -- 常用
gdb> finish                  # 退出函数(fin), 会执行完当前函数 -- 常用
gdb> return ...              # 退出函数, 并指定返回值, 和 finish 的区别是不会继续执行之后的代码, 直接返回
gdb> print v                 # 输出变量的值(p)       -- 常用
gdb> print v=123             # 修改变量的值(p)
gdb> p *pointer              # 输出指针指向的值
gdb> p arr[1]@3              # 输出数组 arr[1] 开始的3个元素
gdb> p/t var                 # 按  二进制格式显示变量
gdb> p/o var                 # 按  八进制格式显示变量
gdb> p/d var                 # 按  十进制格式显示变量
gdb> p/u var                 # 按  十进制格式显示无符号整型
gdb> p/x var                 # 按十六进制格式显示变量        -- 常用
gdb> p/a var                 # 按十六进制格式显示地址
gdb> p/c var                 # 按字符格式显示变量
gdb> p/f var                 # 按浮点数格式显示变量
gdb> p/s var                 # 字符串
gdb>         display v       # 和 p 类似, 但后续会自动输出变量的值
gdb> disable display num     # 暂时取消输出
gdb>  enable display num     # 恢复输出
gdb>  delete display num     # 删除自动输出变量的值的编号
gdb>       undisplay num     # 删除自动输出变量的值的编号
gdb> info    display         # 列出自动打印变量的值
gdb> x/8xb &v                # 输出 double 的二进制表示 -- 常用
gdb> x/nfu  v                # n 表示打印多少个内存单元
                             # f 打印格式, x d u o t a c f(默认8位)
                             # u 内存单元, b=1 h=2 w=4 g=8
                             # x 和 p 的区别
                             #   * p 的参数是变量的值, x 的参数是变量的地址
                             #   * p 打印的单位长度即是变量的长度, x 可以指定单位长度
                             #   * x 可以打印连续的多个单位长度(这个可以方便看 double 的每一个字节的内容)
gdb> list                    # 显示当前行之后的源程序(l) -- 常用
gdb> list -                  # 显示当前行之前的源程序
gdb> list 2,10               # 显示 2 - 10 行的源程序
gdb>  set listsize 20        # 设置列出源码的行数
gdb> show listsize           # 输出列出源码的行数
gdb> set  print elements 0   # 设置打印变量长度不受限制 -- 常用
gdb> show print elements
gdb> backtrace               # 显示堆栈信息(bt)        -- 常用
gdb> frame     n             # 查看指定层的堆栈信息(f) -- 常用
gdb> thread	                 # 切换到指定线程
gdb> watch	                 # 监视某一个变量的值是否发生变化
gdb> ptype	                 # 查看变量类型
```

