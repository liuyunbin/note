
docker run ubuntu:15.10 -d --name "lyb"           # 启动 docker, 给起一个名字
docker run ubuntu:15.10 -d --net=host             # 主机和 docker 共享 IP 和 端口号
docker run ubuntu:15.10 -d -P                     # docke 内使用随机端口映射主机端口
docker run ubuntu:15.10 -d -p 2000:3000           # 本机:2000 绑定 docker:3000
docker run ubuntu:15.10 -d -v /home/123:/home/456 # 本机:/home/123 绑定 docker:/home/456

docker port     容器ID     # 查看端口号映射
docker ps                  # 列出当前运行的容器
docker ps -a               # 列出所有容器
docker start    容器ID     # 启动容器
docker stop     容器ID     # 停止容器
docker restart  容器ID     # 重新启动容器
docker rm -f    容器ID     # 删除容器
docker exec     容器ID ls  # 对于在后台运行的容器, 执行命令

redis flushdb # 清空数据
redis -c ...  # 集群时需要使用 -c 启动, 否则查不到数据

route    -- 已过时, 被 ip route 替代

sleep 30   # 前台运行
sleep 30 & # 后台运行

systemctl start      nginx   # 启动 nginx
systemctl stop       nginx   # 停止 nginx
systemctl restart    nginx   # 重启 nginx
systemctl status     nginx   # 查看 nginx 状态
systemctl enable     nginx   # 开机自动启动 nginx
systemctl disable    nginx   # 开机禁止启动 nginx
systemctl is-active  nginx   # 查看 nginx 是否启动成功
systemctl is-failed  nginx   # 查看 nginx 是否启动失败
systemctl is-enabled nginx   # 查看 nginx 是否开机启动

traceroute: 查看数据包经过的路径

ss       # 显示已连接的 UDP, TCP, unix domain sockets
ss -x    # unix domain sockets
ss -u    #          UDP
ss -t    # 已连接的 TCP
ss -tl   #   监听的 TCP
ss -ta   # 已连接和监听的 TCP
ss -tln  # 服务使用数字而不是名称
ss -tlnp # 列出监听的进程号, 需要root 权限
ss -s    # 显示统计
ss src   192.168.198.128:22  # 通过源  IP和端口号筛选信息
ss dst   192.168.198.1:51932 # 通过目的IP和端口号筛选信息
ss sport OP 22               # 通过源  端口号过滤数据
ss dport OP 22               # 通过目的端口号过滤数据
                             # OP 可以是空, >(gt) >=(ge) <(lt) <=(le) ==(eq) !=(ne), 注意转义

host     ...       #
nslookup baidu.com # 查询 域名 对应 的 IP

tcpdump 可选项 协议(tcp udp icmp ip arp) 源(src dst) 类型(host net port portrange) 值
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
tcpdump ether   host  ...          # 基于 MAC 过滤
tcpdump gateway host ...          # 基于网关过滤
tcpdump ether broadcast      # 基于广播过滤
tcpdump ether multicast      # 基于多播过滤
tcpdump ip broadcast         # 基于广播过滤
tcpdump ip multicast         # 基于多播过滤

ping      www.bing.com # 使用 ICMP ping 主机
ping -c 3 www.bing.com # 使用 ICMP ping 主机, 设置测试的次数
ping -i 3 www.bing.com # 使用 ICMP ping 主机, 设置间隔的秒数
ping -w 3 www.bing.com # 使用 ICMP ping 主机, 设置耗时的上限
ping -f   www.bing.com # 使用 ICMP ping 主机, 高速率极限测试, 需要 root 权限

ntpdate -s time-b.nist.gov          # 使用时间服务器更新时间

                                        # 注意, 有不同版本的 nc, 参数不一定相同
nc -l             8080                  # 服务端(tcp), 接收单个连接
nc -lk            8080                  # 服务端(tcp), 接收多个连接
nc -lv            8080                  # 服务端(tcp), 显示连接信息
nc -lu            8080                  # 服务端(udp)
nc      127.0.0.1 8080                  # 客户端(tcp)
nc -n   127.0.0.1 8080                  # 客户端(tcp), 不进行域名解析, 节省时间
nc -N   127.0.0.1 8080                  # 客户端(tcp), 收到 EOF 后, 退出(有的版本不需要此参数, 会自动退出)
nc -w 3 127.0.0.1 8080                  # 客户端(tcp), 设置超时时间
nc -vz  127.0.0.1 8080                  # 客户端(tcp), 不发送信息, 只显示连接信息(测试单个端口)
nc -vz  127.0.0.1 8080-8090             # 客户端(tcp), 不发送信息, 只显示连接信息(测试多个端口)
nc -u   127.0.0.1 8080                  # 客户端(udp)
nc -lk            8080 | pv > /dev/null # 测速-服务端, 注意重定向, 否则会受限于终端的写速率
nc      127.0.0.1 8080      < /dev/zero # 测试-客户端

netstat  -- 已过时, 被 ss       替代

nmap             127.0.0.1 # 主机发现 -> 端口扫描, 默认扫描 1000 个端口
nmap -p  80      127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -p  80-85   127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -p  80,8080 127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -Pn         127.0.0.1 # 跳过主机发现, 直接端口扫描
nmap -sn         127.0.0.1 # 主机发现

                   # lsof -- sudo yum install lsof
lsof -iTCP         # 查看 TCP 信息
lsof -i :22        # 查看指定 端口号 的信息
lsof -i@1.2.3.4:22 # 查看是否连接到指定 IP 和 端口号上
lsof -p 1234       # 指定 进程号
lsof -d 0,1,2,3    # 指定 文件描述符
lsof -t            # 仅获取进程ID

ip a                                 # 显示网卡信息
ip addr    show                      # 显示指定网卡信息
ip address show dev   lo             # 显示指定网卡信息
ip address add 192.268.1.10 dev eth0 # 添加 IP 地址
ip address del 192.268.1.10 dev eth0 # 删除 IP 地址

ifconfig    # 查看网卡信息
ifconfig ens33 192.168.1.1                       # 设置 IP
ifconfig ens33 192.168.1.1 netmask 255.255.252.0 # 设置 IP 和子网掩码
ifconfig ens33 hw ether ...                      # 设置硬件地址

ip link set dev eth0 multicast on  # 启用组播
ip link set dev eth0 multicast off # 禁用组播
ip link set dev eth0 up            # 启用网卡
ip link set dev eth0 down          # 禁用网卡
ip link set dev eth0 arp       on  # 启用 arp 解析
ip link set dev eth0 arp       off # 禁用 arp 解析
ip link set dev eth0 mtu      1500 # 设置最大传输单元
ip link set dev eth0 address  ...  # 设置 MAC 地址

ip route       # 路由信息
ip route show  # 路由信息
ip route get   # 查看指定 IP 的路由信息
ip route add   # 添加路由
ip route chage # 修改路由
ip route flush # 清空路由信息

ip neighbour  # 查看 arp 协议

ip -s link         # 查看统计信息
ip -s link ls eth0 # 查看统计信息, 指定网卡

ip maddr  # 广播
ip rule   # 路由策略, 和网卡有关
ip tunnel # 隧道

                              # 使用 iperf 测试的时候需要关掉防火墙: sudo systemctl stop firewalld
iperf -s                      # 服务器(TCP), 端口号为 5001
iperf -s -p 8080              # 服务器(TCP), 端口号为 8080
iperf -s -f MB                # 服务器(TCP), 端口号为 5001, 设置输出的单位
iperf -s -i 10                # 服务器(TCP), 端口号为 5001, 设置报告的时间间隔为 10s
iperf -s -D                   # 服务器(TCP), 端口号为 5001, 服务器在后台启动
iperf -s -1                   # 服务器(TCP), 端口号为 5001, 只接受一个客户端
iperf -s -N                   # 服务器(TCP), 端口号为 5001, 使用 TCP nodelay 算法
iperf -s -u                   # 服务器(UDP), 端口号为 5001
iperf -c 127.0.0.1            # 客户端(TCP), 服务器端口号为 5001
iperf -c 127.0.0.1 -p 8080    # 客户端(TCP), 服务器端口号为 8080
iperf -c 127.0.0.1 -i 1       # 客户端(TCP), 服务器端口号为 5001, 设置报告的时间间隔为 1s
iperf -c 127.0.0.1 -t 10      # 客户端(TCP), 服务器端口号为 5001, 设置测试时间为 10s
iperf -c 127.0.0.1 -f MB      # 客户端(TCP), 服务器端口号为 5001, 设置输出的单位
iperf -c 127.0.0.1 -b 100M    # 客户端(TCP), 服务器端口号为 5001, 设置发送速率
iperf -c 127.0.0.1 -n 100M    # 客户端(TCP), 服务器端口号为 5001, 设置测试的数据的大小
iperf -c 127.0.0.1 -k 100M    # 客户端(TCP), 服务器端口号为 5001, 设置测试的数据包的数量
iperf -c 127.0.0.1 -R         # 客户端(TCP), 服务器端口号为 5001, 反向测试, 服务端连客户端
iperf -c 127.0.0.1         -d # 客户端(TCP), 客户端连服务端的同时, 服务端同时连客户端, 端口号为 5001
iperf -c 127.0.0.1 -L 9090 -d # 客户端(TCP), 客户端连服务端的同时, 服务端同时连客户端, 端口号为 9090
iperf -c 127.0.0.1         -r # 客户端(TCP), 客户端连服务端结束后, 服务端连回客户端,   端口号为 5001
iperf -c 127.0.0.1 -L 9090 -r # 客户端(TCP), 客户端连服务端结束后, 服务端连回客户端,   端口号为 9090
iperf -c 127.0.0.1 -P 30      # 客户端(TCP), 客户端线程数为 30
iperf -c 127.0.0.1 -u         # 客户端(UDP)

```
curl -I ... # 只打印头部信息
firewall-cmd --list-ports                      # 查看所有打开的端口
firewall-cmd --list-services                   # 查看所有打开的服务
firewall-cmd --get-services                    # 查看所有的服务
firewall-cmd --reload                          # 重新加载配置
firewall-cmd --complete-reload                 # 重启服务
firewall-cmd             --add-service=http    # 添加服务
firewall-cmd --permanent --add-service=http    # 添加服务, 永久生效, 需要重新加载配置
firewall-cmd             --remove-service=http # 移除服务
firewall-cmd             --add-port=80/tcp     # 添加端口
firewall-cmd --permanent --add-port=80/tcp     # 添加端口, 永久生效, 需要重新加载配置
firewall-cmd             --remove-port=80/tcp  # 移除端口
firewall-cmd             --query-masquerade    # 检查是否允许伪装IP
firewall-cmd               --add-masquerade    # 允许防火墙伪装IP
firewall-cmd --permanent   --add-masquerade    # 允许防火墙伪装IP, 永久生效, 需要重新加载配置
firewall-cmd            --remove-masquerade    # 禁止防火墙伪装IP
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080
                                               # 端口转发, 0.0.0.0:80 --> 192.168.0.1:8080
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080 --permanent
                                               # 端口转发, 永久生效, 需要重新加载配置
firewall-cmd --runtime-to-permanent            # 将当前防火墙的规则永久保存

wget ... -O ...                    # 指定文件名称
wget ... -o ...                    # 指定日志文件
wget ... -c                        # 断点续传
wget ... -t ...                    # 指定重试的次数
wget ... -t 0                      # 不停重试
wget ... --mirror --convert-links  # 镜像下载, 递归, 并转换为本地 url
wget ... --user ... --password ... # 指定用户名和密码
wget ... --limit-rate ...          # 限制下载速度
wget ... --quota      ...          # 限制最大下载量

curl ...        # 下载到标准输出
curl ... -O     # 下载到文件, 文件名称从 url 中获取
curl ... -o ... # 下载到文件
curl ... --silent # 不显示进度信息
curl ... -C -     # 断点续传
curl ... --referer ... # 表明客户端是从哪儿跳过来的
curl ... --cookie  ... # 指明 cookie
curl ... --cookie-jar ... # 指明 cookie, 使用文件
curl ... --user-agent ... # 指明用户的客户端
curl ... -H ...           # 指明请求头部信息
curl ... --limit-rate ... # 限制下载速度
curl ... --max-filesize ... # 限制最大下载量
curl ... -u user:pass       # 指定用户名和密码
curl ... -I                 # 只打印 http 头部信息
curl ... --head             # 只打印 http 头部信息

