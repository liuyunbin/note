
## 说明
wrk 和 wrk2 是一个轻量级的压测 http 服务器的工具

## 安装 wrk
apt install -y wrk

## 安装 wrk2
```
$ sudo apt update                                    # 更新软件源
$ sudo apt install -y make gcc libssl-dev zlib1g-dev # 安装依赖库
$ cd ~/github                                        #
$ git clone git@github.com:giltene/wrk2              # 克隆及编译 wrk2
$ cd wrk2 && make                                    #
$ sudo ln -s ~/github/wrk2/wrk /usr/bin/wrk2         # 将 wrk2 链接到系统的 bin 目录下
```

## 使用


