
## 1. 开启防火墙服务
```
firewall-cmd --list-services                 # 1. 查看目前开启的服务
firewall-cmd --permanent --add-service=mysql # 2. 永久开启服务
firewall-cmd --reload                        # 3. 重新加载防火墙
firewall-cmd --list-services                 # 4. 再次查看目前开启的服务
```

## 2. 关闭防火墙服务
```
firewall-cmd --list-services                    # 1. 查看目前开启的服务
firewall-cmd --permanent --remove-service=mysql # 2. 永久移除服务
firewall-cmd --reload                           # 3. 重新加载防火墙
firewall-cmd --list-services                    # 4. 再次查看目前开启的服务
```

## 3. 开启防火墙端口号
```
firewall-cmd --list-ports                    # 1. 查看所有打开的端口
firewall-cmd --permanent --add-port=80/tcp   # 2. 永久开启添加端口
firewall-cmd --reload                        # 3. 重新加载防火墙
firewall-cmd --list-ports                    # 4. 再次查看所有打开的端口
```

## 4. 关闭防火墙端口号
```
firewall-cmd --list-ports                     # 1. 查看所有打开的端口
firewall-cmd --permanent --remove-port=80/tcp # 2. 永久移除端口
firewall-cmd --reload                         # 3. 重新加载防火墙
firewall-cmd --list-ports                     # 4. 再次查看所有打开的端口
```

## 5. 允许伪装IP
```
firewall-cmd             --query-masquerade    # 1. 检查是否允许伪装IP
firewall-cmd --permanent   --add-masquerade    # 2. 永久允许防火墙伪装IP
firewall-cmd --reload                          # 3. 重新加载防火墙
firewall-cmd             --query-masquerade    # 4. 再次检查是否允许伪装IP
firewall-cmd --permanent --add-forward-port=port=80:proto=tcp:toaddr=192.168.0.1:toport=8080
                                               # 5. 端口转发, 0.0.0.0:80 --> 192.168.0.1:8080
firewall-cmd --reload                          # 6. 重新加载防火墙
```


## 6. 禁止伪装IP
```
firewall-cmd              --query-masquerade    # 1. 检查是否允许伪装IP
firewall-cmd --permanent --remove-masquerade    # 2. 永久禁止防火墙伪装IP
firewall-cmd --reload                           # 3. 重新加载防火墙
firewall-cmd              --query-masquerade    # 4. 再次检查是否允许伪装IP
```

## 7. 将当前防火墙的规则永久保存
```
firewall-cmd --runtime-to-permanent
```

