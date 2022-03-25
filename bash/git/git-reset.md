## 一步一步探索 git reset
* 为求简单, 本文只考虑初始状态 Git 仓库, 缓存区域 和 当前目录 相同的情况
* 本文的源地址: https://github.com/liuyunbin/liuyunbin-toys/blob/master/bash/git/git-reset.md
* 在同一目录下, 有相关的测试脚本

### 本文使用的 Git 版本
```
$ git version
git version 2.30.1
```

### 探索如下
#### 构建一个测试目录
```
$ rm -r test
$ mkdir -p test && cd test
$
$ git init
$
$ echo a > 1.txt
$ git add 1.txt
$ git commit -m "A"
$
$ echo b > 1.txt
$ git add 1.txt
$ git commit -m "B"
$
$ echo c > 1.txt
$ git add 1.txt
$ git commit -m "C"
$
$ echo d > 1.txt
$ git add 1.txt
$ git commit -m "D"
```

此时的提交记录是 A --> B --> C --> D, Git 仓库, 暂存区, 当前目录都是 D

#### 如果执行 `git reset --soft HEAD~2` 会有以下行为
1. 将 HEAD 指向 HEAD~2 (B)
2. 此时, Git 仓库是 B, 暂存区 和 当前目录 是 D
3. 此时, 查看 仓库状态如下

```
$ git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
    modified:   1.txt
```

#### 如果执行 `git reset --mixed HEAD~2` 会有以下行为
1. 将 HEAD 指向 HEAD~2 (B)
2. 将暂存区域中 HEAD (B) 之后的数据移到当前目录
3. 此时, Git 仓库 和 暂存区域 是 B, 当前目录 是 D
4. 此时, 查看 仓库状态如下

```
$ git status
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

#### 如果执行 `git reset HEAD~2` 会有以下行为
这个同 `git reset --mixed HEAD~2`

#### 如果执行 `git reset --hard HEAD~2` 会有以下行为
1. 将 HEAD 指向 HEAD~2 (B)
2. 删除 暂存区域, 当前目录中 HEAD (B) 之后的数据
3. 此时, Git 仓库, 暂存区域 和 当前目录 都是 B
4. 此时, 查看 仓库状态如下

```
$ git status
On branch master
nothing to commit, working tree clean
```

#### 如果执行 `git reset HEAD~2 -- 1.txt` 会有以下行为
1. 将暂存区域中 HEAD 之后的数据移到当前目录
2. 将 Git 仓库 HEAD~2 的 1.txt 加入暂存区
3. 此时, Git 仓库 和 当前目录为 D, 暂存区域中的 1.txt 是 B
4. 此时, 查看 仓库状态如下

```
$ git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
    modified:   1.txt

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
    modified:   1.txt
```

#### 如果执行 `git reset --mixed HEAD~2 -- 1.txt` 会有以下行为
这个同 `git reset --mixed HEAD~2`, 该命令已过时

## 参考资源
* https://git-scm.com/book/zh/v2/Git-%E5%B7%A5%E5%85%B7-%E9%87%8D%E7%BD%AE%E6%8F%AD%E5%AF%86

