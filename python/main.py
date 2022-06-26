import time
import datetime
import random

# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.

# Press the green button in the gutter to run the script.

if __name__ == '__main__':
    print_hi('PyCharm')
    #print(time.localtime(time.time()))
    #print(time.gmtime(time.time()))

print(-536486400.000)
#print("new")
#print(datetime.datetime(1970,1,1) + datetime.timedelta(seconds=-536486400.000))

x = datetime.datetime(1953, 1, 1)
y = datetime.datetime(1970, 1, 1) + datetime.timedelta(hours=8)
print((x - y).total_seconds())

print(-512899200.000)
x = datetime.datetime(1953, 1, 1)
y = y - datetime.timedelta(seconds=512899200)
print(y)
#print((x - y).total_seconds())