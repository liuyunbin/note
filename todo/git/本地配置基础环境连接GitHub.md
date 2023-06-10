
# 本地配置基础环境连接 GitHub
## 第一步: 安装 Git
```
$ sudo apt install git
```

## 第二步: 为当前用户配置用户名 邮箱
```
$ git config --global user.name  liuyunbin             # 用户名
$ git config --global user.email yunbinliu@outlook.com # 邮箱
```

## 第三步: 查看当前用户的配置信息
```
$ git config --list --global
```

## 第四步: 生成密钥
```
$ ssh-keygen -t rsa
```

## 第五步: 复制公钥到 GitHub, 到此可以免密码使用 GitHub
将文件 `~/.ssh/id_rsa.pub` 里的公钥添加到：https://github.com/settings/keys

