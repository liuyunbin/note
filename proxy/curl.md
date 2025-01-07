
## 1. http 代理
```
curl -x http://host-60:8001              http://www.google.com;
curl -x http://admin:123456@host-60:8002 http://www.google.com;

curl -x http://host-60:8001              https://www.google.com;
curl -x http://admin:123456@host-60:8002 https://www.google.com;
```

## 2. socks4 代理 --- 不行, 域名解析在本地
```
curl -x socks4://host-60:8003  http://www.google.com;
curl -x socks4://host-60:8003 https://www.google.com;
```

## 3. socks4a 代理
```
curl -x socks4a://host-60:8004  http://www.google.com;
curl -x socks4a://host-60:8004 https://www.google.com;
```

## 4. socks5 代理 --- 不行, 域名解析在本地
```
curl -x socks5://host-60:8005              http://www.google.com;
curl -x socks5://admin:123456@host-60:8006 http://www.google.com;

curl -x socks5://host-60:8005              https://www.google.com;
curl -x socks5://admin:123456@host-60:8006 https://www.google.com;
```

## 5. socks5h 代理
```
curl -x socks5h://host-60:8005              http://www.google.com;
curl -x socks5h://admin:123456@host-60:8006 http://www.google.com;

curl -x socks5h://host-60:8005              https://www.google.com;
curl -x socks5h://admin:123456@host-60:8006 https://www.google.com;
```

## 6. https 代理 --- 貌似不支持
```
curl -x https://yunbinliu.com:8007              http://www.google.com;
curl -x https://admin:123456@yunbinliu.com:8008 http://www.google.com;

curl -x https://yunbinliu.com:8007              https://www.google.com;
curl -x https://admin:123456@yunbinliu.com:8008 https://www.google.com;
```

