
## 简介
* Git 是一个分布式版本管理的工具
* 本文只列举 Git 最常用的功能
* Git 只是版本管理的工具, 未必需要做到, 知其然并知其所以然, 够用就好

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

## 本地配置基础环境连接 GitHub
```
$ sudo apt install git                                 # 安装 Git
$                                                      #
$ git config --global user.name  liuyunbin             # 配置用户名
$ git config --global user.email yunbinliu@outlook.com # 配置邮箱
$ git config --global core.editor vim                  # 配置默认编辑器
$ git config --global log.date iso                     # 配置日志使用 年月日 时分秒 时区 的格式
$
$ git config --global alias.lg "log --pretty=format:'%Cgreen%ad%Creset %h %s %C(yellow)%d%Creset %Cblue%an%Creset'"                                                 # 添加别名
$                                                      #
$ git config --list --global                           # 查看当前用户的配置信息
$                                                      #
$ ssh-keygen -t rsa                                    # 生成密钥
$                                                      # 复制公钥到 GitHub
$                                                      #     将文件 `~/.ssh/id_rsa.pub` 里的公钥添加到
$                                                      #     https://github.com/settings/keys
$                                                      # 到此可以免密码使用 GitHub
$ ssh -T git@github.com                                # 测试是否成功
```

## 常用命令
```
git add README # 未跟踪 --> 已暂存
git add README # 已修改 --> 已暂存
git add README # 合并时把有冲突的文件标记为已解决状态
git add -u     # 添加所有已修改的文件

git blame  main.cc        # 查看文件每行的最后变更

git branch                                 # 列出所有的本地分支
git branch -v                              # 列出所有的本地分支, 以及最后一次提交
git branch -vv                             # 列出所有的本地分支, 以及最后一次提交, 跟踪的远程分支
git branch --merged                        # 列出已合并到 本分支  的本地分支
git branch --merged     develop            # 列出已合并到 develop 的本地分支
git branch --no-merged                     # 列出未合并到 本分支  的本地分支
git branch --no-merged  develop            # 列出未合并到 develop 的本地分支
git branch              test-branch        # 新建分支, 并不会切换分支
git branch -d           test-branch        #       删除分支, 如果该分支还未合并到当前分支,   会报错
git branch -D           test-branch        #   强制删除分支, 如果该分支还未合并到当前分支, 不会报错
git branch -m            new-branch        # 重命名当前分支, 如果新分支名已存在,   会报错
git branch -M            new-branch        # 重命名当前分支, 如果新分支名已存在, 不会报错
git branch -m old-branch new-branch        # 重命名指定分支, 如果新分支名已存在,   会报错
git branch -M old-branch new-branch        # 重命名指定分支, 如果新分支名已存在, 不会报错
git branch -r                              # 查看远程分支
git branch --set-upstream-to=orgin/develop # 本地分支和远程分支关联
git branch -u orgin/develop                # 本地分支和远程分支关联

git checkout    -- README                       # 使用暂存区的 README 替换当前目录的 README
git checkout HEAD~ README                       # 使用 HEAD~ 的 README 替换当前目录和暂存区域 的 README
git checkout    test-branch                     #       切换分支
git checkout -b test-branch                     # 新建并切换分支
git checkout --orphan test-branch               # 新建并切换到独立分支
git checkout -b      serverfix origin/serverfix # 新建并关联到远程分支
git checkout --track           origin/serverfix # 新建并关联到远程分支
git checkout         serverfix                  # 本地分支不存在, 且 远程分支存在, 新建并关联到远程分支

git clone                      https://github.com/liuyunbin/note # 克隆仓库
git clone --recurse-submodules https://github.com...             # 克隆包含子模块的项目
git clone git@github.com:liuyunbin/note     # ssh 协议
git clone git@github.com:liuyunbin/note.git # TODO: 和上一个有什么区别

git commit -a -m "message"   # 已修改 --> 已暂存 --> 已提交
git commit    -m "message"   #            已暂存 --> 已提交
git commit --amend           # 将要修改的内容合并到最后一次提交中, 并修改提交信息, 旧的提交将删除
git commit --amend -m ...    # 将要修改的内容合并到最后一次提交中, 并修改提交信息, 旧的提交将删除
git commit --amend --no-edit # 同上, 但不需要修改提交信息

                                                     # --system  为整个系统中的项目配置
                                                     # --global  为某个用户下的项目配置
                                                     # --local   为单独的某个项目配置 -- 这个是默认行为
git config --global user.name  liuyunbin             # 配置用户名
git config --global user.email yunbinliu@outlook.com # 配置邮箱
git config --global core.editor vim                  # 配置默认编辑器
git config --global log.date iso                     # 日志使用 年月日 时分秒 时区 的格式
git config --global color.status      auto
git config --global color.diff        auto
git config --global color.branch      auto
git config --global color.interactive auto
git config --global --list                           # 检查配置信息
git config --global --list --show-origin             # 检查配置信息 以及 所属文件
git config --global               user.name          # 检查某一项配置
git config --global --show-origin user.name          # 检查某一项配置 及其 所属文件

git config --global core.eol     lf # 设置工作目录的换行符为   \n
git config --global core.eol   crlf # 设置工作目录的换行符为 \r\n
git config --global core.eol native # 设置工作目录的换行符为 native, 使用平台默认的换行符 == 默认值

git config --global core.autocrlf true  # 提交时: CRLF --> LF, 检出时: LF --> CRLF
git config --global core.autocrlf input # 提交时: CRLF --> LF, 检出时: 不转换
git config --global core.autocrlf false # 提交时: 不转换,      检出时: 不转换 == Linux 下的默认值

git config --global core.safecrlf true  # 拒绝提交包含混合换行符的文件
git config --global core.safecrlf false # 允许提交包含混合换行符的文件  == Linux 下的默认值
git config --global core.safecrlf warn  # 提交包含混合换行符的文件时给出警告

git config --global core.quotepath false # 引用路径不使用八进制, 中文名不再乱码

                     # 有参数比较 已修改 与 Git 仓库的区别吗? TODO
git diff             # 暂存区域 和 已修改   的差异
git diff --staged    # 暂存区域 和 Git 仓库 的差异
git diff --cached    # 暂存区域 和 Git 仓库 的差异
git diff --submodule # 获取子模块的修改

git fetch [remote-name] # 从远程仓库获取数据
git fetch -a            # 从所有远程仓库获取数据

git for-each-ref --format='%(committerdate:iso) %(refname) %(authorname)'
                        # 查看所有远程分支最后一次的提交
git init                    # 初始化仓库

git log
git log --stat              # 显示简略统计信息
git log --shortstat         # 只显示添加移除信息
git log  -p                 # 显示修改的内容
git log --patch
git log  -2                 # 显示近两次的提交
git log --oneline           # 每个提交一行, 相当于 --pretty=oneline --abbrev-commit
git log --pretty=oneline    # 每个提交一行
git log --pretty=short      # 只有作者, 没有日期
git log --pretty=full       # 显示作者和提交者
git log --pretty=fuller     # 显示作者 作者提交的日期和提交者 提交者提交的日期
git log --pretty=format:"." # 指定显示格式
git log --pretty=format:'%Cgreen%ad%Creset %h %s %C(yellow)%d%Creset %Cblue%an%Creset'
                            # %h 提交的简写哈希值
                            # %t 树的简写哈希值
                            # %p 父提交的简写哈希值
                            # %an 作者名字
                            # %ae 作者的邮箱
                            # %ad 作者修订日期
                            # %cn 提交者的名字
                            # %ce 提交者的邮箱
                            # %cd 提交日期
                            # %d  ref名称 -- 包括tag等
                            # %s 提交说明
                            # %Cred	切换到红色
                            # %Cgreen 切换到绿色
                            # %Cblue  切换到蓝色
                            # %Creset 重设颜色
git log --graph             # 显示分支的合并
git log --name-only         # 显示修改的文件清单
git log --name-status       # 显示修改的文件信息, 增删改
git log --abbrev-commit     # 只显示提交hash的前几个字符
git log --after=2021-07-16
git log --since=2021-07-16
git log --before=2021-07-16
git log --until=2021-07-16
git log --author=liuyunbin            # 指定作者
git log --committer=54c7cd09          # 指定提交者
git log --grep=liuyunbin              # 搜索提交说明中包含该关键字的提交
git log --grep=A --grep=B             # 搜索提交说明中包含 A 或 B 的提交
git log --grep=A --grep=B --all-match # 搜索提交说明中包含 A 且 B 的提交
git log --no-merges                  # 不显示提交合并
git log a..b                         # 不在 a 中, 在 b 中的提交
git log ^a b                         # 不在 a 中, 在 b 中的提交
git log --not a b                    # 不在 a 中, 在 b 中的提交
git log a...b                        # 在 a 或 b 中, 但不同时在 a 且 b 中的提交
git log -L :main:main.cpp            # 查询某一函数的变更记录
git log -L :10:main.cpp              # 查询某一行的变更记录
git log -L 8,10:main.cpp             # 查询某几行的变更记录
git log -S main                      # 搜索字符串的增加 删除
git log -- ...                       # 指定路径
git log --decorate                   # 查看 HEAD 分支 tag 所属的提交

git ls-remote (remote)    # 查看远程分支

git merge test-branch # 将 test-branch 合并到 当前分支

git mv file_from file_to # 移动文件或目录

git pull            # 从远程仓库获取数据, 然后合并
git pull --rebase   # 从远程仓库获取数据, 然后合并, 自动 rebase

git push origin master                          # 推送提交到远程仓库
git push origin A:B                             # 推送本地分支A到远程分支B
git push origin --delete serverfix              # 删除远程分支
git push origin --set-upstream-to=orgin/develop # 本地分支和远程分支关联
git push origin -u orgin/develop                # 本地分支和远程分支关联
git push origin v1.0                            # 将指定 标签 推送到远程
git push origin --tags                          # 将所有 标签 推送到远程
git push origin --delete v1.0                   # 删除远程 标签
git push orign feature/test -f                  # 强推本地分支
git push origin --delete feature/test           # 删除远程分支

git rebase master server-branch        # 将 server-branch 分支变基到 master
git rebase -i HEAD~6                   # 之后，使用 f 取消掉不需要的内容，合并提交
git rebase orign/develop               # 将 orign/develop 上的内容，变基到 当前分支
git rebase --onto master server client # 将在 server 上存在, 不在 client 上的内容变基到 master

git remote                          # 查看远程仓库
git remote -v                       # 查看远程仓库
git remote add <shortname> <url>    # 添加远程仓库
git remote rm     origin            # 删除远程仓库
git remote remove origin            # 删除远程仓库
git remote rename origin new-origin # 重命名远程仓库
git remote show   origin            # 查看远程仓库的详细信息
git remote prune  origin            # 删除本地仓库中的远程分支(远程仓库里已删除)

git reset --soft  HEAD~           # 将 HEAD 指到 HEAD~, 暂存区和工作目录不变
                                  # 有可能会丢失 HEAD~ 之后的数据
                                  # 已提交 => 已暂存
git reset         HEAD~           #
git reset --mixed HEAD~           # 将 HEAD 指到 HEAD~, 使用 HEAD 指向的数据重置暂存区, 工作目录保持不变
                                  # 有可能会丢失 HEAD~ 之后的数据, 以及已暂存的数据
                                  # 已提交 => 已修改
git reset --hard  HEAD~           # 将 HEAD 指到 HEAD~, 使用 HEAD 指向的数据重置暂存区和工作目录
                                  # 会丢失 HEAD~ 之后的数据, 以及已暂存, 已修改的数据
                                  # 已提交 => 已删除
git reset --soft  HEAD~ -- README # 非法
git reset         HEAD~ -- README # 使用 HEAD~ 的 README 替换 暂存区 的 README, Git 仓库 和 工作目录保持不变
                                  # 有可能会丢失已暂存的数据, 有取消暂存的效果
git reset               -- README # 和 git reset HEAD~ -- README 等价
git reset --mixed HEAD~ -- README # 同上一个, 但已过时
git reset --hard  HEAD~ -- README # 非法

git restore                     README # 使用 暂存区 的 README 覆盖 当前目录 中 的 README
                                       # 和 git checkout -- README 意思相同
git restore --staged            README # 使用 HEAD   的 README 覆盖 暂存区 的 README
                                       # 和 git reset -- README 意思相同
git restore --staged --worktree README # 使用 HEAD   的 README 覆盖 暂存区 和 当前目录 中的 README
                                       # 和 git checkout HEAD README 意思相同
git restore --staged --worktree --source HEAD~2 README
                                       # 使用 HEAD~2 的 README 覆盖 暂存区 和 当前目录 中的 README
                                       # 如果 指定提交 或 暂存区域不含 README, 则删除对应的 README
                                       # 和 git checkout HEAD~2 README 意思相同
git restore --source HEAD~2 README     # 使用 HEAD~2 的 README 覆盖当前目录 中的 README, 暂存区的内容保持不变

git revert -m 1 HEAD # 撤销提交

git rm          README # 从 暂存区域 和 本地目录 中移除文件, 如果该文件已修改 或 已暂存,   会失败
git rm  -f      README # 从 暂存区域 和 本地目录 中移除文件, 如果该文件已修改 或 已暂存, 也会成功
git rm --cached README # 从 暂存区域 中移除文件, 本地目录保留

git show HEAD   # 展示指定提交
git show HEAD^  # 展示指定提交的第一父提交
git show HEAD^^ # 展示指定提交的第一父提交的第一父提交
git show HEAD^2 # 展示指定提交的第二父提交, 用于 merge
git show HEAD~  # 展示指定提交的第一父提交
git show HEAD~~ # 展示指定提交的第一父提交的第一父提交
git show HEAD~2 # 展示指定提交的第一父提交的第一父提交

git stash                     # 贮藏工作
git stash --keep-index        # 贮藏工作, 同时将暂存的内容存在索引内
git stash --include-untracked # 贮藏工作, 同时贮藏未跟踪的文件, 不包括忽略的文件
git stash  -u                 # 贮藏工作, 同时贮藏未跟踪的文件, 不包括忽略的文件
git stash --all               # 贮藏工作, 同时贮藏未跟踪的文件,   包括忽略的文件
git stash  -a                 # 贮藏工作, 同时贮藏未跟踪的文件,   包括忽略的文件
git stash list                # 列出已贮藏的工作
git stash apply               # 恢复已贮藏的工作
git stash apply --index       # 恢复已贮藏的工作, 同时恢复暂存区
git stash drop                # 丢弃贮藏区的工作
git stash pop                 # 恢复已贮藏的工作, 并丢弃贮藏区的工作

git status         # 列出文件状态
git status  -s     # 显示简短信息
git status --short # 显示简短信息

git submodule add https://github.com...      # 添加子模块
git submodule init                           # 初始化本地子模块的配置
git submodule update                         # 获取子模块远程数据, 相对于当前仓库中子模块的提交号
git submodule update --init                  # 等价于前两个命令
git submodule update --init --recursive      # 递归获取子模块的远程数据
git submodule update --remote DbConnector    # 在主目录更新子模块, 远程子模块仓库的最新数据
git submodule update --remote --merge        # 合并远程修改到本地
git submodule update --remote --rebase       # 变基远程修改到本地

git switch    test-branch #       切换到 test-branch
git switch -c test-branch # 创建并切换到 test-branch

git tag                       # 列出 标签
git tag -l "v*"               # 列出 标签
git tag v1.0                  # 创建 标签
git tag v1.0  提交号          # 在某次提交上, 创建 标签
git tag -d v1.0               # 删除本地 标签
git tag --contains 提交号     # 查看某个提交号在哪些 tag 中出现
```

## 参考资源
1. https://help.github.com/en/articles/set-up-git
2. https://git-scm.com/book/zh/v2

