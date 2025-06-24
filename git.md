
## 代理
```
# 1. hhtp 协议
git config --global http.proxy socks5h://127.0.0.1:7890
git clone https://github.com/liuyunbin/note
git config --global --unset http.proxy

# 2. ssh 协议 --- 在 ~/.ssh/config 内添加
Host github.com
ProxyCommand nc      --proxy-type socks5 --proxy 127.0.0.1:7890 %h %p # centos
ProxyCommand nc                -X 5           -x 127.0.0.1:7890 %h %p # ubuntu
ProxyCommand connect                          -S 127.0.0.1:7890 %h %p # windows
```


git clone --recurse-submodules https://github.com... # 克隆包含子模块的项目

git diff             # 暂存区域 和 已修改   的差异
git diff --staged    # 暂存区域 和 Git 仓库 的差异
git diff --cached    # 暂存区域 和 Git 仓库 的差异
git diff --submodule # 获取子模块的修改

git rm --cached README # 从 暂存区域 中移除文件, 本地目录保留

git log -L :main:main.cpp            # 查询某一函数的变更记录
git log -L :10:main.cpp              # 查询某一行的变更记录
git log -L 8,10:main.cpp             # 查询某几行的变更记录
git log -S doRzrqPtywHqzqdmxx        # 搜索字符串的增加 删除

git revert -m 1 HEAD # 撤销合并提交, -m 后要保留的父提交的索引

git reset HEAD~ --soft         # 只修改仓库
git reset HEAD~                # 修改仓库和暂存区
git reset HEAD~ --hard         # 修改仓库, 暂存区和工作目录
git reset HEAD~ README         # 替换暂存区域中的 README
                               # 有取消暂存区中文件修改的作用

git checkout    -- README             # 使用暂存区域内的 README 替换当前目录的 README
                                      # 有取消工作目录中文件修改的作用
git checkout HEAD~ README             # 使用 HEAD~ 的 README 替换当前目录 和 暂存区域 中的 README
                                      # 可以用于拉取, 某一提交的一个文件
git checkout --orphan test-branch     # 新建并切换到独立分支

git restore                     README # 使用 暂存区 的 README 覆盖 当前目录 中 的 README
                                       # 有取消工作目录中文件修改的作用
git restore --staged            README # 使用 HEAD   的 README 覆盖 暂存区 的 README
                                       # 和 git reset -- README 意思相同
git restore --staged --worktree README # 使用 HEAD   的 README 覆盖 暂存区 和 当前目录 中的 README
                                       # 和 git checkout HEAD README 意思相同
git restore --staged --worktree --source HEAD~2 README
                                       # 使用 HEAD~2 的 README 覆盖 暂存区 和 当前目录 中的 README
                                       # 如果 指定提交 或 暂存区域不含 README, 则删除对应的 README
                                       # 和 git checkout HEAD~2 README 意思相同

git submodule add https://github.com...      # 添加子模块
git submodule init                           # 初始化本地子模块的配置
git submodule update                         # 获取子模块远程数据, 相对于当前仓库中子模块的提交号
git submodule update --init                  # 等价于前两个命令
git submodule update --init --recursive      # 递归获取子模块的远程数据
git submodule update --remote DbConnector    # 在主目录更新子模块, 远程子模块仓库的最新数据
git submodule update --remote --merge        # 合并远程修改到本地
git submodule update --remote --rebase       # 变基远程修改到本地

git reflog show --date=iso                   # 记录每一次提交, 用于找回删除的提交

git apply --check ...                        # 检查补丁是否能成功应用
git apply         ...                        # 应用补丁

#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

git config --global user.name "Yunbin Liu"            # 1. 配置用户名
git config --global user.email yunbinliu@outlook.com  # 2. 配置邮箱
git config --global core.editor vim                   # 3. 配置编辑器
git config --global log.date iso                      # 4. 配置日期格式
git config --global alias.co checkout                 # 5. 配置简要命令
git config --global alias.br branch                   #
git config --global alias.ci commit                   #
git config --global alias.st status                   #
git config --global alias.lg "log --pretty=format:'%ad %h %s %d %C(bold)%an%Creset' --graph"
                                                      # 6. 配置日志显示格式
git config --global core.quotepath false              # 7. 中文显示不乱码
git config --global --list                            # 8. 查看配置
#ssh-keygen -t ed25519                                # 9. 生成秘钥
                                                      # 10. 复制公钥到 GitHub
#ssh -T git@github.com                                # 11. 测试连接

