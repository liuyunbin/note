
##  申请独立的域名证书
### 1. 安装命令
```
$ apt install -y certbot
```

### 2. 签证书, 此时 80 和 443 端口号不能被占用
```
$ certbot certonly --standalone -d yunbinliu.com
```

### 3. 更新证书, 此时 80 和 443 端口号不能被占用
```
$ /usr/bin/certbot renew --force-renewal
```

### 4. 查看证书信息
```
$ certbot certificates
```

### 5. 更新证书前, 自动停止 openresty, 更新证书后, 自动启动 openresty 和 gost
```
$ /usr/bin/certbot renew --force-renewal --pre-hook "/usr/bin/openresty -s stop" --post-hook "/usr/bin/docker restart gost; /usr/bin/openresty"
```

## 申请通配符的域名证书
### 1. 安装 certbot 和 certbot-dns-cloudflare
```
$ apt remove certbot
$ snap install --classic certbot
$ ln -s /snap/bin/certbot /usr/bin/certbot
$ snap set certbot trust-plugin-with-root=ok
$ snap install certbot-dns-cloudflare
```

### 2. 生成 cloudflare 的 Edit zone DNS 的 api-token
https://dash.cloudflare.com/profile/api-tokens

### 3. 将申请的值配入文件 /etc/letsencrypt/cloudflare.ini
```
dns_cloudflare_api_token = .....
```

### 4. 生成证书
```
$ certbot certonly \
  --dns-cloudflare \
  --dns-cloudflare-credentials /etc/letsencrypt/cloudflare.ini \
  -d yunbinliu.com \
  -d "*.yunbinliu.com"
```

### 5. 配置 通配的 DNS 的 A 记录的解析
https://dash.cloudflare.com/a6a241765ac65eac8573d33e11409814/yunbinliu.com/dns/records

### 6. 一段时间后, 就可以看到解析成功了(可能得半个小时)

### 7. 参考资源
* https://certbot-dns-cloudflare.readthedocs.io/en/stable/
* https://certbot.eff.org/instructions?ws=nginx&os=ubuntufocal&tab=wildcard

### 8. 注意
1. 通配域名不能跨级, 即 1.yunbinliu.com 可以, 1.2.yunbinliu.com 不行

## 数字证书认证过程
1. 服务器将自己的公钥以及相关信息发送给数字证书认证中心
2. 数字证书认证中心使用服务端的信息生成摘要信息
3. 数字证书认证中心使用自己的私钥对摘要信息进行加密 -- 生成数字签名
4. 数字证书认证中心使用数字签名和服务器的信息生成数字证书
5. 数字证书认证中心将数字证书发回服务器

## 为什么认证中心要对摘要信息加密, 而不是整体加密?
* 非对称加密比较耗时
* 服务器的公钥信息是公开的, 对摘要进行加密主要是防止信息被篡改

## 证书检验过程
1. 服务器将自己的数字证书发给客户端
2. 客户端检验一下基本信息, 比如有效期, 域名
3. 客户端计算服务器信息的摘要信息
4. 客户端使用认证中心的公钥进行解密
5. 比较 4 5 的摘要信息是否一致, 一致表明, 该证书确实是指定域名的

## 浏览器输入 https://www.bing.com 后的行为
1. 解析到域名 www.bing.com.. 查找对应 IP, 顺序查找,
    * DNS cache
    * 本地 host 文件
    * DNS 服务器
2. 使用目标 IP 和端口号三次握手
3. 使用 TLS 检验服务端证书, 以及生成对称密钥 -- 后续通信使用对称密钥
4. 服务端将响应数据发给客户端
5. 客户端解析后展示

