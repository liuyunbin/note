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
        year = item[0]
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

        cursor.execute("select code from " + table + " where pcode = " + province_code)
        citys = []
        for city in cursor.fetchall():
            citys.append(city[0])

        cursor.execute("select code from " + table + " where pcode in " + str(tuple(citys))[:-2] + ")" )
        countys = []
        for county in cursor.fetchall():
            countys.append(county[0])

        cursor.execute("select code from " + table + " where pcode in " + str(tuple(countys))[:-2] + ")" )
        towns = []
        for town in cursor.fetchall():
            towns.append(town[0])

        cursor.execute("select code from " + table + " where pcode in " + str(tuple(towns))[:-2] + ")" )
        villages = []
        for village in cursor.fetchall():
            villages.append(village[0])

        results.append([year,
                        str(len(citys)),
                        str(len(countys)),
                        str(len(towns)),
                        str(len(villages))
                       ])

    result = [results[2][0] + "-" + results[-1][0]]
    for i in range(1, 5):
        result.append(str(int(results[-1][i]) - int(results[2][i])))
    results.append(result)

    print("#### " + results[-1][0] + " " + province_name + " 市区县乡镇村数量的汇总")
    for result in results:
        print('|' + '|'.join(result) + '|')
    print("")

# 历年 某个市 的县区乡镇村 的变化
def get_change_city(city_code):
    cursor.execute("select name, pcode from " + tables[-1][1] + " where code = " + city_code)
    data = cursor.fetchall()
    city_name = data[0][0]

    province_code = data[0][1]
    cursor.execute("select name, pcode from " + tables[-1][1] + " where code = " + str(province_code))
    data = cursor.fetchall()
    province_name = data[0][0]

    results = [["年份", "区县", "乡镇", "村"], ["--", "--", "--", "--"]]
    for item in tables:
        year  = item[0]
        table = item[1]

        cursor.execute("select code from " + table + " where pcode = " + city_code)
        countys = []
        for county in cursor.fetchall():
            countys.append(county[0])

        cursor.execute("select code from " + table + " where pcode in " + str(tuple(countys))[:-2] + ")" )
        towns = []
        towns = []
        for town in cursor.fetchall():
            towns.append(town[0])

        cursor.execute("select code from " + table + " where pcode in " + str(tuple(towns))[:-2] + ")" )
        villages = []
        for village in cursor.fetchall():
            villages.append(village[0])

        results.append([year,
                        str(len(countys)),
                        str(len(towns)),
                        str(len(villages))
                       ])

    result = [results[2][0] + "-" + results[-1][0]]
    for i in range(1, 4):
        result.append(str(int(results[-1][i]) - int(results[2][i])))
    results.append(result)

    print("#### " + results[-1][0] + " " + province_name + " " + city_name + " 区县乡镇村数量的汇总")
    for result in results:
        print('|' + '|'.join(result) + '|')
    print("")

# 历年 某个县 的 乡镇村 的变化
def get_change_county(county_code):
    cursor.execute("select name, pcode from " + tables[-1][1] + " where code = " + county_code)
    data = cursor.fetchall()
    county_name = data[0][0]

    city_code = data[0][1]
    cursor.execute("select name, pcode from " + tables[-1][1] + " where code = " + str(city_code))
    data = cursor.fetchall()
    city_name = data[0][0]

    province_code = data[0][1]
    cursor.execute("select name, pcode from " + tables[-1][1] + " where code = " + str(province_code))
    data = cursor.fetchall()
    province_name = data[0][0]

    results = [["年份", "乡镇", "村"], ["--", "--", "--"]]
    for item in tables:
        year  = item[0]
        table = item[1]

        cursor.execute("select code from " + table + " where pcode = " + county_code)
        towns = []
        for town in cursor.fetchall():
            towns.append(town[0])

        cursor.execute("select code from " + table + " where pcode in " + str(tuple(towns))[:-2] + ")" )
        villages = []
        for village in cursor.fetchall():
            villages.append(village[0])

        results.append([year,
                        str(len(towns)),
                        str(len(villages))
                       ])

    result = [results[2][0] + "-" + results[-1][0]]
    for i in range(1, 3):
        result.append(str(int(results[-1][i]) - int(results[2][i])))
    results.append(result)

    print("#### " + results[-1][0] + " " + province_name + " " + city_name + " " + county_name + " 乡镇村数量的汇总")
    for result in results:
        print('|' + '|'.join(result) + '|')
    print("")

# 历年 某个乡镇 的 村 的变化
def get_change_town(town_code):
    cursor.execute("select name, pcode from " + tables[-1][1] + " where code = " + town_code)
    data = cursor.fetchall()
    town_name = data[0][0]

    county_code = data[0][1]
    cursor.execute("select name, pcode from " + tables[-1][1] + " where code = " + str(county_code))
    data = cursor.fetchall()
    county_name = data[0][0]

    city_code = data[0][1]
    cursor.execute("select name, pcode from " + tables[-1][1] + " where code = " + str(city_code))
    data = cursor.fetchall()
    city_name = data[0][0]

    province_code = data[0][1]
    cursor.execute("select name, pcode from " + tables[-1][1] + " where code = " + str(province_code))
    data = cursor.fetchall()
    province_name = data[0][0]

    results = [["年份", "乡镇", "村"], ["--", "--", "--"]]
    for item in tables:
        year  = item[0]
        table = item[1]

        cursor.execute("select code from " + table + " where pcode = " + town_code)
        villages = []
        for village in cursor.fetchall():
            villages.append(village[0])

        results.append([year,
                        str(len(villages))
                       ])

    result = [results[2][0] + "-" + results[-1][0]]
    for i in range(1, 2):
        result.append(str(int(results[-1][i]) - int(results[2][i])))
    results.append(result)

    print("#### " + results[-1][0] + " " + province_name + " " + city_name + " " + county_name + " " +  town_name + " 村数量的汇总")
    for result in results:
        print('|' + '|'.join(result) + '|')
    print("")

def get_detail_new():
    year  = tables[-1][0]
    table = tables[-1][1]

    results = [["代码", "省", "市", "区县", "乡镇", "村"], ["---", "---", "--", "--", "--", "--"]]
    cursor.execute("select code, name from " + table + " where pcode = 0 order by code")
    provinces = cursor.fetchall()
    for item in provinces:
        province_code = item[0]
        province_name = item[1]

        cursor.execute("select code from " + table + " where pcode = " + str(province_code))
        citys = []
        for city in cursor.fetchall():
            citys.append(city[0])

        cursor.execute("select code from " + table + " where pcode in " + str(tuple(citys))[:-2] + ")" )
        countys = []
        for county in cursor.fetchall():
            countys.append(county[0])

        cursor.execute("select code from " + table + " where pcode in " + str(tuple(countys))[:-2] + ")" )
        towns = []
        for town in cursor.fetchall():
            towns.append(town[0])

        cursor.execute("select code from " + table + " where pcode in " + str(tuple(towns))[:-2] + ")" )
        villages = []
        for village in cursor.fetchall():
            villages.append(village[0])

        results.append([str(province_code),
                        province_name,
                        str(len(citys)),
                        str(len(countys)),
                        str(len(towns)),
                        str(len(villages))
                       ])

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
#get_change_city("140700000000")
#get_change_county("140728000000")
#get_change_town("140728202000")


end_time = time.time()
logging.info("took: %ds", end_time - start_time)

