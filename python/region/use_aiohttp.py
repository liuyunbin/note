#!/usr/bin/env python3

from lxml import etree
#from requests_html import HTMLSession
import aiohttp
import datetime
import asyncio
import csv
import datetime
import functools
import itertools
import json
import os
import requests
import time

#session = HTMLSession()
#    url_base  = os.path.dirname(url) + "/"
## tr class="villagetr"(多) => td(3) (code=td[1].text(), code_villagetr=td[2].text(), name=td[3].text())
## tr class="towntr"(多)    => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
## tr class="countytr"(多)  => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
## tr class="citytr"(多)    => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
## tr class="provincetr"    => td(多) => a (url=href, name=text())
## div class="list-content" => ul => li(多) => a(3) (url=href, year=text())

def save_csv(file_name, results):
    with open(year + "-" +file_name + ".csv", 'w', encoding='utf-8', newline='') as f:
        writer = csv.writer(f)
        for result in results:
            v = []
            v.append(result["code"])
            v.append(result["name"])
            if "villagetr" in result:
                v.append(result["villagetr"])
            writer.writerow(v)

def access(value):
    if value:
        return value[0].strip()
    return ""

def access_url(value, url_base):
    url = access(value)
    if url != "":
        url = url_base + url
    return url

def handle_years(result, xpaths):
    url_base = "https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/"

    for v in xpaths:
        child = {}
        child["year"] = access(v.xpath("./a[1]/text()"))[:4]
        child["url"]  = url_base + access(v.xpath("./a[1]/@href"))[-15:]
        years.append(child)

def handle_provinces(result, xpaths):
    url_base  = os.path.dirname(result["url"]) + "/"

    for v in xpaths:
        child = {}
        child["name"]     = access(v.xpath("./text()"))
        child["url"]      = access_url(v.xpath("./@href"), url_base)
        provinces.append(child)

def handle_citys(result, xpaths):
    url_base  = os.path.dirname(result["url"]) + "/"

    for v in xpaths:
        child = {}
        child["code"]     = access(v.xpath("./td[1]//text()"))[:4]
        child["name"]     = access(v.xpath("./td[2]//text()"))
        child["url"]      = access_url(v.xpath("./td[1]//@href"), url_base)
        citys.append(child)
        result["code"]     = child["code"][:2]  # 为省份补充代码

def handle_countys(result, xpaths):
    url_base  = os.path.dirname(result["url"]) + "/"

    for v in xpaths:
        child = {}
        child["code"]     = access(v.xpath("./td[1]//text()"))[:6]
        child["name"]     = access(v.xpath("./td[2]//text()"))
        child["url"]      = access_url(v.xpath("./td[1]//@href"), url_base)
        countys.append(child)

def handle_towns(result, xpaths):
    url_base  = os.path.dirname(result["url"]) + "/"

    for v in xpaths:
        child = {}
        child["code"]     = access(v.xpath("./td[1]//text()"))[:9]
        child["name"]     = access(v.xpath("./td[2]//text()"))
        child["url"]      = access_url(v.xpath("./td[1]//@href"), url_base)
        towns.append(child)

def handle_villages(result, xpaths):
    url_base  = os.path.dirname(result["url"]) + "/"

    for v in xpaths:
        child = {}
        child["code"]      = access(v.xpath("./td[1]//text()"))
        child["villagetr"] = access(v.xpath("./td[2]//text()"))
        child["name"]      = access(v.xpath("./td[3]//text()"))
        child["url"]       = access_url(v.xpath("./td[1]//@href"), url_base)
        villages.append(child)

funs = {
    "//div[@class='list-content']//li":handle_years,
    "//tr[@class='provincetr']//a":handle_provinces,
    "//tr[@class='citytr']":handle_citys,
    "//tr[@class='countytr']":handle_countys,
    "//tr[@class='towntr']":handle_towns,
    "//tr[@class='villagetr']":handle_villages
}

async def handle_url(result):
    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36'
    }

    try:
        async with aiohttp.ClientSession() as session:
            async with await session.get(url=result["url"], headers=headers) as response:
                content = await response.read()
                tree    = etree.HTML(content, parser=etree.HTMLParser(encoding=encode))

                for k, v in funs.items():
                    xpaths = tree.xpath(k)
                    if xpaths:
                        v(result, xpaths)
                        return
                count = 3
                print(result["url"])
                print("接口调用成功, 但解析失败, 可能被封, 暂停 %ds" % (count*60))
                await asyncio.sleep(count * 60)
                await handle_url(result)
    except Exception as e:
        count = 1
        print(result["url"])
        print("接口调用失败, 可能被封, 暂停 %ds" % (count*60))
        await asyncio.sleep(count * 60)
        await handle_url(result)

# seconds -- 每次次请求后的休眠时间
def use_aiohttp(results, type_str, seconds = 2):
    count_max = 100 # 每次次请求的最大数量
    if isinstance(results, str):
        results = { "url":results}
    if isinstance(results, dict):
        results = [ results ]
    index = 0
    while index < len(results):
        count = 0
        tasks = []
        while index < len(results) and count < count_max:
            value = results[index]
            if value["url"] != "":
                c = handle_url(value)
                task = asyncio.ensure_future(c)
                tasks.append(task)
                count = count + 1
            index = index + 1
        loop = asyncio.get_event_loop()
        loop.run_until_complete(asyncio.wait(tasks))
        print("处理 %s 年的 %s 数据 总共: %d 已获取: %d 休眠 %ds" % (year, type_str, len(results), index, seconds))
        time.sleep(seconds)

start_time = time.time()

years  = []
year   = datetime.datetime.today().year
encode = "utf-8"
url    = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
use_aiohttp(url, "年") # 获取年数据

for v in years:
    year = v["year"]
    if year <= "2020":
        encode = "gbk"
    else:
        encode = "utf-8"

    print("处理 %s 年的数据中..." %(year))

    provinces = []
    citys     = []
    countys   = []
    towns     = []
    villages  = []

    use_aiohttp(v,         "省") # 获取省数据
    use_aiohttp(provinces, "市") # 获取市数据

    save_csv("provinces", provinces) # 保存省数据
    save_csv("citys",     citys)     # 保存市数据

    use_aiohttp(citys, "区县")   # 获取区县数据
    save_csv("countys", countys) # 保存区县数据

    use_aiohttp(countys, "乡镇", 10) # 获取乡镇数据
    save_csv("towns", towns)     # 保存乡镇数据
    break

    use_aiohttp(towns, "存", 10)    # 获取村数据
    save_csv("villages", villages) # 保存村数据

    print(year, "年的数据处理完成, 暂时休眠 60s")
    time.sleep(60)
    break

end_time = time.time()
print("took: %ds" % (end_time - start_time))

