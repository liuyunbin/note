#!/usr/bin/env python3

from requests_html import HTMLSession
import csv
import datetime
import logging
import time
import json
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

def add_result(results, code, name, children, level, pcode = "0", category = "0"):
    result = {}
    result["code"]     = code
    result["name"]     = name
    result["level"]    = level
    result["pcode"]    = pcode
    result["category"] = category
    if children and len(children) > 0:
        result["children"] = children
    results.append(result)

def handle_year(res_year):
    years = {}
    for v in res_year:
        year        = v.text[:4]
        url         = access_url(v.absolute_links)
        years[year] = url
    return years

def handle_province(res_province):
    results = []
    for v in res_province:
        url      = access_url(v.absolute_links)
        name     = v.text
        children = handle_url(url)
        if children and len(children) > 0:
            code = children[0]["code"][:2] + "0000000000"
        else:
            code = ""
        add_result(results, code, name, children, 1)
    return results

def handle_city(res_city):
    results = []
    for v in res_city:
        tds      = v.find("td")
        url      = access_url(tds[0].absolute_links)
        code     = tds[0].text
        name     = tds[1].text
        pcode    = code[:2] + "0000000000"
        children = handle_url(url)
        add_result(results, code, name, children, 2, pcode)
    return results

def handle_county(res_county):
    results = []
    for v in res_county:
        tds      = v.find("td")
        url      = access_url(tds[0].absolute_links)
        code     = tds[0].text
        name     = tds[1].text
        pcode    = code[:4] + "00000000"
        if all_data:
            children = handle_url(url)
        else:
            children = []
        add_result(results, code, name, children, 3, pcode)
    return results

def handle_town(res_town):
    if not all_data:
        return
    results = []
    for v in res_town:
        tds      = v.find("td")
        url      = access_url(tds[0].absolute_links)
        code     = tds[0].text
        name     = tds[1].text
        pcode    = code[:6] + "000000"
        children = handle_url(url)
        add_result(results, code, name, children, 4, pcode)
    return results

def handle_village(res_village):
    if not all_data:
        return
    results = []
    for v in res_village:
        tds      = v.find("td")
        code     = tds[0].text
        category = tds[1].text
        name     = tds[2].text
        pcode    = code[:9] + "000"
        add_result(results, code, name, [], 5, pcode, category)
    return results

# div class="list-content" => ul => li(多) => a(3) (url=href, year=text())
# tr  class="provincetr"   => td(多) => a (url=href, name=text())
# tr  class="citytr"       => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="countytr"     => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="towntr"       => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="villagetr"    => td(3) (code=td[1].text(), code_villagetr=td[2].text(), name=td[3].text())
def handle_url(url):

    if url == "":
        return None

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
                return None

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

def sort_and_format(results):
    results.sort(key=get_code)
    for result in results:
        if "children" in result:
            sort_and_format(result["children"])
        if not all_data:
            result["code"]  = int(result["code"][:6])
            result["pcode"] = int(result["pcode"][:6])
            del result["category"]
        else:
            result["code"]     = int(result["code"])
            result["pcode"]    = int(result["pcode"])
            result["category"] = int(result["category"])

start_time = time.time()

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s', datefmt="%Y-%m-%d %H:%M:%S %z")
session = HTMLSession()

all_data = False # True 只查到区县, False 查所有

if "all_data" in sys.argv:
    all_data = True

if all_data:
    path_name = "code-name-gov-stats-json-all"
else:
    path_name = "code-name-gov-stats-json"

if not os.path.exists(path_name):
    os.makedirs(path_name)
os.chdir(path_name)

# 获取年数据
url   = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
years = handle_url(url)

for year, url in years.items():
    logging.info(f"获取 {year} 年的数据...")

    file_name = year + ".json"
    if os.path.exists(file_name):
        logging.info(f"{year} 年数据已存在, 跳过")
        continue

    results = handle_url(url)
    sort_and_format(results)

    logging.info(f"存储 {year} 年的数据...")
    with open(file_name, 'w',  encoding='utf-8') as f:
        json.dump(results, f, ensure_ascii=False)

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

