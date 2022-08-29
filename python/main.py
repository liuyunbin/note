# 导入 requests 包
import requests

params = {
    "q":"lyyb"
}

# 发送请求
x = requests.get(url='https://www.bing.com', params=params)

#requests.get(url=,headers=)

# 返回网页内容
print(x.status_code)
