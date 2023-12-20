
## 说明
```
tcpdump 可选项 协议 源 类型 值
* 协议: tcp udp icmp ip arp
* 源:   src dst
* 类型: host(IP) net(网络) port(端口号) portrange(一系列端口号)

* [S]: SYN(发起连接), [P]: push(发送), [F]:fin(结束), [R]: RST(重置), [.](确认或其他)
* ack 表示下一个要接收的 seq 号
* length 有效数据的长度
* win 接收窗口的大小
* 为避免shell干扰, 可将内容用引号包含
* and  or 可以组合多个条件

tcpdump -D                      # 列出可以 tcpdump 的网络接口
tcpdump -i eth0                 # 捕捉某一网络接口
tcpdump -i any                  # 捕捉所有网络接口
tcpdump -i any -c 20            # 捕捉所有网络接口, 限制包的数量
tcpdump -i any -n               # 捕捉所有网络接口, 使用IP和端口号, 而不是域名和服务名称
tcpdump -i any -w ...           # 捕捉所有网络接口, 将数据保存在文件中
tcpdump -i any -r ...           # 捕捉所有网络接口, 从文件中读取数据
tcpdump -i any -A               # 捕捉所有网络接口, 打印报文 ASCII
tcpdump -i any -x               # 捕捉所有网络接口, 打印包的头部, -xx -X -XX 类似
tcpdump -i any -e               # 捕捉所有网络接口, 输出包含数据链路层信息
tcpdump -i any -l               # 捕捉所有网络接口, 使用行缓存, 可用于管道
tcpdump -i any -N               # 捕捉所有网络接口, 不打印域名
tcpdump -i any -Q in            # 捕捉所有网络接口, 指定数据包的方向 in, out, inout
tcpdump -i any -q               # 捕捉所有网络接口, 简洁输出
tcpdump -i any -s ...           # 捕捉所有网络接口, 设置读取的报文长度,0 无限制
tcpdump -i any -S ...           # 捕捉所有网络接口, 使用绝对 seq
tcpdump -i any -v               # 捕捉所有网络接口, 显示详细信息, -vv -vvv 更详细
tcpdump -i any -t               # 捕捉所有网络接口, 不打印时间
tcpdump -i any -tt              # 捕捉所有网络接口, 发送(绝对时间), 确认(绝对时间)(时间戳)
tcpdump -i any -ttt             # 捕捉所有网络接口, 发送(相对时间), 确认(相对间隔)(时分秒 毫秒)
tcpdump -i any -tttt            # 捕捉所有网络接口, 发送(绝对时间), 确认(绝对时间)(年月日-时分秒)
tcpdump -i any -ttttt           # 捕捉所有网络接口, 发送(相对时间), 确认(相对时间)(时分秒 毫秒)
tcpdump -l                      # 使用行缓存, 可用于管道
tcpdump src  host 192.168.1.100 # 指定源地址 可以使用 /8 表明网络
tcpdump dst  host 192.168.1.100 # 指定目的地址
tcpdump      host 192.168.1.100 # 指定主机地址
tcpdump       net 192.168.1     # 指定网络地址, 也可以使用 /8 表示
tcpdump src  port 22            # 指定源端口号
tcpdump dst  port 22            # 指定目的端口号
tcpdump      port 22            # 指定端口号, 可使用服务名称
tcpdump not  port 22            # 排除端口号
tcpdump tcp                     # 指定协议
tcpdump "tcp[tcpflags] == tcp-syn" # 基于tcp的flag过滤
tcpdump less 32                 # 基于包大小过滤
tcpdump greater 64              # 基于包大小过滤
tcpdump ether   host  ...       # 基于 MAC 过滤
tcpdump gateway host ...        # 基于网关过滤
tcpdump ether broadcast         # 基于广播过滤
tcpdump ether multicast         # 基于多播过滤
tcpdump ip broadcast            # 基于广播过滤
tcpdump ip multicast            # 基于多播过滤
```

