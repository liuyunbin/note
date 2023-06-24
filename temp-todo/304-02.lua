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

