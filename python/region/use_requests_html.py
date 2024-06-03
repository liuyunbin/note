#!/usr/bin/env python3

from lxml import etree
from requests_html import HTMLSession
from requests_html import AsyncHTMLSession
from enum import Enum
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

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s', datefmt="%Y-%m-%d %H:%M:%S %z")
session = HTMLSession()
asession = AsyncHTMLSession()

def access(value):
    if value:
        return value[0].strip()
    return ""

def access_url(urls):
    if len(urls) > 0:
        return urls.pop()
    return ""

def add_result(code, name, level, pcode = "0", category = "0"):
    results.append({
            "code":code,
            "name":name,
            "level":level,
            "pcode":pcode,
            "category":category
            })

# div class="list-content" => ul => li(多) => a(3) (url=href, year=text())
# tr  class="provincetr"   => td(多) => a (url=href, name=text())
# tr  class="citytr"       => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="countytr"     => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="towntr"       => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="villagetr"    => td(3) (code=td[1].text(), code_villagetr=td[2].text(), name=td[3].text())
async def handle_url_async(url):
    if url == "":
        return

    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36'
    }

    logging.info("handle %s", url)

    try:
        reponse = session.get(url=url, headers=headers)

        res_year     = reponse.html.find(".list-content a")
        res_province = reponse.html.find(".provincetr a")
        res_city     = reponse.html.find(".citytr")
        res_county   = reponse.html.find(".countytr")
        res_town     = reponse.html.find(".towntr")
        res_village  = reponse.html.find(".villagetr")

        if len(res_year) > 0:
            for v in res_year:
                year        = v.text[:4]
                url         = access_url(v.absolute_links)
                years[year] = url
            return
        if len(res_province) > 0:
            for v in res_province:
                url  = access_url(v.absolute_links)
                code = await handle_url_async(url)
                name = v.text
                add_result(code, name, 1)
            return
        if len(res_city) > 0:
            for v in res_city:
                tds   = v.find("td")
                url   = access_url(tds[0].absolute_links)
                code  = tds[0].text
                name  = tds[1].text
                pcode = code[:2] + "0000000000"
                add_result(code, name, 2, pcode)
                next_urls.append(url)
            return pcode
        if len(res_county) > 0:
            for v in res_county:
                tds   = v.find("td")
                url   = access_url(tds[0].absolute_links)
                code  = tds[0].text
                name  = tds[1].text
                pcode = code[:4] + "00000000"
                add_result(code, name, 3, pcode)
                next_urls.append(url)
            return pcode
        if len(res_town) > 0:
            for v in res_town:
                tds   = v.find("td")
                url   = access_url(tds[0].absolute_links)
                code  = tds[0].text
                name  = tds[1].text
                pcode = code[:6] + "000000"
                add_result(code, name, 4, pcode)
                next_urls.append(url)
            return pcode
        if len(res_village) > 0:
            for v in res_village:
                tds      = v.find("td")
                code     = tds[0].text
                category = tds[1].text
                name     = tds[2].text
                pcode = code[:9] + "000"
                add_result(code, name, 5, pcode, category)
            return pcode
        logging.info("%s 接口调用成功, 但解析失败, 可能被封, 暂停 %ds", url, 60)
        time.sleep(60)
        await handle_url_async(url)
    except Exception as e:
        logging.info(e)
        logging.info("%s 接口调用失败, 可能被封, 暂停 %ds", url, 60)
        time.sleep(60)
        await handle_url_async(url)

def get_code(item):
    return item["code"]

start_time = time.time()

years     = {}

# 获取年数据
url  = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
task = lambda url=url: handle_url_async(url)
asession.run(task)

for year, url in years.items():
    next_urls = [ url ]

    results = []
    count  = 0
    while len(next_urls) != 0:
        count = count + 1
        logging.info(f"第 {count} 次, 长度为: {len(next_urls)}")
        tasks = []
        for url in next_urls:
            tasks.append( lambda url=url: handle_url_async(url))
        next_urls = []
        asession.run(*tasks)

    results.sort(key=get_code)
    with open(year + ".csv", 'w', encoding='utf-8', newline='') as f:
        writer = csv.writer(f)
        for result in results:
            writer.writerow([result["code"], result["name"], result["level"], result["pcode"], result["category"]])
    break

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

