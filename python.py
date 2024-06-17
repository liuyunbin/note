#!/usr/bin/env python3

# 写入 JSON 文件(整个文件是一个JSON)
import json

results = {"abc":"中国"}
file_name = "1.json"
with open(file_name, 'w', encoding='utf-8') as f:
    json.dump(results, f, ensure_ascii=False)

# 读取 JSON 文件(整个文件是一个JSON)
import json

file_name = "1.json"
with open(file_name, 'r', encoding='utf-8') as f:
    data = json.load(f)
#print(data)

# 写入 JSON 文件(每行一个JSON)
import json

results = {"abc":"中国"}
file_name = "1.json"
with open(file_name, 'w', encoding='utf-8') as f:
    data = json.dumps(results, ensure_ascii=False)
    f.write(data + "\n")
    f.write(data + "\n")

# 读取 JSON 文件(每行一个JSON)
import json

file_name = "1.json"
with open(file_name, 'r', encoding='utf-8') as f:
    for line in f:
        data = json.loads(line)
#print(data)

# 写入 CSV 文件(一次写入多行)
import csv

results = [["a","b","c"], ["中","国","人"]]
file_name = "1.csv"
with open(file_name, 'w', encoding='utf-8', newline='') as f:
    writer = csv.writer(f, lineterminator='\n')
    writer.writerows(results)

# 读取 CSV 文件
import csv

file_name = "1.csv"
with open(file_name, 'r', encoding='utf-8', newline='') as f:
    reader = csv.reader(f)
    results = list(reader)
    print(results)

# 写入 CSV 文件(一次写入一行)
import csv

results = [["a","b","c"], ["中","国","人"]]
file_name = "1.csv"
with open(file_name, 'w', encoding='utf-8', newline='') as f:
    writer = csv.writer(f, lineterminator='\n')
    writer.writerow(results[0])
    writer.writerow(results[1])



### 安装：
#* windows 7, 3.8.10: https://www.python.org/downloads/windows/
#
### IDE
#* pycharm : https://www.jetbrains.com/pycharm/
#
### 安装第三方模块
#* sudo apt install python3-pip
#
### python 数据类型
#* 数字类型:
#    * 整数, 可表示任意大小, 可用 _ 分割, 100_100 表示 100100
#    * bool 类型, True, False, and, or, not
#    * 浮点数
#    * 复数
#* 字符串
#    * 单引号和双引号的作用完全相同
#    * 三引号可以跨行
#    * r 不让字符串转义, 例如, "123\n" 中的 '\n' 不会转义
#    * + 用于 字符串相加, 例如, "123" + "456" == "123456"
#    * * 用于重复字符串, 例如, "123"*2 == "123123"
#    * 字符串的值不能变
#    * 下标从左到右以 0 开始, 从右到左以 -1 开始
#    * 子串, [左标, 右标, 步长], 例如, "0123456"[1:5:2] == "13"
#    * "中国".encode("utf8"), str -> utf8
#    * b'\xe4\xb8\xad\xe5\x9b\xbd'.decode("utf8"), utf8 -> str
#    * len(str) 字符数
#    * len(b'\xe4\xb8\xad\xe5\x9b\xbd') 字节数
#    * str.strip() 去除首尾的空白字符
#    * str.lower() 小写
#    * str.upper() 大写
#    * str.replace("123", "456") 字符串替换
#    * str.split(",") 字符串切割
#    * str1 in str2
#    * str1 + str2
#* List 列表
#    * 使用中括号包含, 使用 逗号 分割
#    * 列表中的元素类型可以不同
#    * + 用于列表相加, * 用于重复列表
#    * 列表中的值可以变化
#    * 下标从左到右以 0 开始, 从右到左以 -1 开始
#    * append, insert 添加元素, remove, pop 删除元素, len 元素个数
#    * 空列表 []
#* Tuple 元组
#    * 使用小括号包含, 使用 逗号 分割
#    * 元组中的元素类型可以不同
#    * 元组中的值不能变化
#    * 下标从左到右以 0 开始, 从右到左以 -1 开始
#    * 空元组 ()
#    * 一个元素的元组 (1,)
#* Set 集合
#    * 使用大括号包含, 使用 逗号 分割
#    * 空集合 set{}
#    * add 添加元素
#    * update 更新集合
#    * remove  移除元素, 如果元素不存在, 报错
#    * discard 移除元素, 如果元素不存在, 不报错
#    * pop 随机删除一个元素
#* Dict 字典
#    * 使用大括号包含, 使用 逗号 分割的 key, val 串
#    * key 的值为不可变类型
#    * 同一字典 key 值类型必须相同
#    * 空字典 {}
#
### python 命名空间和作用域
#    * global 指明使用 全局变量
#    * nonlocal 指明使用上一层作用域的变量
#
### python 常用功能
#### json 和 string 相互转化
#* json --> string: json.dumps()
#* string --> json: json.loads()
#
#### time, 核心是时间元组
#* 概念
#  * 时间戳: 与 1970-01-01 0:0:0 +0000 utc 的浮点秒数的差值
#  * 时间戳不受时区影响
#  * 时间戳不处理闰秒
#* 时间戳, 字符串 --> 时间元组
#  * t = time.strptime("2022-02-02 00:00:00", "%Y-%m-%d %H:%M:%S") # 字符串 --> 时间元组
#  * t = time.localtime(-1)                                     # 时间戳 --> 时间元组, utc +0800, 本地时间
#  * t = time.gmtime(-1)                                        # 时间戳 --> 时间元组, utc +0000
#* 时间元组 等 --> 时间戳
#  * time.time()                                                # 当前时间的时间戳
#  * time.mktime(t)                                             # 时间元组 --> 时间戳, 其中时间元组是本地时间
#* 时间元组 --> 字符串
#  * time.strftime("%Y-%m-%d %H:%M:%S", t)                      # 时间元组 --> 字符串
#* time.sleep(10)                                               # 停止 10s
#* time, 只能表示 1970 年之后的数据?
#    * time.strptime("1950-01-01 8:0:0", "%Y-%m-%d %H:%M:%S")
#    * time.mktime(dt)
#    * Linux 不报错
#    * windows 报错
#
#### datetime, 核心是类 datetime, timedelta
#* 时间戳, 字符串 --> datetime
#  * dt = datetime.datetime.now()
#  * dt = datetime.datetime(2020, 6, 26)
#  * dt = datetime.datetime.fromtimestamp(t) # 时间戳 --> datetime, 基于 utf +0800 的 datetime，本地时间
#  * dt = datetime.datetime.utcfromtimestamp(t) # 时间戳 --> datetime, 基于 utf +0000 的 datetime
#  * dt = datetime.datetime.strptime("2022-02-02 0:0:0", "%Y-%m-%d %H:%M:%S") # 字符串 --> datetime
#* datetime --> 字符串
#  * dt.strftime("%Y-%m-%d %H:%M:%S")
#* datetime --> 时间戳
#  * dt.timestamp()
#* timedelta
#    * (x - y).total_seconds() # 两个日期的差的秒数
#    * x + timedelta(hours=8)  # 日期 和 时分秒 加减 运算
#* 计算时间戳, 使用当前分区计算
#    * x = datetime.now()
#    * y = datetime.datetime(1970, 1, 1) + datetime.timedelta(hours=8)
#    * (x-y).total_seconds()
#* 额外说明
#    * 由于 datetime 比 time 更方便, 所以建议使用 datetime
#    * 由于直接计算时间戳受制于具体平台的实现, 能表示的范围也不同,
#        * 所以建议使用 datetime 和 datedelta 计算时间戳
#
#### requests
#* requests.get(url=, headers=, params=)
#* requests.post(url=, headers=, data=)
#
#### os
#* os.getcwd() # 返回当前目录
#* os.system('ls') # 执行命令, 返回成功或失败
#* a=os.popen('ls'); a.read()  # 执行命令, 返回执行的结果
#
#### random
#* random.random() # 产生随机数
#
