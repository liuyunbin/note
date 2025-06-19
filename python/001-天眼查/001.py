import aiohttp
import asyncio
import json
import time
import datetime
import itertools
import csv

url = 'https://capi.tianyancha.com/cloud-tempest/advance'

headers = {
    'authority': 'capi.tianyancha.com',
    'method': 'POST',
    'path': '/cloud-tempest/advance',
    'scheme': 'https',
    'accept': '*/*',
    'accept-encoding': 'gzip, deflate, br',
    'accept-language': 'zh-CN,zh;q=0.9',
    #'content-length': '452',
    'content-type': 'application/json; charset=UTF-8',
    'origin': '//www.tianyancha.com',
    'referer': '//www.tianyancha.com/',
    'sec-ch-ua': '" Not A;Brand";v="99", "Chromium";v="96", "Google Chrome";v="96"',
    'sec-ch-ua-mobile': '?0',
    'sec-ch-ua-platform': '"Windows"',
    'sec-fetch-dest': 'empty',
    'sec-fetch-mode': 'cors',
    'sec-fetch-site': 'same-site',
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36',
    'version': 'TYC-Web',
    'x-tycid': '61b44820f8eb11eb90c25beeeaa71b03',
    'set-cookie': 'aliyungf_tc=c9465432f93e39f1192a2037eee53e2b25a63d1f9ec4ad41dd343e4f42b07255; Path=/; HttpOnly',
    'Set-Cookie': 'CLOUDID=431a6a37-e037-49dc-b0b4-e90d0356df6f; Expires=Sat, 10-Jun-2023 11:39:38 GMT; Path=/; HttpOnly'
}

# 用于存储最终所有的结果
results = []

async def get_data(data):
    try:
        async with aiohttp.ClientSession() as session:
            async with await session.post(url=url, headers=headers, data=json.dumps(data)) as response:
                json_data = await response.json()
                result = json_data['data']['realTotal']
                area_code = data['customAreaCodeSet']
                cate_code = data['categoryGuobiao2017Set']
                capital = data['regCapitalRangeSet']

                # 将网站的返回暂时存入变量 results
                temp = [area_code, cate_code, capital, result]
                results.append(temp)
                #print("网站返回: ", json_data)
                #print("存入数据: ", temp)

                # 将 成功获取的数据从 areas_cates 中删除
                areas_cates.remove([area_code,cate_code])
    except Exception as e:
        # 忽略所有异常
        pass

# 注册开始时间 -- 与 1970-1-1 +0000 utc 的差值, 毫秒
x = datetime.datetime(1953, 1, 1)
y = datetime.datetime(1970, 1, 1) + datetime.timedelta(hours=8)
time1 = (x - y).total_seconds() * 1000

# 注册截止时间 -- 与 1970-1-1 +0000 utc 的差值, 毫秒
x = datetime.datetime.now()
y = datetime.datetime(1970, 1, 1) + datetime.timedelta(hours=8)
time2 = (x - y).total_seconds() * 1000

# 省份国标代码
areas = [['00110000V2024'], ['00120000V2024'], ['00130000V2024'], ['00140000V2024'],
         ['00150000V2024'], ['00210000V2024'], ['00220000V2024'], ['00230000V2024'],
         ['00310000V2024'], ['00320000V2024'], ['00330000V2024'], ['00340000V2024'],
         ['00350000V2024'], ['00360000V2024'], ['00370000V2024'], ['00410000V2024'],
         ['00420000V2024'], ['00430000V2024'], ['00440000V2024'], ['00450000V2024'],
         ['00460000V2024'], ['00500000V2024'], ['00510000V2024'], ['00520000V2024'],
         ['00530000V2024'], ['00540000V2024'], ['00610000V2024'], ['00620000V2024'],
         ['00630000V2024'], ['00640000V2024'], ['00650000V2024'], ['00810000V2024'],
         ['00820000V2024'], ['00710000V2024']]

# 二级行业代码
cates = [['01'], ['02'], ['03'], ['04'], ['05'], ['06'], ['07'], ['08'], ['09'], ['10'],
         ['11'], ['12'], ['13'], ['14'], ['15'], ['16'], ['17'], ['18'], ['19'], ['20'],
         ['21'], ['22'], ['23'], ['24'], ['25'], ['26'], ['27'], ['28'], ['29'], ['30'],
         ['31'], ['32'], ['33'], ['34'], ['35'], ['36'], ['37'], ['38'], ['39'], ['40'],
         ['41'], ['42'], ['43'], ['44'], ['45'], ['46'], ['47'], ['48'], ['49'], ['50'],
         ['51'], ['52'], ['53'], ['54'], ['55'], ['56'], ['57'], ['58'], ['59'], ['60'],
         ['61'], ['62'], ['63'], ['64'], ['65'], ['66'], ['67'], ['68'], ['69'], ['70'],
         ['71'], ['72'], ['73'], ['74'], ['75'], ['76'], ['77'], ['78'], ['79'], ['80'],
         ['81'], ['82'], ['83'], ['84'], ['85'], ['86'], ['87'], ['88'], ['89'], ['90'],
         ['91'], ['92'], ['93'], ['94'], ['95'], ['96'], ['97']]

#areas = [['00110000V2020']]
#cates = [['01']]

def main() :
    tasks = []
    for v in areas_cates:
        area = v[0]
        cate = v[1]
        data = {
            # 输入注册资本
            "regCapitalRangeSet": [
                5000,
                -1
            ],
            # 行业代码
            'categoryGuobiao2017Set': cate,
            # 省份代码
            'customAreaCodeSet': area,
            # 注册时间
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
        c = get_data(data)
        task = asyncio.ensure_future(c)
        tasks.append(task)
    loop = asyncio.get_event_loop()
    loop.run_until_complete(asyncio.wait(tasks))

all_start_time = time.time()

# 将所有的组合存入变量 areas_cates 中
areas_cates = []
for area, cate in itertools.product(areas, cates):
    areas_cates.append([area, cate])

while len(areas_cates) > 0:
    print("获取数据中...", end=" ")
    start_time = time.time()
    # 所有的数据
    all_counts = len(areas) * len(cates)
    # 还未获取的数据
    current_counts = len(areas_cates)
    # 获取数据
    main()

    end_time = time.time()

    print("总共数据: %6d, 已成功获取: %6d, 此次获取: %6d, 剩余数据: %6d, 此次耗时: %.2f 秒" % (
          all_counts,
          all_counts - len(areas_cates),
          current_counts - len(areas_cates),
          len(areas_cates),
          end_time - start_time))

    if current_counts == len(areas_cates):
        print("此轮成功查询数据为 0, 可能临时被封, 强行停止 一分钟")
        time.sleep(60)

# 写入数据
with open('./2010(1).csv', 'w', encoding='utf-8', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(["省份", "产业", "注册资本", "数量"])
    writer.writerows(results)

all_end_time = time.time()

print("总共耗时: %.2f 秒" % (all_end_time - all_start_time))