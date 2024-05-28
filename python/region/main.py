#!/usr/bin/env python3

from lxml import etree
import aiohttp
import json
import logging
import os
import requests
import time
import asyncio
import functools

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(message)s',
                    datefmt="%Y-%m-%d %H:%M:%S %z"
                    )

until_county = True # True --- 只到县一级数据
                    # False -- 所有数据

def access(value):
    if value:
        return value[0].strip()
    return ""

def access_url(value, url_base):
    url = access(value)
    if url != "":
        url = url_base + url
    return url

def handle_url(url):
    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36'
    }

    try:
        reponse = requests.get(url=url, headers=headers)
        logging.info("%s : success", url)
        return reponse
    except Exception as e:
#        logging.info("%s : failed, sleep %d seconds", url, 100)
#time.sleep(100)
        return handle_url(url)

def handle_year(year, url_base, encode):
    for v in year:
        year = access(v.xpath("./a[1]/text()"))[:4]
        url  = access(v.xpath("./a[1]/@href"))
#        if year > "2010":
#            continue
        if year <= "2020":
            encode = "gbk"
        else:
            encode = "utf-8"
        if (not url.startswith("http")):
            url = url_base + url
        result = handle_detail(url, encode)
        if until_county:
            file_name = year + "-county.json"
        else:
            file_name = year + "-all.json"
        with open(file_name, 'w', encoding='utf-8') as f:
            json.dump(result, f, ensure_ascii=False)
#break

def handle_province(province, url_base, encode):
    results = []
    for v in province:
        result         = {}
        result["name"] = access(v.xpath("./text()"))
        url            = access_url(v.xpath("./@href"), url_base)
        if url != "":
            children = handle_detail(url, encode)
            if children and len(children) > 0:
                result["children"] = children
                result["code"]     = children[0]["code"][:2]
        results.append(result)
    return results

def handle_city(city, url_base, encode):
    results = []
    for v in city:
        result         = {}
        result["code"] = access(v.xpath("./td[1]//text()"))[:4]
        result["name"] = access(v.xpath("./td[2]//text()"))
        url            = access_url(v.xpath("./td[1]//@href"), url_base)
        if url != "":
            children = handle_detail(url, encode)
            if children and len(children) > 0:
                result["children"] = children
        results.append(result)
    return results

def handle_county(county, url_base, encode):
    results = []
    for v in county:
        result         = {}
        result["code"] = access(v.xpath("./td[1]//text()"))[:6]
        result["name"] = access(v.xpath("./td[2]//text()"))
        url            = access_url(v.xpath("./td[1]//@href"), url_base)
        if url != "" and not until_county:
            children = handle_detail(url, encode)
            if children and len(children) > 0:
                result["children"] = children
        results.append(result)
    return results

def handle_town(town, url_base, encode):
    results = []
    for v in town:
        result           = {}
        result["code"]   = access(v.xpath("./td[1]//text()"))[:9]
        result["name"]   = access(v.xpath("./td[2]//text()"))
        url              = access_url(v.xpath("./td[1]//@href"), url_base)
        if url != "":
            children = handle_detail(url, encode)
            if children and len(children) > 0:
                result["children"] = children
        results.append(result)
    return results

def handle_village(village, url_base, encode):
    results = []
    for v in village:
        result            = {}
        result["code"]    = access(v.xpath("./td[1]//text()"))
        result["village"] = access(v.xpath("./td[2]//text()"))
        result["name"]    = access(v.xpath("./td[3]//text()"))
        results.append(result)
    return results

# tr class="villagetr"(多) => td(3) (code=td[1].text(), code_villagetr=td[2].text(), name=td[3].text())
# tr class="towntr"(多)    => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr class="countytr"(多)  => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr class="citytr"(多)    => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr class="provincetr"    => td(多) => a (url=href, name=text())
# div class="list-content" => ul => li(多) => a(3) (url=href, year=text())
def handle_detail(url, encode):
    reponse = handle_url(url)
    tree    = etree.HTML(reponse.content, parser=etree.HTMLParser(encoding=encode))

    year     = tree.xpath("//div[@class='list-content']//li")
    province = tree.xpath("//tr[@class='provincetr']//a")
    city     = tree.xpath("//tr[@class='citytr']")
    county   = tree.xpath("//tr[@class='countytr']")
    town     = tree.xpath("//tr[@class='towntr']")
    village  = tree.xpath("//tr[@class='villagetr']")

    url_base  = os.path.dirname(url) + "/"
    if year:
        # 年数据
        url_base = "https://www.stats.gov.cn"
        return handle_year(year, url_base, encode)
    if province:
        # 省数据
        return handle_province(province, url_base, encode)
    if city:
        # 市数据
        return handle_city(city, url_base, encode)
    if county:
        # 区县数据
        return handle_county(county, url_base, encode)
    if town:
        # 乡镇数据
        if until_county:
            return []
        return handle_town(town, url_base, encode)
    if village and all:
        # 村数据
        if until_county:
            return []
        return handle_village(village, url_base, encode)

def main():
    start_time = time.time()

    url      = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
# url      = "https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/index.html"
#    url =  "https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2010/52/5204.html"
    encode   = "utf-8"
#    encode   = "gbk"

    print(handle_detail(url, encode))

    end_time = time.time()
    logging.info("总共耗时: %d 秒" % (end_time - start_time))

main()

