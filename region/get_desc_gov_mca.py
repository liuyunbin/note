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
#    logging.info("handle %s", url)

    try:
        response = session.get(url=url)
        response.encoding = 'gbk'
        return response
    except Exception as e:
        logging.info(e)
        logging.info("%s 接口调用失败, 可能被封, 暂停 %ds", url, 60)
        time.sleep(60)
        return handle_url(url)

def get_code(item):
    return item[0]

start_time = time.time()

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s', datefmt="%Y-%m-%d %H:%M:%S %z")
session = HTMLSession()
text_maker = html2text.HTML2Text()

path_name = "desc-gov-mca"
if not os.path.exists(path_name):
    os.makedirs(path_name)
os.chdir(path_name)

# 获取年数据
logging.info("获取年 url...")
years = {}

url      = "http://xzqh.mca.gov.cn/description?dcpid=1"
response = handle_url(url)
for v in response.html.find(".tz_con a"):
    url  = access_url(v.absolute_links)
    year = url[-4:]
    if year != "":
        years[year] = url

for year in sorted(years):
    logging.info(f"获取 {year} 年的数据...")

    file_name = year + ".txt"
    if os.path.exists(file_name):
        logging.info(f"{year} 年的数据已存在, 跳过")
        continue

    url = years[year]
    response = handle_url(url)
    text = text_maker.handle(response.text)

    #logging.info(f"存储 {year} 年的数据...")
    with open(file_name, 'w', encoding='utf-8') as f:
        f.write(text)

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

