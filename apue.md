
## ubuntu 下设置生成 core
```
$ ulimit -c unlimited           # 设置允许生成的 core 文件大小不受限制
$                               # 可以考虑写入配置项 bashrc
$ echo "kernel.core_pattern=%e.%p" >> /etc/sysctl.conf
$                               # 将core命名方式写入配置文件: 文件名.进程号
$ sudo sysctl -p                # 使配置生效
$ sudo systemctl stop apport    # 停止此服务, 该服务会自动收集 core 文件
$ sudo systemctl disable apport # 禁止改服务自动启动
```

## core 不能生成的原因
* core 文件大小受 ulimit 的限制
* 当前进程没有权限在指定目录生成文件
* 指定目录的指定文件已存在, 但改进程无权修改

