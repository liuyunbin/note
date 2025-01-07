
## 1. http 代理
```
wget http://www.google.com -e http_proxy=http://host-60:8001
wget http://www.google.com -e http_proxy=http://admin:123456@host-60:8002

wget https://www.google.com -e https_proxy=http://host-60:8001
wget https://www.google.com -e https_proxy=http://admin:123456@host-60:8002
```

## 2. socks4 代理 --- 不支持
```
wget  http://www.google.com -e  http_proxy=socks4://host-60:8003
wget https://www.google.com -e https_proxy=socks4://host-60:8003
```

## 3. socks4a 代理 --- 不支持
```
wget  http://www.google.com -e  http_proxy=socks4a://host-60:8004
wget https://www.google.com -e https_proxy=socks4a://host-60:8004
```

## 4. socks5 代理 --- 不支持
```
wget http://www.google.com -e http_proxy=socks5://host-60:8005
wget http://www.google.com -e http_proxy=socks5://admin:123456@host-60:8006

wget https://www.google.com -e https_proxy=socks5://host-60:8005
wget https://www.google.com -e https_proxy=socks5://admin:123456@host-60:8006
```

## 5. socks5h 代理 --- 不支持
```
wget http://www.google.com -e http_proxy=socks5h://host-60:8005
wget http://www.google.com -e http_proxy=socks5h://admin:123456@host-60:8006

wget https://www.google.com -e https_proxy=socks5h://host-60:8005
wget https://www.google.com -e https_proxy=socks5h://admin:123456@host-60:8006
```

## 6. https 代理 --- 貌似不支持
```
wget http://www.google.com -e http_proxy=https://yunbinliu.com:8007
wget http://www.google.com -e http_proxy=https://admin:123456@yunbinliu.com:8008

wget https://www.google.com -e https_proxy=https://yunbinliu.com:8007
wget https://www.google.com -e https_proxy=https://admin:123456@yunbinliu.com:8008
```

