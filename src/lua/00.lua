#!/usr/bin/lua

-- 这是注释

--[[
 多行注释
 多行注释
--]]

-- 类型

v1 = true
v2 = 3.1415926 * 2
v3 = '123\t456'
v4 = "123\t456"
v5 = [[
    123
    456
]]
v6 = "123" .. "456" -- 字符串连接
v7 = "123" +  "456" -- 数字相加
v8 = #v6            -- 字符串大小
v9 = {789, 123, 456} -- 字典, key 未指定时, 使用索引作为 key, 索引以 1 开始
v9[111] = 222
local v10 = 123   -- 局部变量
v10 = "abc ABC abc ABC 123"

print("测试 bool          : ", v1)
print("测试 浮点数        : ", v2)
print("测试 字符串(单引号): ", v3)
print("测试 字符串(双引号): ", v4)
print("测试 字符串(  跨行): ", v5)
print("测试 字符串(  连接): ", v6)
print("测试 字符串(  相加): ", v7)
print("测试 字符串(  大小): ", v8)

print("测试字符串大写: ", string.upper(v10))
print("测试字符串小写: ", string.lower(v10))
print("测试字符串替换: ", string.gsub(v10,"a","123"))
print("测试字符串查找: ", string.find(v10,"abc"))
print("测试字符串逆序: ", string.reverse(v10))
print("测试字符串格式化: ", string.format("格式化: %s", v10))
print("测试字符串长度: ", string.len(v10))
print("测试字符串重复: ", string.rep(v10, 3))
print("测试字符 =>   数字: ", string.byte(v10))
print("测试数字 => 字符串: ", string.char(97, 98, 99, 100))
print("测试字符串 子串: ", string.sub(v10, 2))
print("测试字符串匹配(只查询第一个匹配): ", string.match(v10, "123"))
print("测试字符串匹配(多个): ")
for v in string.gmatch(v10, "%a+") do
    print(v)
end
-- 上述匹配支持正则表达式
-- %a: 任何字母
-- %c: 任何控制符(例如\n)
-- %d: 任何数字
-- %l: 任何小写字母
-- %p: 任何标点
-- %s: 空白字符
-- %u: 任何大写字母
-- %w: 任何字母/数字
-- %x: 任何十六进制数
-- %z: 任何代表0的字符
-- 大写表相反

print("测试字典: ")

for k,v in pairs(v9) do
    print(k, " -> ", v)
end

print("测试 table => string: ", table.concat(v9, '-'))
table.insert(v9, "123456")
print("测试 table 插入: ", v9[4])
table.remove(v9)
print("测试 table 删除: ", v9[4])
print("测试 table 排序, 排序前: ") -- 只能对数组排序, 不能对字典排序
for k,v in pairs(v9) do
    print(k, " -> ", v)
end
table.sort(v9)

print("测试 table 排序, 排序后: ")
for k,v in pairs(v9) do
    print(k, " -> ", v)
end

function test(n)
    if n == 0 then
        return true
    else
        return false
    end
end

print("测试函数调用: ", test(0))
print("测试函数调用: ", test(1))

print("测试循环和选择判断: ")

for i = 1,10,2 do
    print(i)
end

for k, v in pairs(v9) do
    print(k, " -> ", v)
end

i = 1
while (i < 10) do
    print (i)
    i = i + 3
end

i = 10
if (i == 0) then
    print("i == 0")
else if (i == 1)
    then
        print("i == 1")
    else
        print("i > 1")
    end
end

if ("123" == 123) then
    print('"123" == 123');
else
    print('"123" != 123');
end

