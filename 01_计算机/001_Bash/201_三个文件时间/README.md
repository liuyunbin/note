
#### 文件的三个时间
* atime: 文件内容最后被读取的时间--更新可能不及时
* mtime: 文件内容被修改的时间
* ctime: 状态修改时间
    * 文件内容修改
    * 文件名称修改: mv, rename
    * 所有者, 所属组变化: chown
    * 权限修改: chmod

#### 查看 文件的三个时间
```
$ stat -c  %x 1.txt # atime 人类可读的形式
$ stat -c  %X 1.txt # atime 时间戳
$ stat -c  %y 1.txt # mtime 人类可读的形式
$ stat -c  %Y 1.txt # mtime 时间戳
$ stat -c  %z 1.txt # ctime 人类可读的形式
$ stat -c  %Z 1.txt # ctime 时间戳
$ ls   -lu    1.txt # atime 人类可读的形式
$ ls   -lt    1.txt # mtime 人类可读的形式
$ ls   -lc    1.txt # ctime 人类可读的形式
```

#### 修改三个时间
```
$ touch    1.txt # 修改 atime mtime ctiem
$ touch -a 1.txt # 修改 atime
$ touch -m 1.txt # 修改       mtime ctime
```

#### 出于性能考虑，在内核 2.6.30 之后 只有以下情况会更新 atime
* atime 比 mtime 或 ctime 旧
* atime 比上一次 atime 超过 24 小时
* mount 时, 使用了 strictatime 选项

#### 例子
* 只修改 atime: cat 1.txt
* 只修改 ctime: chmod +x 1.txt
* 同时修改 mtime 和 ctime: echo "123" >> 1.txt
* 同时修改 atime, mtime 和 ctime: 使用 vim 编辑并保存

