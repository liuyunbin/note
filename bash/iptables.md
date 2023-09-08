
## 说明
```
iptables 表格(table) 过滤链(chain)
* filter -- 数据包过滤 -- 默认使用
    * INPUT ---- 输入
    * OUTPUT --- 输出
    * FORWARD -- 转发
* nat ----- 网络地址转换
    * prerouting --- 路由选择之前
    * postrouting -- 路由选择之后
* mangle --- 修改数据包的信息
    * prerouting
    * postrouting
    * input
    * output
    * forward
* raw ------ 跟踪包信息
    * output
    * prerouting
* 优先级: raw > mangle > nat > filter
* iptables [-t 表名] 管理选项 [链名] [匹配条件] [-j 控制类型]
* iptables -t filter -A ... ---- 添加规则
* iptables -t filter -D ... ---- 删除规则
* iptables -t filter -I ... ---- 插入规则
* iptables -t filter -R ... ---- 修改规则
* iptables -t filter -F ... ---- 清空规则
* iptables -t filter -L ... ---- 列出规则
* iptables -t filter -L --line-numbers ... ---- 列出规则, 包括顺序号
* iptables -t filter -L -n ............... ---- 列出规则, 使用数字而不是域名和服务名称
* iptables -t filter -L -v ............... ---- 列出规则, 详细信息
* iptables -t filter -P .................. ---- 设置指定链的默认策略
* 匹配条件
    * -s ---- 源地址
    * -d ---- 目标地址
    * -p tcp --sport ... --- TCP 源端口
    * -p tcp --dport ... --- TCP 目标端口
    * -p udp --sport ... --- UDP 源端口
    * -p udp --dport ... --- UDP 目标端口
    * -p icmp
    * -m state --state NEW,ESTABLISHED --- 新建立 或 已连接
    * -m multiport --ports ................ --- 多端口
    * -m multiport --source-ports ......... --- 多源端口
    * -m multiport --destination-ports .... --- 多目的端口
    * -m iprange --src-range .............. --- 多源 IP
    * -m iprange --dst-range .............. --- 多目标 IP
    * -m connlimit ! --connlimit-above n ------ 同 IP 连接的上限
    * -m limit --limit RATE ------------------- 限制响应速度
    * -m limit --limit-burst ------------------ 一批请求的最高峰值
    * -m string --algo {bm|kmp} --------------- 屏蔽特殊的字符串 选择匹配算法
    * -m string --string "STRING" ------------- 屏蔽特殊的字符串 正则表达式
* 控制类型
    * ACCEPT ------ 接收
    * DROP -------- 丢弃
    * REJECT ------ 拒绝
    * ACCEPT ------ 放行
    * DROP -------- 丢弃
    * REJECT ------ 拒绝
    * DNAT -------- 目标地址转换
    * SNAT -------- 源地址转换
    * REDIRECT ---- 端口重定向
    * MASQUERADE -- 地址伪装
```

