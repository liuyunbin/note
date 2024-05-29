#!/usr/bin/env python3

from lxml import etree
from requests_html import HTMLSession
import aiohttp
import asyncio
import csv
import datetime
import functools
import itertools
import json
import logging
import os
import requests
import time

session = HTMLSession()
#
#        with open(file_name, 'w', encoding='utf-8') as f:
#            json.dump(result, f, ensure_ascii=False)
#
#def handle_detail(url, encode):
#
#    url_base  = os.path.dirname(url) + "/"
## tr class="villagetr"(多) => td(3) (code=td[1].text(), code_villagetr=td[2].text(), name=td[3].text())
## tr class="towntr"(多)    => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
## tr class="countytr"(多)  => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
## tr class="citytr"(多)    => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
## tr class="provincetr"    => td(多) => a (url=href, name=text())
## div class="list-content" => ul => li(多) => a(3) (url=href, year=text())

#def del_key(result):
#    if result:
#        for v in result:
#            keys = ["url", "encode", "xpath", "xpaths", "callback"]
#            for i in keys:
#                if i in v:
#                    del v[i]
#            if "children" in v:
#                del_key(v["children"])

#provinces = []
#for v in years:
#    year = access(v.xpath("./a[1]/text()"))[:4]
#    url  = access(v.xpath("./a[1]/@href"))
#        if year <= "2020":
#            encode = "gbk"
#        else:
#            encode = "utf-8"
#        if (not url.startswith("http")):
#            url = url_base + url
#        result = handle_detail(url, encode)
#        if until_county:
#            file_name = year + "-county.json"
#        else:
#            file_name = year + "-all.json"
#        with open(file_name, 'w', encoding='utf-8') as f:
#            json.dump(result, f, ensure_ascii=False)
#        break
#
## 写入数据
##with open('./2010(1).csv', 'w', encoding='utf-8', newline='') as f:
##    writer = csv.writer(f)
##    writer.writerow(["省份", "产业", "注册资本", "数量"])
##    writer.writerows(results)

def access(value):
    if value:
        return value[0].strip()
    return ""

def access_url(value, url_base):
    url = access(value)
    if url != "":
        url = url_base + url
    return url

def handle_base(result, callback, xpaths):
    url      = result["url"]
    encode   = result["encode"]
    children = result["children"] = []

    url_base  = os.path.dirname(url) + "/"

    for v in xpaths:
        child = {}
        child["encode"] = encode
        callback(child, v, url_base)
        children.append(child)

def handle_years(child, v, url_base):
    url_base = "https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/"

    child["year"] = access(v.xpath("./a[1]/text()"))[:4]
    child["url"]  = url_base + access(v.xpath("./a[1]/@href"))[-15:]
    if child["year"] <= "2020":
        child["encode"] = "gbk"

def handle_provinces(child, v, url_base):
    child["name"]     = access(v.xpath("./text()"))
    child["url"]      = access_url(v.xpath("./@href"), url_base)

def handle_citys(child, v, url_base):
    child["code"]     = access(v.xpath("./td[1]//text()"))[:4]
    child["name"]     = access(v.xpath("./td[2]//text()"))
    child["url"]      = access_url(v.xpath("./td[1]//@href"), url_base)

def handle_countys(child, v, url_base):
    child["code"]     = access(v.xpath("./td[1]//text()"))[:6]
    child["name"]     = access(v.xpath("./td[2]//text()"))
    child["url"]      = access_url(v.xpath("./td[1]//@href"), url_base)

def handle_towns(child, v, url_base):
    child["code"]     = access(v.xpath("./td[1]//text()"))[:9]
    child["name"]     = access(v.xpath("./td[2]//text()"))
    child["url"]      = access_url(v.xpath("./td[1]//@href"), url_base)

def handle_villages(child, v, url_base):
    child["code"]      = access(v.xpath("./td[1]//text()"))
    child["villagetr"] = access(v.xpath("./td[2]//text()"))
    child["name"]      = access(v.xpath("./td[3]//text()"))
    child["url"]       = access_url(v.xpath("./td[1]//@href"), url_base)

async def handle_url(result):
    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36'
    }

    try:
        async with aiohttp.ClientSession() as session:
            async with await session.get(url=result["url"], headers=headers) as response:
                content           = await response.read()
                tree              = etree.HTML(content, parser=etree.HTMLParser(encoding=result["encode"]))

                year     = tree.xpath("//div[@class='list-content']//li")
                province = tree.xpath("//tr[@class='provincetr']//a")
                city     = tree.xpath("//tr[@class='citytr']")
                county   = tree.xpath("//tr[@class='countytr']")
                town     = tree.xpath("//tr[@class='towntr']")
                village  = tree.xpath("//tr[@class='villagetr']")

                if year: # 年数据
                    handle_base(result, handle_years, year)
                elif province: # 省数据
                    handle_base(result, handle_provinces, province)
                elif city:
                    # 市数据
                    handle_base(result, handle_citys, city)
                elif county:
                    # 区县数据
                    handle_base(result, handle_countys, county)
                elif town:
                    # 乡镇数据
                    handle_base(result, handle_towns, town)
                elif village:
                    # 村数据
                    handle_base(result, handle_villages, village)
                else:
                    raise NameError("可能被封")
    except Exception as e:
        print("%s failed, sleep %d seconds" % (result["url"], 5 * 60))
        print(e)
        time.sleep(5 * 60)
        return await handle_url(result)

def use_aiohttp(results):
    count_max = 10 # 一次请求的最大数量
    index = 0

    while index < len(results):
        count = 0
        tasks = []
        while index < len(results) and count < count_max:
            value = results[index]
            if value["url"] != "":
                value["children"] = []
                c = handle_url(value)
                task = asyncio.ensure_future(c)
                tasks.append(task)
                count = count + 1
            index = index + 1
        loop = asyncio.get_event_loop()
        loop.run_until_complete(asyncio.wait(tasks))
        print("获取数据中...总共: %d, 已获取: %d" % (len(results), index))
#        if index < len(results):
#        time.sleep(10)

    details = []
    for result in results:
        if "children" in result:
            for detail in result["children"]:
                details.append(detail)
                if "code" in detail and len(detail["code"]) == 4:
                    result["code"] = detail["code"][:2] # 为省份补充代码
    return details

start_time = time.time()
# 年数据
years            = []
year             = {}
year["url"]      = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
year["encode"]   = "utf-8"
years.append(year)

print("获取年数据...")
years = use_aiohttp(years)
#years = years[0]["children"]
print("总共 %d 条数据" % (len(years)))

for v in years:
    # 省数据
    year = [ v ]

    print("获取省数据...")
    use_aiohttp(year)
    provinces = year[0]["children"]
    print("总共 %d 条数据" % (len(provinces)))

    # 市数据
    print("获取市数据...")
    citys = use_aiohttp(provinces)
    print("总共 %d 条数据" % (len(citys)))

#    for v in provinces:
#        print(v["code"], v["name"])
#print(citys)
    # 区县数据
    print("获取区县数据...")
    countys = use_aiohttp(citys)
    print("总共 %d 条数据" % (len(countys)))

    # 乡镇数据
    print("获取乡镇数据...")
    towns = use_aiohttp(countys)
    print("总共 %d 条数据" % (len(towns)))
    break

end_time = time.time()
print("took: %ds" % (end_time - start_time))

