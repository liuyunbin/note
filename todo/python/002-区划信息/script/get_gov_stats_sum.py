#!/usr/bin/env python3

import datetime
import logging
import time
import re
import mysql.connector

# 历年 省市区县乡镇村的变化情况
def get_change_year():
    print("")

    results = [["年份", "省", "市", "区县", "乡镇", "村"], ["--", "--", "--", "--", "--", "--"]]
    for item in tables:
        year  = item[0]
        table = item[1]
        cursor.execute("select count(*) from " + table + " group by level order by level")
        result = [year]
        for data in cursor.fetchall():
            result.append(str(data[0]))
        results.append(result)

    result = [results[2][0] + "-" + results[-1][0]]
    for i in range(1, 6):
        result.append(str(int(results[-1][i]) - int(results[2][i])))
    results.append(result)

    print("#### " + results[-1][0] + " 省市区县乡镇村数量的变化")
    for result in results:
        print('|' + '|'.join(result) + '|')
    print("")

# 历年 某个省的 市县区乡镇村 的变化
def get_change_province(province_code):
    cursor.execute("select name from " + tables[-1][1] + " where code = " + province_code)
    data = cursor.fetchall()
    province_name = data[0][0]

    results = [["年份", "市", "区县", "乡镇", "村"], ["--", "--", "--", "--", "--"]]
    for item in tables:
        year  = item[0]
        table = item[1]

        cursor.execute("select count(*) from " + table + " where province = " + province_code + " group by level order by level")
        data = cursor.fetchall()
        result = [year, str(data[0][0]), str(data[1][0]), str(data[2][0]), str(data[3][0])]
        results.append(result)

    result = [results[2][0] + "-" + results[-1][0]]
    for i in range(1, 5):
        result.append(str(int(results[-1][i]) - int(results[2][i])))
    results.append(result)

    print("#### " + results[-1][0] + " " + province_name + " 市区县乡镇村数量的汇总")
    for result in results:
        print('|' + '|'.join(result) + '|')
    print("")

def get_detail_new():
    year  = tables[-1][0]
    table = tables[-1][1]

    results = [["代码", "省", "市", "区县", "乡镇", "村"], ["---", "---", "--", "--", "--", "--"]]
    cursor.execute("select code, name from " + table + " where level = 1 order by code")
    provinces = cursor.fetchall()
    for item in provinces:
        province_code = str(item[0])
        province_name = item[1]

        cursor.execute("select count(*) from " + table + " where province = " + province_code + " group by level order by level")
        data = cursor.fetchall()
        result = [province_code, province_name, str(data[0][0]), str(data[1][0]), str(data[2][0]), str(data[3][0])]
        results.append(result)

    result = [" ", "全国", 0, 0, 0, 0]
    for i in range(2, len(results)):
        for j in range(2, 6):
            result[j] = result[j] + int(results[i][j])
    for i in range(2, 6):
        result[i] = str(result[i])
    results.append(result)

    print("#### " + year + " 省市区县乡镇村数量的汇总")
    for result in results:
        print('|' + '|'.join(result) + '|')
    print("")

start_time = time.time()

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s', datefmt="%Y-%m-%d %H:%M:%S %z")

db = mysql.connector.connect(
  host="localhost",
  user="root",
  password="root",
  database="testdb"
)

cursor = db.cursor()

cursor.execute("show tables")

tables = []
for v in cursor.fetchall():
    table = v[0]
    if re.match("^gov_stats_", table):
        year = table[-4:]
        tables.append([year, table])

tables.sort(key=lambda v: v[0])

get_change_year()
get_detail_new()
get_change_province("140000000000")

end_time = time.time()
logging.info("took: %ds", end_time - start_time)

