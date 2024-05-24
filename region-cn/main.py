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

logging.basicConfig(filename='log.txt',
                    level=logging.INFO,
                    format='%(asctime)s %(message)s',
                    datefmt="%Y-%m-%d %H:%M:%S %z"
                    )

test = True

# url_base = "https://www.stats.gov.cn"
def access(value):
    if value:
        return value[0].strip()
    return ""

def access_url(value, url_base):
    url = access(value)
    if url != "":
        url = url_base + url
    return url

async def get_url(result):
    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36'
    }

    try:
        async with aiohttp.ClientSession() as session:
            async with await session.get(url=result["url"], headers=headers) as response:
                content          = await response.read()
                tree             = etree.HTML(content, parser=etree.HTMLParser(encoding=result["encode"]))
                result["xpaths"] = tree.xpath(result["xpath"])
                logging.info("handle %s success", result["url"])
                return result
    except Exception as e:
        logging.exception(e)
        print(result)
        logging.info("handle fail, sleep 10 seconds: %s", result["url"])
        time.sleep(10)
        return await get_url(result)

# tr class="villagetr"(多) => td(3) (code=td[1].text(), code_villagetr=td[2].text(), name=td[3].text())
# tr class="towntr"(多)    => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr class="countytr"(多)  => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr class="citytr"(多)    => td(2)  => a (url=td[1].href, code=td[1].text(), name=td[2].text())
# tr class="provincetr"    => td(多) => a (url=href, name=text())
# div class="list-content" => ul => li(多) => a(3) (url=href, year=text())
def handle_villagetrs(child, v, url_base):
    child["villagetr"] = access(v.xpath("./td[2]//text()"))
    child["name"]      = access(v.xpath("./td[3]//text()"))

def handle_towns(child, v, url_base):
    child["xpath"]    = "//tr[@class='villagetr']"
    child["callback"] = handle_villagetrs
    child["code"]     = child["code"][:9]

def handle_countys(child, v, url_base):
    child["xpath"]    = "//tr[@class='towntr']"
    child["callback"] = handle_towns
    child["code"]     = child["code"][:6]

def handle_citys(child, v, url_base):
    child["xpath"]    = "//tr[@class='countytr']"
    child["callback"] = handle_countys
    child["code"]     = child["code"][:4]

def handle_provinces(child, v, url_base):
    child["xpath"]    = "//tr[@class='citytr']"
    child["callback"] = handle_citys

    child["name"]   = access(v.xpath("./text()"))
    child["url"]    = access_url(v.xpath("./@href"), url_base)

def handle_years(child, v, url_base):
    child["xpath"]    = "//tr[@class='provincetr']//a"
    child["callback"] = handle_provinces

    url_base = "https://www.stats.gov.cn/sj/tjbz/tjyqhdmhcxhfdm/"

    child["year"]     = access(v.xpath("./a[1]/text()"))[:4]
    child["url"]      = url_base + access(v.xpath("./a[1]/@href"))[-15:]
    if child["year"] <= "2020":
        child["encode"] = "gbk"

def handle_base(task, callback):
    result = task.result()
    url    = result["url"]
    encode = result["encode"]

    result["children"] = []
    children = result["children"]

    url_base  = os.path.dirname(url) + "/"
    for v in result["xpaths"]:
        child = {}
        child["encode"] = encode
        child["code"]   = access(v.xpath("./td[1]//text()"))
        child["name"]   = access(v.xpath("./td[2]//text()"))
        child["url"]    = access_url(v.xpath("./td[1]//@href"), url_base)
        callback(child, v, url_base)
        children.append(child)

def use_aiohttp(children):
    if len(children) == 0:
        return
    tasks = []
    for v in children:
        if v["url"] == "":
            continue
        c = get_url(v)
        task = asyncio.ensure_future(c)
        if "callback" in v:
            task.add_done_callback(functools.partial(handle_base, callback=v["callback"]))
        tasks.append(task)
    if len(tasks) != 0:
        loop = asyncio.get_event_loop()
        loop.run_until_complete(asyncio.wait(tasks))
    for v in children:
        if "children" in v:
            print(v["children"])
            use_aiohttp(v["children"])
            print(v["children"])

def del_key(result):
    if result:
        for v in result:
            keys = ["url", "encode", "xpath", "xpaths", "callback"]
            for i in keys:
                if i in v:
                    del v[i]
            if "children" in v:
                del_key(v["children"])

def main():
    start_time = time.time()

    results = []
    result             = {}
    result["url"]      = "https://www.stats.gov.cn/sj/tjbz/qhdm/"
    result["encode"]   = "utf-8"
    result["xpath"]    = "//div[@class='list-content']//li"
    result["callback"] = handle_years
    results.append(result)

    print(results)
    use_aiohttp(results)
    print(results)
    del_key(results)
    print(results)

    for v in result["children"]:
        with open(v["year"] + ".json", 'w', encoding='utf-8') as f:
            print(v)
            json.dump(v, f, ensure_ascii=False)

    end_time = time.time()
    logging.info("总共耗时: %d 秒" % (end_time - start_time))

main()

