#!/usr/bin/env python3

import requests
import json
import os
import time
from lxml import etree

def save_file(name, results):
    with open(name + ".json", 'w', encoding='utf-8') as f:
        json.dump(results, f, ensure_ascii=False)

# url_base = "https://www.stats.gov.cn"
def access(value):
    if value:
        return value[0].strip()
    return ""

def access_url(value, url_base):
    url = access(value)
    if url != "":
        url = url_base + url
    return url

def handle_url(url, encode):
    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36'
    }

    try:
        print("handle", url)
        response = requests.get(url=url, headers=headers)
        tree     = etree.HTML(response.content, parser=etree.HTMLParser(encoding=encode))
        return tree
    except Exception as e:
        print("调用报错, 可能临时被封, 强行暂停 10 秒, 然后重新请求")
        time.sleep(10)
        return get_url(url, encode)

# https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/07/28/140728202.html -- 村数据
# 结构: tr class="villagetr"(多) => td(3) (code=td[1].text(), code_villagetr=td[2].text(), name=td[3].text())
def handle_villagetrs(url, encode, results):
    if url == "":
        return
    results["children"] = []
    results  = results["children"]
    tree       = handle_url(url, encode)
    villagetrs = tree.xpath("//tr[@class='villagetr']")
    url_base   = os.path.dirname(url) + "/"
    for v in villagetrs:
        villagetr                   = {}
        villagetr["code"]           = access(v.xpath("./td[1]//text()"))
        villagetr["code_villagetr"] = access(v.xpath("./td[2]//text()"))
        villagetr["name"]           = access(v.xpath("./td[3]//text()"))
        results.append(villagetr)
#print(handle_villagetrs("https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/07/28/140728202.html", "utf-8"))

# https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/07/140728.html -------- 乡镇数据
# 结构: tr class="towntr"(多) => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# 返回: 28/140728202.html
def handle_towns(url, encode, results):
    if url == "" or True:
        return
    results["children"] = []
    results  = results["children"]
    tree     = handle_url(url, encode)
    towns    = tree.xpath("//tr[@class='towntr']")
    url_base = os.path.dirname(url) + "/"
    for v in towns:
        town = {}
        town["code"] = access(v.xpath("./td[1]//text()"))
        town["name"] = access(v.xpath("./td[2]//text()"))
        url  = access_url(v.xpath("./td[1]/a/@href"), url_base)
        handle_villagetrs(url, encode, town)
        results.append(town)
#print(handle_towns("https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/07/140728.html", "utf-8"))

# https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/1407.html ------------- 县区数据
# 结构: tr class="countytr"(多) => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# 返回: 07/140728.html
def handle_countys(url, encode, results):
    if url == "":
        return
    results["children"] = []
    results  = results["children"]
    tree     = handle_url(url, encode)
    countys  = tree.xpath("//tr[@class='countytr']")
    url_base = os.path.dirname(url) + "/"
    for v in countys:
        county         = {}
        county["code"] = access(v.xpath("./td[1]//text()"))
        county["name"] = access(v.xpath("./td[2]//text()"))
        url  = access_url(v.xpath("./td[1]/a/@href"), url_base)
        handle_towns(url, encode, county)
        results.append(county)
#print(handle_countys("https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/1407.html", "utf-8"))

# https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14.html ------------------ 市数据
# 结构: tr class="citytr"(多) => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# 返回: 14/1407.html
def handle_citys(url, encode, results):
    if url == "":
        return
    results["children"] = []
    results  = results["children"]
    tree     = handle_url(url, encode)
    citys    = tree.xpath("//tr[@class='citytr']")
    url_base = os.path.dirname(url) + "/"
    for v in citys:
        city         = {}
        city["code"] = access(v.xpath("./td[1]/a/text()"))
        city["name"] = access(v.xpath("./td[2]/a/text()"))
        url  = access_url(v.xpath("./td[1]/a/@href"), url_base)
        handle_countys(url, encode, city)
        results.append(city)
#print(handle_citys("https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14.html", "utf-8"))

# https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/index.html --------------- 省数据
# 结构: tr class="provincetr" => td(多) => a (url=href, name=text())
# 返回: 14.html
def handle_provinces(url, encode, results):
    tree      = handle_url(url, encode)
    provinces = tree.xpath("//tr[@class='provincetr']//a")
    url_base  = os.path.dirname(url) + "/"
    for v in provinces:
        province         = {}
        province["name"] = access(v.xpath("./text()"))
        url  = access_url(v.xpath("./@href"), url_base)
        handle_citys(url, encode, province)
        results.append(province)
#print(handle_provinces("https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/index.html", "utf-8"))

# https://www.stats.gov.cn/sj/tjbz/qhdm/ ---------------------------------------- 年份数据
# 返回 http://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/index.html 或 /sj/tjbz/tjyqhdmhcxhfdm/2022/index.html
# 结构: div class="list-content" => ul => li(多) => a(3) (url=href, year=text())
def handle_years(url, encode):
    tree     = handle_url(url, encode)
    years    = tree.xpath("//div[@class='list-content']//li")
    url_base = "https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/"
    for v in years:
        year = access(v.xpath("./a[1]/text()"))[:4]
        url  = url_base + access(v.xpath("./a[1]/@href"))[-15:]
        encode = "utf-8"
        if year <= "2020":
            encode = "gbk"
        results = []
        handle_provinces(url, encode, results)
        save_file(year, results)

start_time = time.time()
handle_years("https://www.stats.gov.cn/sj/tjbz/qhdm/", "utf-8")
end_time = time.time()
print("总共耗时: %d 秒" % (end_time - start_time))

