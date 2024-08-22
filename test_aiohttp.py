#!/usr/bin/env python3

import aiohttp
import datetime
import asyncio
import time

count_success = 0
count_failed  = 0

async def handle_url(url):
    global count_success
    global count_failed

    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36'
    }

    try:
        async with aiohttp.ClientSession() as session:
            async with await session.get(url=url, headers=headers) as response:
                content = await response.read()
                count_success = count_success + 1
                return content
    except Exception as e:
        print(e)
        count_failed = count_failed + 1

start_time = time.time()

count = 10000

url = "http://127.0.0.1"

tasks = []
while count > 0:
    c = handle_url(url)
    task = asyncio.ensure_future(c)
    tasks.append(task)
    count = count - 1
loop = asyncio.get_event_loop()
loop.run_until_complete(asyncio.wait(tasks))

end_time = time.time()
print(f"took: {(end_time - start_time)}s count_success: {count_success} count_failed: {count_failed}")

