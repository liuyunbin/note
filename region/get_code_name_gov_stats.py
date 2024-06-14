#!/usr/bin/env python3

from requests_html import HTMLSession
import csv
import datetime
import logging
import time
import os
import sys

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


def handle_year(res_year):
    for v in res_year:
        year        = v.text[:4]
        url         = access_url(v.absolute_links)
        years[year] = url

def handle_province(res_province):
    for v in res_province:
        url  = access_url(v.absolute_links)
        code = handle_url(url)
        name = v.text
        add_result(code, name, 1)

def handle_city(res_city):
    for v in res_city:
        tds   = v.find("td")
        url   = access_url(tds[0].absolute_links)
        code  = tds[0].text
        name  = tds[1].text
        pcode = code[:2] + "0000000000"
        add_result(code, name, 2, pcode)
        handle_url(url)
    return pcode

def handle_county(res_county):
    for v in res_county:
        tds   = v.find("td")
        url   = access_url(tds[0].absolute_links)
        code  = tds[0].text
        name  = tds[1].text
        pcode = code[:4] + "00000000"
        add_result(code, name, 3, pcode)
        if all_data:
            handle_url(url)

def handle_town(res_town):
    if not all_data:
        return
    for v in res_town:
        tds   = v.find("td")
        url   = access_url(tds[0].absolute_links)
        code  = tds[0].text
        name  = tds[1].text
        pcode = code[:6] + "000000"
        add_result(code, name, 4, pcode)
        handle_url(url)

def handle_village(res_village):
    if not all_data:
        return
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
def handle_url(url):

    if url == "":
        return

    logging.info("handle %s", url)

    try:
        response = session.get(url=url)

        res_year     = response.html.find(".list-content a")
        res_province = response.html.find(".provincetr a")
        res_city     = response.html.find(".citytr")
        res_county   = response.html.find(".countytr")
        res_town     = response.html.find(".towntr")
        res_village  = response.html.find(".villagetr")

        if len(res_year) > 0:
            return handle_year(res_year)
        if len(res_province) > 0:
            return handle_province(res_province)
        if len(res_city) > 0:
            return handle_city(res_city)
        if len(res_county) > 0:
            return handle_county(res_county)
        if len(res_town) > 0:
            return handle_town(res_town)
        if len(res_village) > 0:
            return handle_village(res_village)

        # 有些页面没有值
        for v in [".wrapper-list-title", ".provincehead", ".cityhead", ".countyhead",".townhead", ".villagehead"]:
            if len(reponse.html.find(v)) > 0:
                return

        logging.info("%s 接口调用成功, 但解析失败, 可能被封, 暂停 %ds", url, 10*60)
        time.sleep(10 * 60)
        return handle_url(url)
    except Exception as e:
        logging.info(e)
        logging.info("%s 接口调用失败, 可能被封, 暂停 %ds", url, 60)
        time.sleep(60)
        return handle_url(url)

def get_code(item):
    return item["code"]

start_time = time.time()

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s', datefmt="%Y-%m-%d %H:%M:%S %z")
session = HTMLSession()

all_data = False # True 只查到区县, False 查所有

if "all_data" in sys.argv:
    all_data = True

if all_data:
    path_name = "code-name-gov-stats-all"
else:
    path_name = "code-name-gov-stats"

if not os.path.exists(path_name):
    os.makedirs(path_name)
os.chdir(path_name)

# 获取年数据
years     = {}
url  = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
handle_url(url)

for year, url in years.items():
    logging.info(f"获取 {year} 年的数据...")
    file_name = year + ".csv"
    if os.path.exists(file_name):
        logging.info(f"{year} 年数据已存在, 跳过")
        continue

    results = []
    handle_url(url)
    results.sort(key=get_code)

    logging.info(f"存储 {year} 年的数据...")
    with open(file_name, 'w', encoding='utf-8', newline='') as f:
        writer = csv.writer(f)
        for result in results:
            code     = result["code"]
            name     = result["name"]
            level    = result["level"]
            pcode    = result["pcode"]
            category = result["category"]

            if not all_data:
                code  = code[:6]
                pcode = pcode[:6]
            writer.writerow([code, name, level, pcode, category])

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

