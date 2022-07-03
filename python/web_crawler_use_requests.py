import requests
import json
import datetime

url = 'https://capi.tianyancha.com/cloud-tempest/advance'

headers = {
    'authority': 'capi.tianyancha.com',
    'method': 'POST',
    'path': '/cloud-tempest/advance',
    'scheme': 'https',
    'accept': '*/*',
    #'content-length': '249',
    'content-type': 'application/json; charset=UTF-8',
    'origin': 'https://www.tianyancha.com',
    'referer': 'https://www.tianyancha.com/',
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36',
    'version': 'TYC-Web',
    'x-tycid': '61b44820f8eb11eb90c25beeeaa71b03',
    'set-cookie': 'aliyungf_tc=c9465432f93e39f1192a2037eee53e2b25a63d1f9ec4ad41dd343e4f42b07255; Path=/; HttpOnly',
    'Set-Cookie': 'CLOUDID=431a6a37-e037-49dc-b0b4-e90d0356df6f; Expires=Sat, 10-Jun-2023 11:39:38 GMT; Path=/; HttpOnly'
}

# 注册开始时间 -- 与 1970-1-1 +0000 utc 的差值, 毫秒
x = datetime.datetime(1953, 1, 1)
y = datetime.datetime(1970, 1, 1) + datetime.timedelta(hours=8)
time1 = (x - y).total_seconds() * 1000
time1 = datetime.datetime(1953, 1, 1).timestamp() * 1000;

# 注册截止时间 -- 与 1970-1-1 +0000 utc 的差值, 毫秒
x = datetime.datetime.now()
y = datetime.datetime(1970, 1, 1) + datetime.timedelta(hours=8)
time2 = (x - y).total_seconds() * 1000

data = {
    # 输入注册资本
    "regCapitalRangeSet" : [
        5000,
        -1
    ],

    # 行业代码
    "categoryGuobiao2017Set" : [
        "01"
    ],

    # 省份代码
    "customAreaCodeSet" : [
        "00110000V2020"
    ],

    # 注册时间, 单位是毫秒
    "establishTimeRangeSet": [
        time1,
        time2
    ],

    "regStatusSet": [
        "存续（在营、开业、在业）"
    ],

    "pageNum": 1,
    "pageSize": 20,
    "searchType": 2
}

response = requests.post(url=url, headers=headers, data=json.dumps(data))
json_data = response.json()
print(json_data)
