import requests
import json
import time
import csv
import datetime
import itertools
import os

# 1. 获取行业信息
industry = []

def get_industry_code(s):
    industry_code = {
        "医药制造业": 1,
        "铁路、船舶、航空航天和其他运输设备制造业": 2,
        "专用设备制造业": 3,
        "电气机械和器材制造业": 4,
        "计算机、通信和其他电子设备制造业": 5,
        "仪器仪表制造业": 6
    }
    return industry_code.get(s, -1)
def get_industry_child_list(it1):
    if "childList" not in it1 or len(it1["childList"]) == 0: # 一层
        index = get_industry_code(it1["name"])
        if index != -1:
            industry.append({
                    "name": it1["name"],
                    "index": index,
                    "data": {
                        "value": it1["value"]
                    }
                }
            )
    else:
        for it2 in it1["childList"]:
            if "childList" not in it2 or len(it2["childList"]) == 0 or True: # 两层
                index = get_industry_code(it2["name"])
                if index != -1:
                    industry.append({
                            "name": it2["name"],
                            "index": index,
                            "data": {
                                "value": it1["value"],
                                "childList": [
                                    { "value": it2["value"] }
                                ]
                            }
                        }
                    )
            else:
                for it3 in it2["childList"]:
                    if "childList" not in it3 or len(it3["childList"]) == 0:  # 三层
                        index = get_industry_code(it3["name"])
                        if index != -1:
                            industry.append(
                                {
                                    "name": it3["name"],
                                    "index": index,
                                    "data": {
                                        "value": it1["value"],
                                        "childList": [
                                            {
                                                "value": it2["value"],
                                                "childList": [
                                                    { "value": it3["value"] }
                                                ]
                                            }
                                        ]
                                    }
                                }
                            )
                    else:
                        for it4 in it3["childList"]:
                            if "childList" not in it4 or len(it4["childList"]) == 0:  # 四层
                                index = get_industry_code(it4["name"])
                                if index != -1:
                                    industry.append(
                                        {
                                            "name": it4["name"],
                                            "index": index,
                                            "data": {
                                                "value": it1["value"],
                                                "childList": [
                                                    {
                                                        "value": it2["value"],
                                                        "childList": [
                                                            {
                                                                "value": it3["value"],
                                                                "childList": [
                                                                    { "value": it4["value"] }
                                                                ]
                                                            }
                                                        ]
                                                    }
                                                ]
                                            }
                                        }
                                    )
def get_industry():
    industry_url = 'https://static.tianyancha.com/static/pro/industry_level4_v2017.json'
    items = requests.get(url=industry_url).json()["data"]
    for item in items:
        get_industry_child_list(item)

get_industry()
#print(industry)

# 2. 获取省份信息
areas = []

def get_area_code(s):
    area_code = {
        "太原市": 1,
        "大同市": 2,
        "阳泉市": 3,
        "长治市": 4,
        "晋城市": 5,
        "朔州市": 6,
        "晋中市": 7,
        "运城市": 8,
        "忻州市": 9,
        "临汾市": 10,
        "吕梁市": 11
    }
    return area_code.get(s, -1)
def get_areas_child_list(item):
    #if len(item["childList"]) == 0 or "childList" not in item["childList"][0] or True:  # 港澳台 和直辖市
    if len(item["childList"]) == 0: # 港澳台
        pass
    else:
        #areas.append(
        #    {
        #        "name": item["name"],
        #        "value": item["value"],
        #        "data": {
        #            "value": item["value"]
        #        }
        #    }
        #)
        if item["name"] == "山西省":
            for it in item["childList"]:
                areas.append(
                    {
                        "name": it["name"],
                        "index": get_area_code(it["name"]),
                        "data": {
                            "value": item["value"],
                            "childList": [
                                { "value": it["value"] }
                            ]
                        }
                    }
                )
def get_areas():
    areas_url = 'https://static.tianyancha.com/static/pro/area_level3_v2024.json'
    items = requests.get(url=areas_url).json()["data"]
    for item in items:
        get_areas_child_list(item)
get_areas()
#print(areas)

# 3. 获取时间戳的差值
def get_time():
    # 注册开始时间 -- 与 1970-1-1 +0000 utc 的差值, 毫秒
    #x = datetime.datetime(1953, 1, 1)
    #y = datetime.datetime(1970, 1, 1) + datetime.timedelta(hours=8)
    #time1 = (x - y).total_seconds() * 1000

    # 注册截止时间 -- 与 1970-1-1 +0000 utc 的差值, 毫秒
    x = datetime.datetime.now()
    y = datetime.datetime(1970, 1, 1) + datetime.timedelta(hours=8)
    time2 = (x - y).total_seconds() * 1000

    return str(int(time2))

def get_end_time(year):
    # 注册开始时间 -- 与 1970-1-1 +0000 utc 的差值, 毫秒
    x = datetime.datetime(1953, 1, 1)
    y = datetime.datetime(1970, 1, 1) + datetime.timedelta(hours=8)
    time1 = (x - y).total_seconds() * 1000

    # 注册截止时间 -- 与 1970-1-1 +0000 utc 的差值, 毫秒
    x = datetime.datetime(year + 1, 1, 1)
    y = datetime.datetime(1970, 1, 1) + datetime.timedelta(hours=8)
    time2 = (x - y).total_seconds() * 1000

    return [{"value": int(time1) }, {"value": int(time2) - 1}]

# 4. 请求头部, 可能需要变化, 应该需要在网页登录
headers = {
'Accept': 'application/json, text/plain, */*',
'Accept-Encoding': 'gzip, deflate, br, zstd',
'Accept-Language': 'en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7',
'Cache-Control': 'no-cache',
'Connection': 'keep-alive',
'Content-Length': '2146',
'Content-Type': 'application/json',
'Host': 'capi.tianyancha.com',
'Origin': 'https://www.tianyancha.com',
'Pragma': 'no-cache',
'Referer': 'https://www.tianyancha.com/',
'Sec-Fetch-Dest': 'empty',
'Sec-Fetch-Mode': 'cors',
'Sec-Fetch-Site': 'same-site',
'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/137.0.0.0 Safari/537.36',
'X-AUTH-TOKEN': 'eyJhbGciOiJIUzUxMiJ9.eyJzdWIiOiIxOTEwMTQyODk4NSIsImlhdCI6MTc3OTY3ODkxOSwiZXhwIjoxNzgyMjcwOTE5fQ.IXU4rFo9_f3SflUyZqmEDpiORGm3LwCSuyqC7McQPYVXPO3M5SJJ5adqgwI_ckI9jW0EP5maHd0L9mhTLOOJuA',
'X-TYCID': '7c0c7f60529311f183262d2036a5c75a',
'eventId': 'i244',
'page_id': 'AdvancedSearchPage',
'pm': '263',
'sec-ch-ua': '"Google Chrome";v="137", "Chromium";v="137", "Not/A)Brand";v="24"',
'sec-ch-ua-mobile': '?0',
'sec-ch-ua-platform': '"Windows"',
'spm': 'i244',
'version': 'TYC-Web'
}

# 5. 构造入参
def get_input(it1, it2, it3):
    filterJson = {
        "searchMethod": {
            "key": "searchMethod",
            "items": [
                {
                    "value": "1"
                }
            ]
        },
        "institutionTypeMethod": {
            "key": "institutionTypeMethod",
            "items": [
                {
                    "value": "1"
                }
            ]
        },
        "incomeReportYear": {
            "key": "incomeReportYear",
            "items": [
                {
                    "value": "最新"
                }
            ]
        },
        "incomeReportPeriod": {
            "key": "incomeReportPeriod",
            "items": [
                {
                    "value": "12"
                }
            ]
        },
        "incomeRelation": {
            "key": "incomeRelation",
            "items": [
                {
                    "value": "gt"
                }
            ]
        },
        "economicTypeMethod": {
            "key": "economicTypeMethod",
            "items": [
                {
                    "value": "1"
                }
            ]
        },
        "technologyTypeNewMethod": {
            "key": "technologyTypeNewMethod",
            "items": [
                {
                    "value": "1"
                }
            ]
        },
        "enterTopListMethod": {
            "key": "enterTopListMethod",
            "items": [
                {
                    "value": "1"
                }
            ]
        },
        "certificateTypeMethod": {
            "key": "certificateTypeMethod",
            "items": [
                {
                    "value": "1"
                }
            ]
        },
        "incomeUnit": {
            "key": "incomeUnit",
            "items": [
                {
                    "value": "万"
                }
            ]
        },
        "sortType": {
            "key": "sortType",
            "items": [
                {
                    "value": "0"
                }
            ]
        },
        "profitUnit": {
            "key": "profitUnit",
            "items": [
                {
                    "value": "万"
                }
            ]
        },
        "profitRelation": {
            "key": "profitRelation",
            "items": [
                {
                    "value": "gt"
                }
            ]
        },
        "profitReportYear": {
            "key": "profitReportYear",
            "items": [
                {
                    "value": "最新"
                }
            ]
        },
        "profitReportPeriod": {
            "key": "profitReportPeriod",
            "items": [
                {
                    "value": "12"
                }
            ]
        },
        "assetUnit": {
            "key": "assetUnit",
            "items": [
                {
                    "value": "万"
                }
            ]
        },
        "assetRelation": {
            "key": "assetRelation",
            "items": [
                {
                    "value": "gt"
                }
            ]
        },
        "assetReportYear": {
            "key": "assetReportYear",
            "items": [
                {
                    "value": "最新"
                }
            ]
        },
        "assetReportPeriod": {
            "key": "assetReportPeriod",
            "items": [
                {
                    "value": "12"
                }
            ]
        },
        "liabilityUnit": {
            "key": "liabilityUnit",
            "items": [
                {
                    "value": "万"
                }
            ]
        },
        "liabilityRelation": {
            "key": "liabilityRelation",
            "items": [
                {
                    "value": "gt"
                }
            ]
        },
        "liabilityReportYear": {
            "key": "liabilityReportYear",
            "items": [
                {
                    "value": "最新"
                }
            ]
        },
        "liabilityReportPeriod": {
            "key": "liabilityReportPeriod",
            "items": [
                {
                    "value": "12"
                }
            ]
        },
        "financialDataMethod": {
            "key": "financialDataMethod",
            "items": [
                {
                    "value": "1"
                }
            ]
        },
        # 存续状态
        "regStatus": {
            "key": "regStatus",
            "items": [
                {
                    "value": "正常",
                    "childList": [
                        {
                            "value": "存续/在业"
                        }
                    ]
                }
            ]
        },
        # 注册资本
      #  "regCapital": {
       #     "key": "regCapital",
       #     "items": [
       #         {
       #             "value": "7"
       #         }
       #     ]
       # },
        "companyScale": {
            "key": "companyScale",
            "items": [
                {"value": "大型"},
                {"value": "中型"},
                {"value": "小型"}
            ]
        },
        # 取值 A-T
        "industryCode": {
            "key": "industryCode",
            "items": [ it2["data"] ]
        },
        "areaCode": {
            "key": "areaCode",
            "items": [ it1["data"] ]
        },
        "establishTimeRange": {
            "key": "establishTimeRange",
            "items": get_end_time(it3)
        }
    }
    data = {
        "filterJson": json.dumps(filterJson),
        "searchType": 2,
        "pageNum": 1,
        "pageSize": 20,
        "eventId": "i244"
    }
    return data

url = 'https://capi.tianyancha.com/cloud-tempest/company/advance?_=' + get_time()

all_start_time = time.time()

#print("总数据: ", len(areas) * len(industry))
years = list(range(2010, 2026))

sleep_time_1 = 10 # 查完每条数据休眠的次数
sleep_time_2 = 60 # 查完每省数据休眠的次数
sleep_time_3 = 60 # 查完每年数据休眠的次数

for year in years:
    print("获取数据: ", year)
    file_name = './' + str(year) + '.csv'
    if os.path.exists(file_name):
        print("数据已存在, 跳过")
        continue
    count = 0
    for it1 in areas:
        results = []
        print("获取数据: ", year, it1["name"])
        file_name = './' + str(year) + "-" + it1["name"] + '.csv'
        if os.path.exists(file_name):
            print("数据已存在, 跳过")
            continue
        count += 1
        for it2 in industry:
            response = requests.post(url=url, headers=headers, data=json.dumps(get_input(it1, it2, year))).json()
            #print(response)
            #print(it1)
            #print(it2)
            #exit(0)
            temp = [it1["index"], it1["name"], it2["index"], it2["name"], response["data"]["realTotal"]]
            results.append(temp)
            print(year, temp)
            #print("暂停", sleep_time_1, "秒")
            #time.sleep(sleep_time_1)
        #print("暂停", sleep_time_2, "秒")
        #time.sleep(sleep_time_2)
        print("写入文件", file_name)
        with open(file_name, 'w', encoding='utf-8', newline='') as f:
            writer = csv.writer(f)
            #writer.writerow(["地域", "产业", "数量"])
            writer.writerows(results)
        if count >= 3:
            break
    break
    print("暂停",  sleep_time_3, "秒")
    time.sleep(sleep_time_3)
all_end_time = time.time()
print("总共耗时: %.2f 秒" % (all_end_time - all_start_time))
