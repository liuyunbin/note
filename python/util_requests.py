
import requests #导入 requests 包

url = 'https://www.bing.com'

headers = {
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36'
}

params = {
    "q":"www"
}

# 发送 get 请求
x = requests.get(url=url, params=params, headers=headers)
print(x.status_code)

# 发送 post 请求
x = requests.post(url=url, data=params, headers=headers)
print(x.status_code)
