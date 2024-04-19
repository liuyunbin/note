
from datetime import datetime, timedelta

# 获取时间戳
#   * 时间戳: 与 1970-01-01 0:0:0 +0000 utc 的浮点秒数的差值
#   * 时间戳不受时区影响
#   * 时间戳不处理闰秒
x = datetime(1953, 1, 1)
y = datetime(1970, 1, 1) + timedelta(hours=8)
time1 = (x - y).total_seconds()
print(time1)

