#!/usr/bin/env python3

# 写入 JSON 文件(整个文件是一个JSON)
import json

results = {"abc":"中国"}
file_name = "1.json"
with open(file_name, 'w', encoding='utf-8') as f:
    json.dump(results, f, ensure_ascii=False)

# 读取 JSON 文件(整个文件是一个JSON)
file_name = "1.json"
with open(file_name, 'r', encoding='utf-8') as f:
    data = json.load(f)
print(data)

# 写入 JSON 文件(每行一个JSON)
results = {"abc":"中国"}
file_name = "1.json"
with open(file_name, 'w', encoding='utf-8') as f:
    data = json.dumps(results, ensure_ascii=False)
    f.write(data + "\n")
    f.write(data + "\n")

# 读取 JSON 文件(每行一个JSON)
file_name = "1.json"
with open(file_name, 'r', encoding='utf-8') as f:
    for line in f:
        data = json.loads(line)
print(data)

