#!/usr/bin/env python3

from requests_html import HTMLSession
import csv
import datetime
import logging
import time
import os
import html2text

def access_url(urls):
    if len(urls) > 0:
        return urls.pop()
    return ""

def handle_url(url):
    try:
        response = session.get(url=url)
        response.encoding = 'utf-8'
        return response
    except Exception as e:
        logging.info(e)
        logging.info("%s 接口调用失败, 可能被封, 暂停 %ds", url, 60)
        time.sleep(60)
        return handle_url(url)

def handle_2021(response):
    # 获取 2020 年的数据
    file_name = "2020.csv"
    with open(file_name, 'r', encoding='utf-8', newline='') as f:
        reader = csv.reader(f)
        results = list(reader)
    # 先处理撤销, 在处理设立, 避免同时删除和设立同时存在时, 误删的情况
    for v in response.html.find("td"):
        li = v.text.split("\n")
        if len(li) != 3:
            continue
        if li[2] == "撤销":
            results.remove([li[1], li[0]])
    for v in response.html.find("td"):
        li = v.text.split("\n")
        if len(li) != 3:
            continue
        if li[0] == "设立":
            results.append([li[2], li[1]])
    return results

def handle(response):
    results = []
    text = text_maker.handle(response.text)
    for v in text.split('\n'):
        result = v.split()
        if len(result) == 2 and result[0].isdigit():
            results.append(result)
    return results

def get_code(item):
    return item[0]

start_time = time.time()

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s', datefmt="%Y-%m-%d %H:%M:%S %z")
session = HTMLSession()
text_maker = html2text.HTML2Text()
text_maker.ignore_tables  = True

path_name = "code-name-gov-mca"
if not os.path.exists(path_name):
    os.makedirs(path_name)
os.chdir(path_name)

# 获取年数据
logging.info("获取年 url...")
years = {}

url      = "https://www.mca.gov.cn/n156/n186/index.html"
response = handle_url(url)
for v in response.html.find(".artitlelist"):
    year = v.text[:4]
    url  = access_url(v.absolute_links)
    years[year] = url

# 处理翻页
logging.info("处理翻页...")
for v in response.html.find("div > a"):
    if v.text:
        continue
    url      = access_url(v.absolute_links)
    response = handle_url(url)
    for w in response.html.find(".artitlelist"):
        year        = w.text[:4]
        if not year.isdigit():
            continue
        url         = access_url(w.absolute_links)
        years[year] = url

# 2010 及之前的 url 是直接的url
# 2010 之后需要特殊处理
logging.info("处理 2010 年之后的间接的 url...")
all_urls = {}
for year, url in years.items():
    if year > "2010":
        response = handle_url(url)
        res = response.html.find(".content a")
        years[year] = res[0].absolute_links.pop()

for year in sorted(years):
    logging.info(f"获取 {year} 年的数据...")

    file_name = year + ".csv"
    if os.path.exists(file_name):
        logging.info(f"{year} 年的数据已存在, 跳过")
        continue

    url = years[year]
    while True:
        response = handle_url(url)
        if year == "2021":
            results = handle_2021(response) # 2021 年只列了新增和撤销
        else:
            results = handle(response)
        if len(results) > 0:
            break
        logging.info(url)
        logging.info(f"{year} 年的数据获取失败, 暂停 10 秒后重试...")
        time.sleep(10)

    results.sort(key=get_code)
    #logging.info(f"存储 {year} 年的数据...")
    with open(file_name, 'w', encoding='utf-8', newline='') as f:
        writer = csv.writer(f)
        writer.writerows(results)

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

