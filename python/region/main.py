#!/usr/bin/env python3

from lxml import etree
from requests_html import HTMLSession
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
import logging

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(message)s',
                    datefmt="%Y-%m-%d %H:%M:%S %z"
                    )
count_cur = 0
count_all = 0
#        async with aiohttp.ClientSession() as session:
#            async with await session.get(url=result["url"], headers=headers) as response:
#                content = await response.read()
#                tree    = etree.HTML(content, parser=etree.HTMLParser(encoding=encode))
#
#def use_aiohttp(results, type_str, seconds = 1):
#    count_max = 35 # 每次次请求的最大数量
#    if isinstance(results, str):
#        results = { "url":results}
#    if isinstance(results, dict):
#        results = [ results ]
#    index = 0
#    while index < len(results):
#        count = 0
#        tasks = []
#        while index < len(results) and count < count_max:
#            value = results[index]
#            if value["url"] != "":
#                c = handle_url(value)
#                task = asyncio.ensure_future(c)
#                tasks.append(task)
#                count = count + 1
#            index = index + 1
#        loop = asyncio.get_event_loop()
#        loop.run_until_complete(asyncio.wait(tasks))
#        logging.info("处理 %s 年的 %s 数据 总共: %d 已获取: %d 休眠 %ds" % (year, type_str, len(results), index, seconds))
#        time.sleep(seconds)
#
session = HTMLSession()

def access(value):
    if value:
        return value[0].strip()
    return ""

def access_url(urls):
    if len(urls) > 0:
        return urls.pop()
    return ""

# div class="list-content" => ul => li(多) => a(3) (url=href, year=text())
def handle_years(v):
    for x in v.find("a"):
        year        = x.text[:4]
        url         = access_url(x.absolute_links)
        years[year] = url

# tr class="provincetr" => td(多) => a (url=href, name=text())
def handle_provinces(v):
    for x in v.find("a"):
        name = x.text
        url  = access_url(x.absolute_links)
        provinces.append({"name":name, "url":url})

# tr class="citytr" => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
def handle_citys(v):
    tds  = v.find("td")
    code = tds[0].text[:4]
    url  = access_url(tds[0].absolute_links)
    name = tds[1].text
    citys.append({"name":name, "url":url, "code":code})

# tr class="countytr" => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
def handle_countys(v):
    tds  = v.find("td")
    code = tds[0].text[:6]
    url  = access_url(tds[0].absolute_links)
    name = tds[1].text
    countys.append({"name":name, "url":url, "code":code})

# tr class="towntr" => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
def handle_towns(v):
    tds  = v.find("td")
    code = tds[0].text[:9]
    url  = access_url(tds[0].absolute_links)
    name = tds[1].text
    towns.append({"name":name, "url":url, "code":code})

# tr class="villagetr" => td(3) (code=td[1].text(), code_villagetr=td[2].text(), name=td[3].text())
def handle_villages(v):
    tds     = v.find("td")
    code    = tds[0].text
    village = tds[1].text
    name    = tds[2].text
    villages.append({"name":name, "village":village, "code":code})

funs = {
    ".list-content": handle_years,
    ".provincetr": handle_provinces,
    ".citytr": handle_citys,
    ".countytr": handle_countys,
    ".towntr": handle_towns,
    ".villagetr": handle_villages
}

def handle_urls(url):
    global count_cur
    global count_all
    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36'
    }
    if isinstance(url, list):
        for v in url:
            handle_urls(v["url"])
        return
    if url == "":
        count_cur = count_cur + 1
        if count_cur % 100 == 0:
            logging.info("总共: %d , 已处理: %d", count_all, count_cur)
        return

    try:
        reponse = session.get(url=url, headers=headers)

        for k, f in funs.items():
            res = reponse.html.find(k)
            if len(res) == 0:
                continue
            for v in res:
                f(v)
            count_cur = count_cur + 1
            if count_cur % 100 == 0:
                logging.info("总共: %d , 已处理: %d", count_all, count_cur)
            return
            logging.info("%s 接口调用成功, 但解析失败, 可能被封, 暂停 %ds", url, 60)
            time.sleep(60)
            handle_urls(url)
    except Exception as e:
        logging.info("%s 接口调用失败, 可能被封, 暂停 %ds", url, 60)
        logging.info(e)
        time.sleep(60)
        handle_urls(url)

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

def handle_help(results, prompt):

    logging.info("获取...")




start_time = time.time()

# 获取年数据
logging.info("获取年数据...")
url   = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
years = {}
handle_urls(url)
logging.info("总共: %d", len(years))

for year, url in years.items():
    provinces = []
    citys     = []
    countys   = []
    towns     = []
    villages  = []

    logging.info("获取省数据...")
    count_cur = 0
    count_all = 1
    handle_urls(url)
    logging.info("总共: %d", len(provinces))

    logging.info("获取市数据...")
    count_cur = 0
    count_all = len(provinces)
    for province in provinces:
        handle_urls(province["url"])
        province["code"] = citys[-1]["code"][:2]
    logging.info("总共: %d", len(citys))
    save_csv("provinces", provinces) # 保存省数据
    save_csv("citys",     citys)     # 保存市数据

    logging.info("获取区县数据...")
    count_cur = 0
    count_all = len(citys)
    handle_urls(citys)
    logging.info("总共: %d", len(countys))
    save_csv("countys", countys) # 保存区县数据

    continue
    logging.info("获取乡镇数据...")
    count_cur = 0
    count_all = len(countys)
    handle_urls(countys)
    logging.info("总共: %d", len(towns))
    save_csv("towns", towns) # 保存区县数据

    logging.info("获取村数据...")
    count_cur = 0
    count_all = len(towns)
    handle_urls(towns)
    logging.info("总共: %d", len(villages))
    save_csv("villages", villages) # 保存区县数据
    break

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

