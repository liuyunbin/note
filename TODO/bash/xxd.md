
## 相关命令
```
xxd -b     1.txt  # 输出二进制而不是十六进制
xxd -e     1.txt  # 使用小端模式
xxd -g ... 1.txt  # 每组的字节数            -- 建议使用, 读取的顺序和存储的顺序相同, 不需要考虑字节序

hd         1.txt # 每组一个字节 显示十六进制+ASCII -- 不建议使用, 得考虑字节序
hexdump -b 1.txt # 每组一个字节 显示八进制
hexdump -c 1.txt # 每组一个字节 显示字符
hexdump -C 1.txt # 每组一个字节 显示十六进制+ASCII
hexdump -d 1.txt # 每组两个字节 显示  十进制
hexdump -o 1.txt # 每组两个字节 显示  八进制
hexdump -x 1.txt # 每组两个字节 显示十六进制

od -t a   1.txt # 每组一个字节, 显示字符(nl) -- 不建议使用, 得考虑字节序
od -t c   1.txt # 每组一个字节, 显示字符(\n)
od -t d4  1.txt # 每组四个字节, 显示有符号的十进制数字
od -t f4  1.txt # 每组四个字节, 显示浮点数
od -t o4  1.txt # 每组四个字节, 显示  八进制数字
od -t u4  1.txt # 每组四个字节, 显示无符号的十进制数字
od -t x4  1.txt # 每组四个字节, 显示十六进制数字
od -t d4z 1.txt # 每组四个字节, 显示十进制数字, 并显示原始字符
od -a     1.txt # 同 -t a
od -b     1.txt # 同 -t o1
od -c     1.txt # 同 -t c
od -d     1.txt # 同 -t u2
od -f     1.txt # 同 -t f
od -i     1.txt # 同 -t dI
od -l     1.txt # 同 -t dL
od -o     1.txt # 同 -t o2
od -s     1.txt # 同 -t d2
od -x     1.txt # 同 -t x2
od --endian={big|little} 1.txt # 指明大小端
```

