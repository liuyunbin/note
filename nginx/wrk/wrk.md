
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
```
-c .......... 总共的连接数
-d .......... 持续时间
-t .......... 线程数
-s .......... 使用 lua 脚本
-H .......... 添加请求头部
-L .......... 输出每次的数据的统计
-R .......... 限制发送速率
--latency ... 打印延迟统计数据
--timeout ... 设置超时时间
```

## 原理
1. 启动 n 个线程
2. 每个线程使用类似 epoll 的方法, 发起 m 个连接
3. 每个连接响应回来了, 才会发送新的请求

## lua 相关说明
```
wrk = {
    scheme  = "http",
    host    = "localhost",
    port    = nil,
    method  = "GET",
    path    = "/",
    headers = {},
    body    = nil,
    thread  = <userdata>
}

wrk.format --------- 构造并覆盖 wrk
wrk.lookup --------- 查看服务器所有的地址信息
wrk.connect -------- 测试服务器是否能正常连接

setup() ------------ 线程初始化的时候执行
init() ------------- 线程启动  的时候执行
delay() ------------ 相邻请求的间隔
request() ---------- 发送请求前执行
response() --------- 收到响应后执行
done() ------------- 所有任务完成后执行
```

