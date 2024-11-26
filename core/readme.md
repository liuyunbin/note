
## core 不能生成的原因
```
# 1. ulimit 限制
ulimit -c           # 查看限制
ulimit -c unlimited # 设置允许生成, 可写入 bashrc

# 2. 该进程没有写入该目录的权限

# 3. 指定目录的指定文件已存在, 但该进程无权修改

# 4. /etc/security/limits.conf 限制

# 5. core 文件不在当前目录
echo 'core.%e.%p' > /proc/sys/kernel/core_pattern # 此步可写入 bashrc
```

## ubuntu 下设置生成 core --- 废弃
```
$ ulimit -c unlimited           # 设置允许生成的 core 文件大小不受限制
$                               # 可以考虑写入配置项 bashrc
$ echo "kernel.core_pattern=%e.%p" >> /etc/sysctl.conf
$                               # 将core命名方式写入配置文件: 文件名.进程号
$ sudo sysctl -p                # 使配置生效
$ sudo systemctl stop apport    # 停止此服务, 该服务会自动收集 core 文件
$ sudo systemctl disable apport # 禁止改服务自动启动
```


