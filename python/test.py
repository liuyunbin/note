#!/usr/bin/env python3

import aiohttp
import datetime
import asyncio
import time

count = 0

def f(count):
    print("函数内赋值前", count)
    count = 1
    print("函数内赋值后", count)

print("调用函数前", count)
f(count)
print("调用函数后", count)
count = 10
print("调用函数前", count)
f(count)
print("调用函数后", count)
