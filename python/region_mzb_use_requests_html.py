#!/usr/bin/env python3

from requests_html import HTMLSession
import csv
import datetime
import logging
import time

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s', datefmt="%Y-%m-%d %H:%M:%S %z")
session = HTMLSession()

def access(value):
    if value:
        return value[0].strip()
    return ""

def access_url(urls):
    if len(urls) > 0:
        return urls.pop()
    return ""

def handle_url(url):
    logging.info("handle %s", url)

    try:
        reponse = session.get(url=url)
        return reponse
    except Exception as e:
        logging.info(e)
        logging.info("%s 接口调用失败, 可能被封, 暂停 %ds", url, 60)
        time.sleep(60)
        return handle_url(url)

def get_code(item):
    return item["code"]

start_time = time.time()

# 获取年数据
print("获取年数据")
url     = "https://www.mca.gov.cn/n156/n186/index.html"
reponse = handle_url(url)

years = {}
for v in reponse.html.find(".artitlelist"):
    year = v.text[:4]
    url  = access_url(v.absolute_links)
    years[year] = url

# 处理翻页
print("处理翻页")
for v in reponse.html.find("div > a"):
    if v.text:
        continue
    url     = access_url(v.absolute_links)
    reponse = handle_url(url)
    for w in reponse.html.find(".artitlelist"):
        year        = w.text[:4]
        if not year.isdigit():
            continue
        url         = access_url(w.absolute_links)
        years[year] = url

# 2010 及之前的 url 是直接的url
# 2010 之后需要特殊处理
print("2010 之前的特殊的 url")
for year, url in years.items():
    if year > "2010":
        reponse = handle_url(url)
        res = reponse.html.find(".content a")
        if len(res) > 1:
            res.pop()
        years[year] = res.pop().absolute_links.pop()

for year, url in years.items():
    print(f"获取 {year} 的数据")
    results = []

    reponse = handle_url(url)
    if year == "2021":
        for v in reponse.html.find("td"):
            fonts = v.find("font")
            if len(fonts) == 2 or len(fonts) == 4:
                print(v.text)
                print("")
        break



    for v in reponse.html.find("tr"):
        tds = v.find("td")
        if len(tds) < 2:
            continue
        code = tds[1].text
        name = tds[2].text
        if code.isdigit():
            results.append({"code":code, "name":name})
#            print(code, name)

    with open(year + "-mzb.csv", 'w', encoding='utf-8', newline='') as f:
        writer = csv.writer(f)
        for result in results:
            code     = result["code"]
            name     = result["name"]
            writer.writerow([code, name])

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

