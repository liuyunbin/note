#!/usr/bin/env python3

from requests_html import HTMLSession
from requests_html import AsyncHTMLSession
import csv
import datetime
import logging
import time
import asyncio
import os

until_county = False # 只查到区县

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


async def handle_year(response):
    global count_all
    global count_failed
    global count_failed_all
    global count_success
    global count_success_all
    global urls
    global next_urls
    global count_current
    res_year     = response.html.find(".list-content a")
    for v in res_year:
        year        = v.text[:4]
        url         = access_url(v.absolute_links)
        years[year] = url

async def handle_province(response):
    global count_all
    global count_failed
    global count_failed_all
    global count_success
    global count_success_all
    global urls
    global next_urls
    global count_current
    res_province = response.html.find(".provincetr a")
    for v in res_province:
        url  = access_url(v.absolute_links)
        code = await handle_url(url)
        name = v.text
        add_result(code, name, 1)

async def handle_city(response):
    global count_all
    global count_failed
    global count_failed_all
    global count_success
    global count_success_all
    global urls
    global next_urls
    global count_current
    res_city = response.html.find(".citytr")
    for v in res_city:
        tds   = v.find("td")
        url   = access_url(tds[0].absolute_links)
        code  = tds[0].text
        name  = tds[1].text
        pcode = code[:2] + "0000000000"
        add_result(code, name, 2, pcode)
        next_urls.append(url)
    return pcode

async def handle_county(response):
    global count_all
    global count_failed
    global count_failed_all
    global count_success
    global count_success_all
    global urls
    global next_urls
    global count_current
    res_county   = response.html.find(".countytr")
    for v in res_county:
        tds   = v.find("td")
        url   = access_url(tds[0].absolute_links)
        code  = tds[0].text
        name  = tds[1].text
        pcode = code[:4] + "00000000"
        add_result(code, name, 3, pcode)
        if until_county == False:
            next_urls.append(url)

async def handle_town(response):
    global count_all
    global count_failed
    global count_failed_all
    global count_success
    global count_success_all
    global urls
    global next_urls
    global count_current
    if until_county:
        return
    res_town     = response.html.find(".towntr")
    for v in res_town:
        tds   = v.find("td")
        url   = access_url(tds[0].absolute_links)
        code  = tds[0].text
        name  = tds[1].text
        pcode = code[:6] + "000000"
        add_result(code, name, 4, pcode)
        next_urls.append(url)

async def handle_village(response):
    global count_all
    global count_failed
    global count_failed_all
    global count_success
    global count_success_all
    global urls
    global next_urls
    global count_current
    if until_county:
        return
    res_village  = response.html.find(".villagetr")
    for v in res_village:
        tds      = v.find("td")
        code     = tds[0].text
        category = tds[1].text
        name     = tds[2].text
        pcode = code[:9] + "000"
        add_result(code, name, 5, pcode, category)

# div class="list-content" => ul => li(多) => a(3) (url=href, year=text())
# tr  class="provincetr"   => td(多) => a (url=href, name=text())
# tr  class="citytr"       => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="countytr"     => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="towntr"       => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="villagetr"    => td(3) (code=td[1].text(), code_villagetr=td[2].text(), name=td[3].text())
async def handle_url(url):
    global count_all
    global count_failed
    global count_failed_all
    global count_success
    global count_success_all
    global urls
    global next_urls
    global count_current

    if url == "":
        return

    logging.info("handle %s", url)

    try:
        response = await asession.get(url=url)

        func = {
            ".wrapper-list-title": handle_year,
            ".provincehead": handle_province,
            ".cityhead": handle_city,
            ".countyhead": handle_county,
            ".townhead": handle_town,
            ".villagehead": handle_village
        }
        for k, f in func.items():
            if len(response.html.find(k)) > 0:
                count_success_all = count_success_all + 1
                count_success = count_success + 1
                return await f(response)

        count_failed = count_failed + 1
        count_failed_all = count_failed_all + 1
        logging.info("%s 接口调用成功, 但解析失败, 可能被封, 暂停 %ds", url, 10*60)
        logging.info(f"总任务: {count_all} 总成功: {count_success_all} 总失败: {count_failed_all} 当前获取: {count_current} 当前成功: {count_success} 当前失败: {count_failed}")
        await asyncio.sleep(10 * 60)
        return await handle_url(url)
    except Exception as e:
        count_failed = count_failed + 1
        count_failed_all = count_failed_all + 1
        logging.info(e)
        logging.info("%s 接口调用失败, 可能被封, 暂停 %ds", url, 60)
        logging.info(f"总任务: {count_all} 总成功: {count_success_all} 总失败: {count_failed_all} 当前获取: {count_current} 当前成功: {count_success} 当前失败: {count_failed}")
        await asyncio.sleep(60)
        return await handle_url(url)

def get_code(item):
    return item["code"]

def use_async():
    global count_all
    global count_failed
    global count_failed_all
    global count_success
    global count_success_all
    global urls
    global next_urls
    global count_current

    count_all = len(urls)
    count_failed_all = 0
    count_success_all = 0

    count_index = 0
    count_current = 50

    while count_index < len(urls):
        if count_index + count_current > len(urls):
            count_current = len(urls) - count_index

        count_failed = 0
        count_success = 0
        tasks = []
        for i in range(count_index, count_index + count_current):
            tasks.append( lambda url=urls[i]: handle_url(url))
        asession.run(*tasks)
        logging.info(f"总任务: {count_all} 总成功: {count_success_all} 总失败: {count_failed_all} 当前获取: {count_current} 当前成功: {count_success} 当前失败: {count_failed}")
        logging.info("暂停 %ds", 10)
        time.sleep(5)
        count_index = count_index + count_current

start_time = time.time()

years     = {}

# 获取年数据
url  = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
urls = [ url ]
next_urls = []
use_async()

count_all         = 0
count_failed      = 0
count_failed_all  = 0
count_success     = 0
count_success_all = 0
count_current  = 0
for year, url in years.items():
    logging.info(f"获取 {year} 的数据...")

    if until_county:
        file_name = year + "-tjj.csv"
    else:
        file_name = year + "-tjj-all.csv"
#    file_name = "test.csv"

    if os.path.exists(file_name):
        logging.info(f"{year} 的数据已存在, 跳过")
        continue

    results = []

    urls = [ url ]
    next_urls = []
    use_async() # 省市数据

    urls = next_urls
    next_urls = []
    use_async() # 区县数据

    urls = next_urls
    next_urls = []
    use_async() # 乡镇数据

    urls = next_urls
    next_urls = []
    use_async() # 村数据

    results.sort(key=get_code)

    logging.info(f"存储 {year} 的数据...")
    with open(file_name, 'w', encoding='utf-8', newline='') as f:
        writer = csv.writer(f)
        for result in results:
            code     = result["code"]
            name     = result["name"]
            level    = result["level"]
            pcode    = result["pcode"]
            category = result["category"]

            if until_county:
                code  = code[:6]
                pcode = pcode[:6]
            writer.writerow([code, name, level, pcode, category])

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

