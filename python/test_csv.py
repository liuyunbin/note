#!/usr/bin/env python3

# 写入 CSV 文件(一次写入多行)
import csv

results = [["a","b","c"], ["中","国","人"]]
file_name = "1.csv"
with open(file_name, 'w', encoding='utf-8', newline='') as f:
    writer = csv.writer(f, lineterminator='\n')
    writer.writerows(results)

# 读取 CSV 文件
file_name = "1.csv"
with open(file_name, 'r', encoding='utf-8', newline='') as f:
    reader = csv.reader(f)
    results = list(reader)
    print(results)

# 写入 CSV 文件(一次写入一行)
results = [["a","b","c"], ["中","国","人"]]
file_name = "1.csv"
with open(file_name, 'w', encoding='utf-8', newline='') as f:
    writer = csv.writer(f, lineterminator='\n')
    writer.writerow(results[0])
    writer.writerow(results[1])

