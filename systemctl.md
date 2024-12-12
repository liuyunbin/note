
## 1. 启动服务
```
systemctl list-unit-files | grep mysql # 1. 查看服务的名称 及其 状态
systemctl is-active  mysql.service     # 2. 查看是否已启动
systemctl start      mysql.service     # 3. 启动服务
systemctl is-active  mysql.service     # 4. 再次查看是否已启动
```

## 2. 停止服务
```
systemctl list-unit-files | grep mysql # 1. 查看服务的名称 及其 状态
systemctl is-active  mysql.service     # 2. 查看是否已启动
systemctl stop       mysql.service     # 3. 停止服务
systemctl is-active  mysql.service     # 4. 再次查看是否已启动
```

## 3. 重启服务
```
systemctl list-unit-files | grep mysql # 1. 查看服务的名称 及其 状态
systemctl is-active  mysql.service     # 2. 查看是否已启动
systemctl restart    mysql.service     # 3. 重启服务
systemctl is-active  mysql.service     # 4. 再次查看是否已启动
```

## 4. 设置开机启动
```
systemctl list-unit-files | grep mysql # 1. 查看服务的名称 及其 状态
systemctl is-enabled mysql.service     # 2. 查看是否开机自动启动
systemctl    enable  mysql.service     # 3. 设置开机自动启动
systemctl is-enabled mysql.service     # 4. 再次查看是否开机自动启动
```

## 5. 禁止开机启动
```
systemctl list-unit-files | grep mysql # 1. 查看服务的名称 及其 状态
systemctl is-enabled mysql.service     # 2. 查看是否开机自动启动
systemctl   disable  mysql.service     # 3. 禁止开机自动启动
systemctl is-enabled mysql.service     # 4. 再次查看是否开机自动启动
```

