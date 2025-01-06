
## 初始化
```
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
ssh-keygen -t ed25519                                 # 9. 生成秘钥
                                                      # 10. 复制公钥到 GitHub
ssh -T git@github.com                                 # 11. 测试连接
```

