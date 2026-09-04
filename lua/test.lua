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
v6 = "123" .. "456"  -- 字符串连接
v7 = "123" +  "456"  -- 数字相加
v8 = #v6             -- 字符串大小
v9 = {789, 123, 456} -- 字典, key 未指定时, 使用索引作为 key, 索引以 1 开始
v9[111] = 222
local v10 = 123      -- 局部变量
v10 = "abc ABC abc ABC 123"

print("测试 nil           : ", v111)
print("测试 bool          : ", v1)
print("测试 浮点数        : ", v2)
print("测试 字符串(单引号): ", v3)
print("测试 字符串(双引号): ", v4)
print("测试 字符串(  跨行): ", v5)
print("测试 字符串(  连接): ", v6)
print("测试 字符串(  相加): ", v7)
print("测试 字符串(  大小): ", v8)

print("测试字符串大写: ",     string.upper(v10))
print("测试字符串小写: ",     string.lower(v10))
print("测试字符串逆序: ",     string.reverse(v10))
print("测试字符串格式化: ",   string.format("格式化: %s", v10))
print("测试字符串长度: ",     string.len(v10))
print("测试字符串重复: ",     string.rep(v10, 3))
print("测试字符 =>   数字: ", string.byte(v10))
print("测试数字 => 字符串: ", string.char(97, 98, 99, 100))
print("测试字符串子串: ",     string.sub(v10, 2))
print()
print("测试字符串    : ", v10)
print()
v12, count = string.gsub(v10,"a","123") -- 全部替换
print("测试字符串替换: ", v12, ", 次数: ", count)
v12, count = string.gsub(v10,"a","123", 1) -- 只替换一次
print("测试字符串替换: ", v12, ", 次数: ", count)
v12, count = string.gsub(v10,"%l","123") -- 全部替换(正则)
print("测试字符串替换: ", v12, ", 次数: ", count)

left, right = string.find(v10, "abc") ------------ 查找, 只返回第一次
print("测试字符串查找: 起始索引: ", left, ", 结束索引: ", right)
left, right = string.find(v10, "%l%l") ----------- 查找(正则), 只返回第一次
print("测试字符串查找: 起始索引: ", left, ", 结束索引: ", right)
left, right = string.find(v10, "%l%l", 1, true) -- 查找(非正则, 普通查找), 只返回第一次 -- 一般不用
print("测试字符串查找: 起始索引: ", left, ", 结束索引: ", right)

print("测试字符串匹配(只查询第一个匹配): ", string.match(v10, "123"))  -- 普通查找(第一个)
print("测试字符串匹配(只查询第一个匹配): ", string.match(v10, "%d%d")) -- 正则查找(第一个)

print("测试字符串匹配(多个): ") -- 查找(多个)
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

print()
print("测试字典: ")

for k, v in pairs(v9) do -- 不要用 ipairs
    print(k, " -> ", v)
end

print("测试 table => string: ", table.concat(v9, '-'))
table.insert(v9, "123456")
print("测试 table 插入: ", v9[4])
table.remove(v9)
print("测试 table 删除: ", v9[4])
print("测试 table 排序, 排序前: ") -- 只能对索引从1开始的连续的值排序
for k,v in pairs(v9) do
    print(k, " -> ", v)
end
table.sort(v9)

print("测试 table 排序, 排序后: ")
for k,v in pairs(v9) do
    print(k, " -> ", v)
end

v10 = v9
v10 = {1, 2, 3}
v10[1] = "abc"
print("测试赋值后修改: ") -- 会影响原值 -- 可以当成指针理解
for k,v in pairs(v9) do
    print(k, " -> ", v)
end

v1 = "123"
v2 = v1
v2 = "456" -- 不会影响原值
print(v1)
print(v2)

-- 赋值和函数传参时
-- 数字和字符串是值传递
-- table 可以理解为是指针, 修改内容时, 会影响原值, 整体新赋值时, 不会影响原值

v1 = {}
v1["abc"] = 456
print("测试table使用点: ", v1.abc)

print()
print("测试循环和选择判断: ")

for i = 1, 10, 2 do
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

print()

function test1(v1)
    v1 = 123 -- 参数 不影响函数外变量 v
    print("调函数内: ", v1)
end

function test2(v1)
    v = 123  -- 这个会影响函数外变量 v -- 不建议
    print("调函数内: ", v)
end

function test3(v1)
    local v = 123  -- 这个不会影响函数外变量 v, 建议
    print("调函数内: ", v)
end

function test4(v1)
    v1[1] = 123
    print("调函数内: ", v1[1])
end

function test5(v1)
    v[1] = 123
    print("调函数内: ", v[1])
end

function test6(v1)
    local v = v1[1]
    v = 123
    print("调函数内: ", v)
end

print()
print("测试函数(传递字符串): ")

v = "abc"
print()
print("调函数前: ", v)
test1(v)
print("调函数后: ", v)

v = "abc"
print()
print("调函数前: ", v)
test2(v)
print("调函数后: ", v)

v = "abc"
print()
print("调函数前: ", v)
test3(v)
print("调函数后: ", v)

v = {1, 2, 3}
print()
print("调函数前: ", v[1])
test4(v)
print("调函数后: ", v[1])

print()
print("测试函数(传递 table): ")

v = {1, 2, 3}
print()
print("调函数前: ", v[1])
test5(v)
print("调函数后: ", v[1])

v = {1, 2, 3}
print()
print("调函数前: ", v[1])
test6(v)
print("调函数后: ", v[1])

-- local mysql = require "resty.mysql"  模块

print()
print("测试类 元表: ")

-- 查找规则:
-- 1. 在表中查找，如果找到，返回该元素，找不到则继续
-- 2. 判断该表是否有元表，如果没有元表，返回 nil，有元表则继续
-- 3. 判断元表有没有 __index
--      如果 __index 方法为 nil，则返回 nil
--      如果 __index 方法是一个表，则重复 1、2、3
--      如果 __index 方法是一个函数，则返回该函数的返回值

-- 元类
Rectangle = {area = 0, length = 0, breadth = 0}

-- 派生类的方法 new
function Rectangle:new (length,breadth)
  o = {}
  setmetatable(o, self) -- 普通表关联到元表, self 表示当前元表
  self.__index = self -- 是否查找 self 表
  self.length = length
  self.breadth = breadth
  self.area = length*breadth;
  return o
end

-- 派生类的方法 printArea
function Rectangle:printArea ()
  print("矩形面积为 ",self.area)
end

r = Rectangle:new(10,20)
print(r.length)
r:printArea()

#!/usr/bin/lua

-- 执行 shell 命令

print("测试输出 ls 的结果到屏幕, 返回状态码")

local ret = os.execute("ls")

if (ret == true) then
    print("执行成功")
else
    print("执行失败: ")
end

print("测试输出 date 的结果到变量")
local t = io.popen("date")  -- 执行命令
local v = t:read("*all")    -- 获取命令的执行结果
print("执行结果: ", v)

