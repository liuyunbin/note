
# 计算机网络
## 基础知识
```
硬盘: 1T = 1000G = 1000 * 1000 * 1000 * 1000B = ... / 1024 / 1024 /1024 GB = 931GB
网卡: 1000M = 1000Mbps = 125MB (网速也一样)

  带宽: 网速, 上限由网卡控制
吞吐量: 有效数据的速度, 速度小于带宽
  延时: 客户端发送数据到收到数据的时差

kmg(1000), KMG(1024), B(字节), b(位)
```

## 网络接口层(帧)(以太网)
* MTU 最大传输单元 (链路层)
* 通过MAC可以区分是单播还是(组播或广播)
* 以太网
* WiFi

* 集线器: 无脑转发数据到所有出口(不知道 MAC 和 IP) -- 很少使用了
* 交换机: 将指定数据直接发送到目标机器(知道 MAC) ---- 机器数量过大时, 会很难处理

## 网络层(数据包)
* IPv4
* IPv6

* 路由器: 连接不同的网络(知道 MAC 和 IP)

## 传输层(段)
* TCP: 面向连接的可靠的字节流协议
* UDP: 无连接, 固定长度的不可靠的数据报协议

## 应用层(消息)
* DHCP(广播, UDP)
    1. 新机器(IP: 0.0.0.0)发送信息给当前网络(IP: 255.255.255.255)的所有机器(不会跨网关)
    2. 包含 DHCP 服务器的机器发送新的 IP 给新机器(IP: 255.255.255.255)
    3. 新机器(IP: 新IP)发送确认信息给 DHCP 服务器
* http
* DNS
    * A ------------------ 域名 => IPv4
    * AAAA --------------- 域名 => IPv6
    * CNAME -------------- 域名 => 另一域名
    * /etc/resolv.conf --- DNS 服务器的地址
    * /etc/hosts --------- 域名 和 IP 的对应关系
* ICMP(传输控制协议 不使用端口号) -- ping 实现


## 为什么不能去掉IP(32位)
* 为了划分子网, 方便路由, 传送数据到子网

## 为什么不能去掉MAC(48位, 一般无法改变)
1. 网络协议分层, 不同层实现不同的功能, 交换机会使用其传递数据
2. 直接使用 IP 其实也可以, 这个就是历史原因了

## 端口号
```
* [0, 1024)      # 公认端口号, 需要 root 启动, 比如 80
* [1024, 32768)  # 注册端口, 可以自己注册一些常用服务
* [32768, 60990) # 动态端口, 进程未指定端口号时, 将从这个范围内获取一个端口号
                 # 可通过文件 /proc/sys/net/ipv4/ip_local_port_range 获取
* [60990, 65535)
```

## 单播(一般的网络服务都是单播)
1. 源 IP 和目标 IP 属于同一个子网时, 利用 arp 获取目标的 MAC, 然后利用交换机发送数据到指定机器
2. 否则, 利用路由表获取下一跳的 IP 地址
3. 利用 arp 获取下一跳的 MAC, 然后利用交换机发送数据到下一跳的机器
4. 默认网关会修改源 MAC, 然后再查找下一跳或指定机器
5. 数据传输过程中, 源 IP 和目标 IP 一般不变, 除了 NAT 等

## 组播(IGMP 直播 电视)(TCP 不支持)
1. 组播源注册: 服务器(组播源IP)向中介机构(RP)注册组播IP(2.2.2.2)
2. 客户端向中介机构(RP)申请加入组播IP: 生成基于中介机构(RP)的树(RPT), 同时获取组播源IP
3. 客户端向服务器(组播源IP)申请加入组播IP: 生成基于源的树(SPT), 废弃掉 RPT(SPT路径更优)
4. 服务器通过SPT, 向所有的注册组播IP的用户发送数据
    * 源IP和MAC填自己的数据
    * 目的IP为组播地址
    * 目的MAC为: 01:00:5e + 组播IP 地址低 23 bit(区分单播 组播 广播)
    * 由于目的IP为组播IP, 无法获取确切的MAC, 指定某一机器, 所以只能采用广播向所有机器发送数据
5. 客户端或者路由器通过接收到的数据的组播地址来确定是不是自己所需要的数据

## 广播(ARP, 使用DHCP申请IP地址时)(TCP 不支持)
* 发送所有数据到当前网络的所有机器
* 一般不能跨网络

## 任播(TCP 不支持)
* 最近或最合适的客户

#### 查看 Linux 临时端口号的范围
```
cat /proc/sys/net/ipv4/ip_local_port_range
32768   60999
``

* [0, 1024) 公认端口号, 需要 root 启动, 比如 80
* [1024, 32768) 注册端口, 可以自己注册一些常用服务
* [32768, 60990) 动态端口, 进程未指定端口号时, 将从这个范围内获取一个端口号
* [60990, 65535)

# 查询 域名 对应 的 IP
* nslookup baidu.com

