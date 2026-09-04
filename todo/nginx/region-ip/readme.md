
pip install IPy
pip install redis


# 目录说明
* 由于 ip2region/binding/lua 的实现是基于 lua 5.2 及其以后的版本实现的
* 而 openresty 使用的版本是 lua 5.1, 两者不兼容
* 为了处理兼容问题, 才有了此目录
* 本目录只是基于 ip2region/binding/lua 的修改

# 测试环境
```
Ubuntu 22.04 x86_64
```

# 安装依赖
```
apt install openresty
apt install lua5.1
apt install luarocks
luarocks install luabitop
```

# 使用 openresty 测试
## 1. 查看使用的 openresty 和 lua 版本
```
$ openresty -v
nginx version: openresty/1.25.3.1
$ resty -e "return print(_VERSION)"
Lua 5.1
```

## 2. 查看当前的目录
```
$ pwd
/root/github/ip2region/binding/openresty
```

## 3. 修改当前目录下的 nginx.conf 和 ip2region.lua 中文件的路径

```
./test_openresty.sh
```

## 数据生成
```
$ ./xdb_make --db ip2region.xdb --src ../../data/ip.merge.txt
took: 1.46s
```

## 数据更新
```
$ ./xdb_edit --old ../../data/ip.merge.txt --new 1.txt
took: 1.46s
```

