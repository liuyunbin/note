
#### 简介：
利用 ncurses 实现小游戏 snake

#### 程序流程：
1. 使用 sigaction 设置信号 SIGALRM 处理函数 move_snake
    * move_snake 流程如下：
        1. 如果，蛇的下一位置是食物，增加成绩，将该位置添加为蛇的部分，并将蛇加速，重新设置食物
        2. 否则，蛇的下一位置是蛇的部分，输出成绩，游戏结束
        3. 否则，删除蛇尾，将该位置添加为蛇的部分
2. 使用 initscr() 初始化界面
3. 使用 ioctl(0, TIOCGWINSZ, &wbuf) 获取终端的长和宽
4. 将终端的中心位置作为蛇的部分
5. 设置食物位置，食物的位置不能和蛇的部分相同
6. 使用 setitimer(ITIMER_REAL, &new_timeset, NULL) 设置指定时间和时间间隔向程序发送 SIGALRM 信号
7. 开始接收终端的输入，控制蛇的移动方向

#### 说明：
* w 或 方向键向左 表示向左
* d 或 方向键向右 表示向右
* w 或 方向键向上 表示向上
* s 或 方向键向下 表示向下
* q 表示退出
* p 表示暂停 或 开始

#### 参考资源：
* [unix/linux 编程实践教程](https://book.douban.com/subject/1219329/)

