## 简介
* Git 是一个分布式版本管理的工具
* 本文只列举 Git 最常用的功能
* Git 只是版本管理的工具, 未必需要做到, 知其然并知其所以然, 够用就好

## 安装
```
$ sudo apt install git
```

## 基本说明
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

## 使用
### 配置用户名
```
$ git config user.name liuyunbin --system # 整个系统中的项目配置
$ git config user.name liuyunbin --global # 某个用户下的项目配置
$ git config user.name liuyunbin --local  #   单独的某个项目配置
$ git config user.name liuyunbin          #   单独的某个项目配置
```

### 配置邮箱
```
$ git config user.email yunbinliu@outlook.com --system # 整个系统中的项目配置
$ git config user.email yunbinliu@outlook.com --global # 某个用户下的项目配置
$ git config user.email yunbinliu@outlook.com --local  #   单独的某个项目配置
$ git config user.email yunbinliu@outlook.com          #   单独的某个项目配置
```

### 配置默认编辑器
```
$ git config core.editor vim --system # 整个系统中的项目配置
$ git config core.editor vim --global # 某个用户下的项目配置
$ git config core.editor vim --local  #         某个项目配置
$ git config core.editor vim          #         某个项目配置
```

### 检查配置信息
```
$ git config --list --system # 整个系统中的项目配置
$ git config --list --global # 某个用户下的项目配置
$ git config --list --local  #         某个项目配置
$ git config --list          #         某个项目配置
```

### 生成密钥
```
$ ssh-keygen -t rsa -b 4096 -C yunbinliu@outlook.com
```

### 复制公钥到 GitHub, 到此可以免密码使用 GitHub
将文件 `~/.ssh/id_rsa.pub` 里的公钥添加到：https://github.com/settings/keys

### 其他常用命令
```
$ git init                                              # 初始化仓库
$
$ git clone https://github.com/liuyunbin/liuyunbin-toys # 克隆仓库
$ git clone git@github.com:liuyunbin/liuyunbin-toys     # ssh 协议
$ git clone git@github.com:liuyunbin/liuyunbin-toys.git
$ git clone --recurse-submodules https://github.com...  # 克隆包含子模块的项目
$
$ git add README # 未跟踪 或 已修改 --> 已暂存
$ git add README # 合并时把有冲突的文件标记为已解决状态
$
$ git commit -a -m "message" # 已修改 --> 已暂存 --> 已提交
$ git commit    -m "message" #            已暂存 --> 已提交
$
$ git reset HEAD~ --soft  # 已提交 --> 已暂存
$                         # 行为:
$                         #     * 将 HEAD 指针指向 HEAD~
$                         #     * 暂存区域 和 工作目录 的数据不变
$                         # 结果:
$                         #     * HEAD~ 之后的数据 已提交 --> 已暂存
$                         #     * 之前 已暂存 的数据保持不变
$
$ git reset HEAD~ --mixed # 已提交 或 已暂存 --> 已修改
$ git reset HEAD~         #
$                         # 行为:
$                         #     * 将 HEAD 指针指向 HEAD~
$                         #     * 使用 HEAD 指针的数据重置暂存区
$                         #     * 工作目录 的数据不变
$                         # 结果:
$                         #     * 之前 已暂存 的数据 --> 已修改
$                         #     * HEAD~ 之后的数据 已提交 --> 已修改
$                         #     * 执行此命令后, Git 仓库 和 暂存区域 数据相同
$
$ git reset HEAD~ --hard  # 已提交 --> 上次提交
$                         # 行为:
$                         #     * 将 HEAD 指针指向 HEAD~
$                         #     * 使用 HEAD 所指向的数据重置 暂存区域 和 工作目录
$                         # 结果:
$                         #     * 将 Git 仓库, 暂存区域 和 工作目录中 HEAD~ 之后的数据 都删除
$                         #     * 会丢失之前 已修改 或 已暂存 的数据
$
$ git reset HEAD~ README         # 使用 HEAD~ 的 README 替换 暂存区域 中的 README
$ git reset HEAD~ README --mixed
$                                # 行为:
$                                #      * 将 Git 仓库 HEAD~ 的 README 替换 暂存区中的 README
$                                #      * Git 仓库 和 工作目录 保持不变
$                                # 结果:
$                                #      * 之前 已暂存 的 README --> 已修改
$                                #      * HEAD~ 的 README 和 暂存区中的 README 相同
$                                #
$                                # git reset -- README  和 git reset HEAD README 等价
$
$ git checkout    -- README             # 使用暂存区域内的 README 替换当前目录的 README
$ git checkout HEAD~ README             # 使用 HEAD~ 的 README 替换当前目录 和 暂存区域 中的 README
$ git checkout test-branch              # 切换分支
$ git checkout -b test-branch           # 新建并切换分支
$ git checkout --orphan test-branch     # 新建并切换到独立分支
$ git checkout --track origin/serverfix # 新建并关联到远程分支
$ git checkout serverfix                # 本地分支不存在, 且 远程分支存在, 新建并关联到远程分支
$
$ git restore                     README # 使用 暂存区 的 README 覆盖 当前目录 中 的 README
$                                        # 和 git checkout -- README 意思相同
$ git restore --staged            README # 使用 HEAD   的 README 覆盖 暂存区 的 README
$                                        # 和 git reset -- README 意思相同
$ git restore --staged --worktree README # 使用 HEAD   的 README 覆盖 暂存区 和 当前目录 中的 README
$                                        # 和 git checkout HEAD README 意思相同
$ git restore --staged --worktree --source HEAD~2 README
$                                        # 使用 HEAD~2 的 README 覆盖 暂存区 和 当前目录 中的 README
$                                        # 如果 指定提交 或 暂存区域不含 README, 则删除对应的 README
$                                        # 和 git checkout HEAD~2 README 意思相同
$
$ git rm          README # 从 暂存区域 和 本地目录 中移除文件
$ git rm  -f      README # 强行删除
$ git rm --cached README # 从 暂存区域 中移除文件, 本地目录保留
$
$ git mv file_from file_to # 移动文件或目录
$
$ git commit --amend # 修改最后一次的提交信息，或增加提交的文件
$
$ git status         # 列出文件状态
$ git status  -s     # 显示简短信息
$ git status --short # 显示简短信息
$
$ git diff             # 暂存区域 和 已修改   的差异
$ git diff --staged    # 暂存区域 和 Git 仓库 的差异
$ git diff --cached    # 暂存区域 和 Git 仓库 的差异
$ git diff --submodule # 获取子模块的修改
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
$ git log -L :main:main.cpp            # 查询某一函数的变更记录
$ git log -L :10:main.cpp              # 查询某一行的变更记录
$ git log -L 8,10:main.cpp             # 查询某几行的变更记录
$ git log -S doRzrqPtywHqzqdmxx        # 搜索字符串的增加 删除
$
$ git branch                # 列出所有的本地分支
$ git branch -v             # 列出所有的本地分支, 以及最后一次提交
$ git branch --merged       # 列出已合并到本分支的本地分支
$ git branch --no-merged    # 列出未合并到本分支的本地分支
$ git branch test-branch    # 新建分支
$ git branch -d test-branch # 删除分支
$ git branch -D test-branch # 强制删除分支
$ git branch -r             # 查看远程分支
$ git branch --set-upstream-to=orgin/develop # 本地分支和远程分支关联
$ git branch -u orgin/develop                # 本地分支和远程分支关联
$
$ git ls-remote (remote)    # 查看远程分支
$
$ git merge test-branch # 将 test-branch 合并到 当前分支
$
$ git rebase master server-branch # 将 server-branch 分支变基到 master
$
$ git remote -v                       # 查看远程仓库
$ git remote add <shortname> <url>    # 添加远程仓库
$ git remote rm     origin            # 删除远程仓库
$ git remote remove origin            # 删除远程仓库
$ git remote rename origin new-origin # 重命名远程仓库
$ git remote show   origin            # 查看远程仓库的详细信息
$
$ git fetch [remote-name]                         # 从远程仓库获取数据
$
$ git pull                                        # 从远程仓库获取数据, 然后合并
$
$ git push origin master                          # 推送提交到远程仓库
$ git push origin --delete serverfix              # 删除远程分支
$ git push origin --set-upstream-to=orgin/develop # 本地分支和远程分支关联
$ git push origin -u orgin/develop                # 本地分支和远程分支关联
$ git push origin v1.0                            # 将指定 标签 推送到远程
$ git push origin --tags                          # 将所有 标签 推送到远程
$ git push origin --delete v1.0                   # 删除远程 标签
$
$ git revert -m 1 HEAD # 撤销提交
$
$ git tag                       # 列出 标签
$ git tag -l "v*"               # 列出 标签
$ git tag v1.0                  # 创建 标签
$ git tag -d v1.0               # 删除本地 标签
$ git tag --contains 提交号     # 查看某个提交号在哪些 tag 中出现
$
$ git submodule add https://github.com...      # 添加子模块
$ git submodule init                           # 初始化本地子模块的配置
$ git submodule update                         # 获取子模块远程数据, 相对于当前仓库中子模块的提交号
$ git submodule update --init                  # 等价于前两个命令
$ git submodule update --init --recursive      # 递归获取子模块的远程数据
$ git submodule update --remote DbConnector    # 在主目录更新子模块, 远程子模块仓库的最新数据
$ git submodule update --remote --merge        # 合并远程修改到本地
$ git submodule update --remote --rebase       # 变基远程修改到本地
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

