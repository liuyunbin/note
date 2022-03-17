## 简介
Git 是一个分布式版本管理的工具

## 安装
```
$ sudo apt install git
```

## 配置
#### 配置用户名
```
$ git config user.name liuyunbin --system # 整个系统中的项目配置
$ git config user.name liuyunbin --global # 某个用户下的项目配置
$ git config user.name liuyunbin --local  #   单独的某个项目配置
$ git config user.name liuyunbin          #   单独的某个项目配置
```

#### 配置邮箱
```
$ git config user.email yunbinliu@outlook.com --system # 整个系统中的项目配置
$ git config user.email yunbinliu@outlook.com --global # 某个用户下的项目配置
$ git config user.email yunbinliu@outlook.com --local  #   单独的某个项目配置
$ git config user.email yunbinliu@outlook.com          #   单独的某个项目配置
```

#### 配置默认编辑器
```
$ git config core.editor vim --system # 整个系统中的项目配置
$ git config core.editor vim --global # 某个用户下的项目配置
$ git config core.editor vim --local  #         某个项目配置
$ git config core.editor vim          #         某个项目配置
```

#### 检查配置信息
```
$ git config --list --system # 整个系统中的项目配置
$ git config --list --global # 某个用户下的项目配置
$ git config --list --local  #         某个项目配置
$ git config --list          #         某个项目配置
```

#### 生成密钥
```
$ ssh-keygen -t rsa -b 4096 -C yunbinliu@outlook.com
```

#### 复制公钥到 GitHub
将文件 ~/.ssh/id_rsa.pub 里的公钥添加到：https://github.com/settings/keys

## 使用
### 三个工作区域：
1. Git 仓库
2. 暂存区域
3. 工作目录

### 文件和目录的分类：
1. 未跟踪的（untracked），位于工作目录
2. 已暂存的（staged），属于暂存区域，位于 Git 仓库目录
3. 已提交的（committed），位于 Git 仓库目录
4. 已修改的（modified），位于工作目录
5. 已忽略的文件或目录，位于工作目录

### 忽略文件或目录
在文件 .gitignore 中添加要忽略的文件或目录，规则如下：
1. 空行或以 `#` 开头的行将被忽略
2. 以 `/` 开头防止递归
3. 以 `/` 结尾表示目录
4. 以 `!` 开头，表示不忽略文件或目录
5. `*` 匹配任意字符（不包括 `/`）
6. `**` 匹配任意字符
7. `[abc]` 表示匹配方括号内的任意单个字符
8. `[0-9]` 表示匹配范围 [0, 9] 内的任意单个个字符
9. `?` 匹配任意单个字符

### Git 常用命令
**注意：以下说明中均不包含被忽略的文件和目录**

```
$ git init # 初始化仓库
$
$ git clone https://github.com/liuyunbin/liuyunbin-toys # 克隆仓库
$ git clone git@github.com:liuyunbin/liuyunbin-toys     # ssh 协议
$ git clone git@github.com:liuyunbin/liuyunbin-toys.git
$
$ git add README # 未跟踪 或 已修改 ----> 已暂存
$                # 合并时把有冲突的文件标记为已解决状态
$
$ git restore --staged <file>... # 已跟踪(已暂存) --> 未跟踪
$
$ git commit -m "message"    # 已暂存 --> 已提交
$ git commit -a -m "message" # 跳过使用暂存区域，直接提交
$ git commit --amend         # 修改最后一次的提交信息，或增加提交的文件
$
$ git status         # 列出文件状态
$ git status  -s     # 显示简短信息
$ git status --short # 显示简短信息
$
$ git diff           #   已修改 和 暂存区域 的差异
$ git diff --staged  # 暂存区域 和 Git 仓库 的差异
$ git diff --cached  # 暂存区域 和 Git 仓库 的差异
$
$ git rm          README   # 从暂存区域内移除文件，同时在工作目录中删除
$ git rm  -f      README   # 强行删除, 包括 暂存区
$ git rm --cached README   # 从暂存区域内移除文件，工作目录中的文件保留
$
$ git mv file_from file_to # 移动文件或目录
$
$ git log
$ git log --stat              # 显示简略统计信息
$ git log --shortstat         # 只显示添加移除信息
$ git log  -p                 # 显示修改的内容
$ git log --patch
$ git log  -2                 # 显示近两次的提交
$ git log --oneline           # 每个提交一行
$ git log --pretty=oneline    # 每个提交一行
$ git log --graph --oneline   # 显示分支的合并
$ git log --name-only         # 显示修改的文件清单
$ git log --name-status       # 显示修改的文件信息, 增删改
$ git log --after=2021-07-16
$ git log --since=2021-07-16
$ git log --before=2021-07-16
$ git log --after=2021-07-16
$ git log --author=liuyunbin
$ git log a..b                         # 不在 a 中, 在 b 中的提交
$ git log ^a b                         # 不在 a 中, 在 b 中的提交
$ git log --not a b                    # 不在 a 中, 在 b 中的提交
$ git log a...b                        # 在 a 或 b 中, 但不同时在 a 且 b 中的提交
$ git log -L :git_deflate_bound:zlib.c # 查询某一函数的变更记录
$
$ git reset HEAD~ --soft         # HEAD~ 之后的数据 已提交 ----> 已暂存
$ git reset HEAD~ --mixed        # HEAD~ 之后的数据 已提交 ----> 已暂存 ----> 已修改
$ git reset HEAD~                # HEAD~ 之后的数据 已提交 ----> 已暂存 ----> 已修改
$ git reset HEAD~ --hard         # HEAD~ 之后的数据 已提交 ----> 已暂存 ----> 已修改 --> 上次提交
$ git reset HEAD~ README         # 此时 当前目录 和 HEAD 相同, 之前已暂存 ----> 已修改
$ git reset HEAD~ README --mixed # 暂存区域中的 README 和 HEAD~ 的 README 相同
$
$ git checkout    -- README # 已修改 ----> 上次提交
$ git checkout HEAD~ README # 当前目录 和 暂存区域中的 README 和 HEAD~ 的 README 相同
$
$ git remote -v                    # 查看远程仓库
$ git remote add <shortname> <url> # 添加远程仓库
$ git remote rm     paul           # 删除远程仓库
$ git remote remove paul           # 删除远程仓库
$ git remote show origin           # 查看远程仓库的详细信息
$ git remote rename pb paul        # 重命名远程仓库
$
$ git fetch [remote-name] # 从远程仓库获取数据
$
$ git tag          # 列出标签
$ git tag -l "v*"  # 列出标签
$ git tag v1.0.0.0 # 创建标签
$ git tag -d v1.5  # 删除本地 tag
$
$ git push origin v1.5                            # 将 tag 推送到远程
$ git push origin --delete v1.5                   # 删除远程 tag
$ git push origin --tags                          # 将 tag 推送到远程
$ git push origin master                          # 推送数据到远程仓库
$ git push origin --delete serverfix              # 删除远程分支
$ git push origin --set-upstream-to=orgin/develop # 本地分支和远程分支关联
$ git push origin -u orgin/develop                # 本地分支和远程分支关联
$
$ git branch                # 列出所有的本地分支
$ git branch -v             # 列出所有的本地分支, 以及最后一次提交
$ git branch --merged       # 列出已合并到本分支的本地分支
$ git branch --no-merged    # 列出未合并到本分支的本地分支
$ git branch test-branch    # 新建分支
$ git branch -d test-branch # 删除分支
$ git branch -D test-branch # 强制删除分支
$ git branch -r             # 查看远程分支
$
$ git ls-remote (remote)    # 查看远程分支
$
$ git checkout test-branch              # 切换分支
$ git checkout -b test-branch           # 新建并切换分支
$ git checkout --orphan test-branch     # 新建并切换到独立分支
$ git checkout --track origin/serverfix # 新建并关联到远程分支
$ git checkout serverfix                # 本地分支不存在, 且 远程分支存在, 新建并关联到远程分支
$
$ git merge test-branch # 将 test-branch 合并到 当前分支
$
$ git pull # 拉取并合并数据
$
$ git rebase master server-branch # 将 server-branch 分支变基到 master
$
$ git stash                     # 贮藏工作
$ git stash --keep-index        # 贮藏工作, 同时将暂存的内容存在索引内
$ git stash --include-untracked # 贮藏工作, 同时贮藏未跟踪的文件, 不包括忽略的文件
$ git stash  -u                 # 贮藏工作, 同时贮藏未跟踪的文件, 不包括忽略的文件
$ git stash --all               # 贮藏工作, 同时贮藏未跟踪的文件,   包括忽略的文件
$ git stash  -a                 # 贮藏工作, 同时贮藏未跟踪的文件,   包括忽略的文件
$ git stash list                # 列出已贮藏的工作
$ git stash apply               # 恢复已贮藏的工作
$ git stash apply --index       # 恢复已贮藏的工作, 同时恢复暂存区
$ git stash drop                # 丢弃贮藏区的工作
$ git stash pop                 # 恢复已贮藏的工作, 并丢弃贮藏区的工作
```

## 参考资源
1. https://help.github.com/en/articles/set-up-git
2. https://git-scm.com/book/zh/v2

