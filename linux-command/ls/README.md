
#### 简介：
本程序用于实现 Linux 命令 ls

为图简单，本程序未使用命令行参数，直接列出文件详细信息

#### 程序主要解决的问题：
1. 使用 getpwuid() 将用户 ID 转换为用户名
2. 使用 getgrgid() 将组   ID 转化为组名
3. 使用 opendir()  打开目录
4. 使用 readdir()  读取目录
5. 使用 closedir() 关闭目录
6. 使用 fstatat() 和 dirfd() 获取在指定目录下的文件的信息

#### 例子：
```
$ ls main.cc
$ ls /tmp
$ ls
```

#### 参考资源：
* [unix/linux 编程实践教程](https://book.douban.com/subject/1219329/)

