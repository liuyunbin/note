#!/usr/bin/env python3

import requests
import json
from lxml import etree

# url_base = "https://www.stats.gov.cn"

def get_url_etree_xpath(url, path):
    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36'
    }

    try:
        response = requests.get(url=url, headers=headers)
        tree = etree.HTML(response.content, parser=etree.HTMLParser(encoding="utf-8"))
        return tree.xpath(path)
    except Exception as e:
        print("调用报错, 可能临时被封, 强行暂停一分钟, 然后重新请求")
        time.sleep(60)
        return get_url_etree(url)

# 年份的数据
# https://www.stats.gov.cn/sj/tjbz/qhdm/
# 结构: div class="list-content" => ul => li => a
# 返回: https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/index.html 或 /sj/tjbz/tjyqhdmhcxhfdm/2022/index.html
# 目标: https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/index.html
def get_years():
    url      = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
    path     = "//div[@class='list-content']//li"
    url_base = "https://www.stats.gov.cn"

    years = []
    path = get_url_etree_xpath(url, path)
    for v in path:
        url  = v.xpath("./a[1]/@href")[0].strip()
        year = v.xpath("./a[1]/text()")[0].strip()[:4]
        if (not url.startswith("http")):
            url = url_base + url
        print(year, url)
        years.append([year, url])
    return years

# 获取省数据
# https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/index.html
# 结构: tr class="provincetr" => td => a
# 返回: 14.html
# 目标: https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14.html
def get_province(year):
    url      = year[1]
    url_base = "https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/" + year[0] + "/";
    path     = "//tr[@class='provincetr']//a"

    provinces = []
    path = get_url_etree_xpath(url, path)
    for v in path:
        url      = url_base + v.xpath("./@href")[0].strip()
        province = v.xpath("./text()")[0].strip()
        print(province, url)
        provinces.append([province, url])
    return provinces

# 获取市数据
# https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14.html
# 结构: tr class="citytr" => td => a
# 返回: 14/1407.html
# 目标: https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/1407.html
def get_city(province, year):
    url      = province[1]
    url_base = "https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/" + year + "/";
    path     = "//tr[@class='citytr']"

    citys = []
    path = get_url_etree_xpath(url, path)
    for v in path:
        url      = url_base + v.xpath("./td[1]/a/@href")[0].strip()
        code     = v.xpath("./td[1]/a/text()")[0].strip()
        city     = v.xpath("./td[2]/a/text()")[0].strip()
        print(city, code, url)
        citys.append([city, code, url])
    return citys

# 获取县区数据
# https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/1407.html
# 结构: tr class="countytr" => td => a
# 返回: 07/140728.html
# 目标: https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/07/140728.html
def get_county(city, year):
    url      = city[2]
    url_base = "https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/" + year + "/" + city[1][:2] + "/";
    path     = "//tr[@class='countytr']"

    countys = []
    path = get_url_etree_xpath(url, path)
    for v in path:

        url      = v.xpath("./td[1]/a/@href")
        if url:
            url  = url_base + url[0].strip()
        else:
            url  = ""
        code     = v.xpath("./td[1]//text()")[0].strip()
        county   = v.xpath("./td[2]//text()")[0].strip()
        print(county, code, url)
        countys.append([county, code, url])
    return countys

# 获取乡镇数据
# https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/07/140728.html
# 结构: tr class="towntr" => td => a
# 返回: 28/140728202.html
# 目标: https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/07/28/140728202.html
def get_town(county, year):
    url      = county[2]
    url_base = "https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/" + year + "/" + county[1][:2] + "/" + county[1][2:4] + "/";
    path     = "//tr[@class='towntr']"

    towns = []
    path = get_url_etree_xpath(url, path)
    for v in path:

        url      = v.xpath("./td[1]/a/@href")
        if url:
            url  = url_base + url[0].strip()
        else:
            url  = ""
        code = v.xpath("./td[1]//text()")[0].strip()
        town = v.xpath("./td[2]//text()")[0].strip()
        print(town, code, url)
        towns.append([town, code, url])
    return towns

# 获取村数据
# https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/2023/14/07/28/140728202.html
# 结构: tr class="villagetr" => td
def get_village(url):
    path     = "//tr[@class='villagetr']"

    villages = []
    path = get_url_etree_xpath(url, path)
    for v in path:
        code1   = v.xpath("./td[1]//text()")[0].strip()
        code2   = v.xpath("./td[2]//text()")[0].strip()
        village = v.xpath("./td[3]//text()")[0].strip()
        print(village, code1, code2)
        villages.append([village, code1, code2])
    return villages

# 年数据
years = get_years()

# 省数据
provinces = get_province(years[0])

# 市数据
citys = get_city(provinces[3], years[0][0])

# 区县数据
countys = get_county(citys[6], years[0][0])

# 乡镇数据
towns = get_town(countys[9], years[0][0])

# # 村数据
get_village(towns[10][2])

##with open('1.html', 'w', encoding='ISO-8859-1') as f:
##    f.write(response.text)
