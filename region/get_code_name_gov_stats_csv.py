#!/usr/bin/env python3

import csv
import datetime
import logging
import time
import json
import os
import sys

def get_results(results, data):
    for v in data:
        results.append([v["code"], v["name"], v["level"], v["pcode"]])
        if "children" in v:
            get_results(results, v["children"])

def get_code(data):
    return data[0]

start_time = time.time()

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s', datefmt="%Y-%m-%d %H:%M:%S %z")

all_data = False # True 只查到区县, False 查所有

if "all_data" in sys.argv:
    all_data = True

path_name_csv = "code-name-gov-stats-csv"
if all_data:
    path_name_csv = path_name_csv + "-all"

if not os.path.exists(path_name_csv):
    os.makedirs(path_name_csv)
path_name_csv = os.path.abspath(path_name_csv)

path_name_json = "code-name-gov-stats-json"
if all_data:
    path_name_json = path_name_json + "-all"
os.chdir(path_name_json)

files = os.listdir(".")
files.sort()

for file_name_json in files:
    logging.info(f"处理 {file_name_json} 数据...")

    with open(file_name_json, 'r', encoding='utf-8', newline='') as f:
        data = json.load(f)

    file_name_csv = path_name_csv + "/" + file_name_json[:4] + ".csv"
    if os.path.exists(file_name_csv):
        logging.info(f"{file_name_csv} 数据已存在, 跳过")
        continue

    results = []
    get_results(results, data)
    results.sort(key=get_code)

    with open(file_name_csv, 'w',  encoding='utf-8') as f:
        writer = csv.writer(f, lineterminator='\n')
        writer.writerows(results)

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

