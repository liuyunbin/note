#!/usr/bin/bash

echo "1. 获取 openresty 的目录"
openresty_dir=$(dirname $(readlink -f $(which openresty)))/../../

echo "2. 备份 nginx 配置"
mv $openresty_dir/nginx/conf/nginx.conf $openresty_dir/nginx/conf/nginx.conf-back

echo "3. 将本地 ip2region.lua, data/ip2region.xdb  和 nginx.conf 拷入指定目录"
mkdir -p $openresty_dir/nginx/lua/
cp nginx.conf $openresty_dir/nginx/conf/nginx.conf
cp xdb_searcher.lua ip2region.lua  ../../data/ip2region.xdb $openresty_dir/nginx/lua/

echo "4. 重写加载 openresty"
openresty -s reload

echo "5. 休眠 3 秒"
sleep 3

echo "6. 使用 curl 127.0.0.1/ip 测试"
curl 127.0.0.1/ip

echo "7. 恢复 oepnresty 的配置"
mv $openresty_dir/nginx/conf/nginx.conf-back $openresty_dir/nginx/conf/nginx.conf
openresty -s reload

