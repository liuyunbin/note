#!/usr/bin/env python3

from requests_html import HTMLSession
import csv
import logging
import time
import os

def access_url(urls):
    if len(urls) > 0:
        return urls.pop()
    return ""

def add_result(code, name, level, province = "0", city = "0", county = "0", town = "0", category = "0"):
    results.append([code, name, level, province, city, county, town, category])

def handle_year(res_year):
    for v in res_year:
        year        = v.text[:4]
        url         = access_url(v.absolute_links)
        years[year] = url

def handle_province(res_province):
    for v in res_province:
        url  = access_url(v.absolute_links)
        name = v.text
        code = handle_url(url)
        add_result(code, name, 1)

def handle_city(res_city):
    for v in res_city:
        tds      = v.find("td")
        url      = access_url(tds[0].absolute_links)
        code     = tds[0].text
        name     = tds[1].text
        province = code[:2] + "0000000000"
        add_result(code, name, 2, province)
        handle_url(url, province, code)
    return province

def handle_county(res_county, province, city):
    for v in res_county:
        tds    = v.find("td")
        url    = access_url(tds[0].absolute_links)
        code   = tds[0].text
        name   = tds[1].text
        add_result(code, name, 3, province, city)
        handle_url(url, province, city, code)

def handle_town(res_town, province, city, county):
    for v in res_town:
        tds   = v.find("td")
        url   = access_url(tds[0].absolute_links)
        code  = tds[0].text
        name  = tds[1].text
        add_result(code, name, 4, province, city, county)
        handle_url(url, province, city, county, code)

def handle_village(res_village, province, city, county, town):
    for v in res_village:
        tds      = v.find("td")
        code     = tds[0].text
        category = tds[1].text
        name     = tds[2].text
        add_result(code, name, 5, province, city, county, town, category)

# div class="list-content" => ul => li(多) => a(3) (url=href, year=text())
# tr  class="provincetr"   => td(多) => a (url=href, name=text())
# tr  class="citytr"       => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="countytr"     => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="towntr"       => td(2) => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr  class="villagetr"    => td(3) (code=td[1].text(), code_villagetr=td[2].text(), name=td[3].text())
def handle_url(url, province = "0", city = "0", county = "0", town = "0"):
    if url == "":
        return None

    logging.info("handle %s", url)

    try:
        response = session.get(url=url, timeout=5)

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
            return handle_county(res_county, province, city)
        if len(res_town) > 0:
            return handle_town(res_town, province, city, county)
        if len(res_village) > 0:
            return handle_village(res_village, province, city, county, town)

        # 有些页面没有值
        for v in [".wrapper-list-title", ".provincehead", ".cityhead", ".countyhead",".townhead", ".villagehead"]:
            if len(response.html.find(v)) > 0:
                return None

        logging.info("%s 接口调用成功, 但解析失败, 可能被封, 暂停 %ds", url, 10 * 60)
        time.sleep(10 * 60)
        return handle_url(url, province, city, county, town)
    except Exception as e:
        logging.info(e)
        logging.info("%s 接口调用失败, 可能被封, 暂停 %ds", url, 60)
        time.sleep(60)
        return handle_url(url, province, city, county, town)

start_time = time.time()

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s', datefmt="%Y-%m-%d %H:%M:%S %z")
session = HTMLSession()

# 新建并切换目录
path = "gov-stats-csv"
if not os.path.exists(path):
    os.mkdir(path)
os.chdir(path)

# 获取年数据
url   = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
years = {}
handle_url(url)

for year, url in years.items():
    logging.info(f"获取 {year} 年的数据...")

    file_name_csv_tgz = year + ".csv" + ".tgz"
    if os.path.exists(file_name_csv_tgz):
        logging.info(f"{file_name_csv_tgz} 年数据已存在, 跳过")
        continue
    file_name_csv     = year + ".csv"
    if os.path.exists(file_name_csv):
        logging.info(f"{file_name_csv} 年数据已存在, 跳过获取")
    else:
        results = []
        handle_url(url)
        results.sort(key=lambda v : v[0])

        logging.info(f"存储 {file_name_csv} 数据...")
        with open(file_name_csv, 'w', encoding='utf-8', newline='') as f:
            writer = csv.writer(f, lineterminator='\n')
            writer.writerows(results)
    logging.info(f"{file_name_csv_tgz} 压缩中...")
    os.system("tar acf " + file_name_csv_tgz + " " + file_name_csv)

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

