#!/usr/bin/env python3

from requests_html import HTMLSession
from requests_html import AsyncHTMLSession
import time
import asyncio
import requests

session = HTMLSession()
asession = AsyncHTMLSession()

count_success = 0
count_failed  = 0

async def handle_url(url):
    global count_success
    global count_failed

    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36'
    }

    try:
        reponse = await asession.get(url=url)
        count_success = count_success + 1
    except Exception as e:
        print(e)
        count_failed = count_failed + 1

start_time = time.time()

count = 1

url = "http://127.0.0.1"

tasks = []
while count > 0:
    tasks.append( lambda url=url: handle_url(url))
    count = count - 1
asession.run(*tasks)

end_time = time.time()
print(f"took: {(end_time - start_time)}s count_success: {count_success} count_failed: {count_failed}")

