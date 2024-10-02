
## 1. 开启防火墙服务
```
firewall-cmd --list-services                 # 1. 查看目前开启的服务
firewall-cmd --permanent --add-service=mysql # 2. 永久开启服务
firewall-cmd --reload                        # 3. 重新加载防火墙
firewall-cmd --list-services                 # 4. 再次查看目前开启的服务
```

## 2. 关闭防火墙服务 --- TODO
```
firewall-cmd --list-services                 # 1. 查看目前开启的服务
firewall-cmd --permanent    --remove-service=mysql # 移除服务
firewall-cmd  --add-service= # 3. 永久开启服务
firewall-cmd --reload                        # 4. 重新加载防火墙
firewall-cmd --list-services                 # 5. 再次查看目前开启的服务
```

## 3. 开启防火墙端口号
```
firewall-cmd --list-ports                    # 1. 查看所有打开的端口
firewall-cmd --permanent --add-port=80/tcp   # 2. 永久开启添加端口
firewall-cmd --reload                        # 3. 重新加载防火墙
firewall-cmd --list-ports                    # 4. 再次查看所有打开的端口
```

## 4. 关闭防火墙端口号 ---- TOOD
```
firewall-cmd --list-services                 # 1. 查看目前开启的服务
firewall-cmd --list-ports                    # 2. 查看所有打开的端口
firewall-cmd             --remove-port=80/tcp  # 移除端口
firewall-cmd --permanent --add-service=mysql # 3. 永久开启服务
firewall-cmd --reload                        # 4. 重新加载防火墙
firewall-cmd --list-services                 # 5. 再次查看目前开启的服务
```

## 5. 



firewall-cmd --get-services                    # 查看所有的服务






firewall-cmd             --query-masquerade    # 检查是否允许伪装IP

firewall-cmd --permanent   --add-masquerade    # 允许防火墙伪装IP, 永久生效, 需要重新加载配置
firewall-cmd            --remove-masquerade    # 禁止防火墙伪装IP
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080
                                               # 端口转发, 0.0.0.0:80 --> 192.168.0.1:8080
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080 --permanent
                                               # 端口转发, 永久生效, 需要重新加载配置
firewall-cmd --runtime-to-permanent            # 将当前防火墙的规则永久保存

