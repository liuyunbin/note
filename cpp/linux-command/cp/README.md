
#### 简介：
本程序用于实现 Linux 命令 cp

#### cp A B 情况的分类：
1. A 不存在，直接失败
2. A 和 B 相同，直接退出
3. A 是文件，B 是文件 且 存在，直接拷贝即可
4. A 是文件，B 是目录 且 存在，获取 A 的文件名 name，相当于 cp A B/name
5. A 是文件，B 不存在，
    * 若 B 是形如 X/ 的形式，直接失败
    * 否则，直接拷贝即可
6. A 是目录，B 是文件 且 存在，直接失败
7. A 是目录，B 是目录 或 不存在
    * 若 B 是目录，获取最后一个目录 dir，相当于 cp A B/dir
    * 然后，将 源目录 和 目的目录 构成一个 pair，加入一个队列，依次取出队列中的元素 data，进行如下操作，直到队列为空
        * 如果 data.second.data() 存在 且 是文件，直接失败
        * 如果 data.second.data() 不存在，新建 此目录
        * 打开目录 data.first.data()，依次遍历元素 v，
            * 如果 v 是文件，直接拷贝，相当于 cp data.first.data()/v data.second.data()/v
            * 如果 v 是目录，将 make_pair(data.first.data()/v, data.second.data()/v)  打入队列

#### 例子：
```
$ cp A  B    # 文件 --> 文件
$ cp A  B/   # 文件 --> 目录
$ cp A/ B/   # 目录 --> 目录
```

#### 说明：
本程序未处理一半成功，一般失败的情况，即：遇到失败，直接退出，可能部分拷贝成功

#### 参考资源：
* [unix/linux 编程实践教程](https://book.douban.com/subject/1219329/)

