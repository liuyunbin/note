
#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <unistd.h>

#include <list>
#include <utility>

enum DIRECT { LEFT, RIGHT, UP, DOWN }; // 蛇的方向

int row_max; // 终端的长
int col_max; // 终端的宽

// 食物的坐标
int row_food;
int col_food;

// 成绩
int snake_score = 0;
// 表示蛇移动的最长间隔时间，单位，毫秒
const int snake_time_higher = 200;
// 表示蛇移动的最短间隔时间，单位，毫秒
const int snake_time_lower = 100;
// 表示蛇间隔时间的减少值，单位，毫秒，即，每吃到食物，就减少间隔时间
const int snake_time_reduce = 10;
// 表示蛇移动的间隔时间，单位，毫秒
int snake_time = snake_time_higher;

// 存储蛇的轨迹
std::list<std::pair<int, int>> snake;

enum DIRECT direct = RIGHT; // 当前蛇移动的方向

// 设置指定时间发送信号，
// n_msecs 单位为 毫秒
int set_ticker(long n_msecs) {
  struct itimerval new_timeset;
  long n_sec = n_msecs / 1000;             // 求秒
  long n_usecs = (n_msecs % 1000) * 1000L; // 求微秒

  new_timeset.it_interval.tv_sec = n_sec;
  new_timeset.it_interval.tv_usec = n_usecs;
  new_timeset.it_value.tv_sec = n_sec;
  new_timeset.it_value.tv_usec = n_usecs;

  return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

// 销毁界面
void destroy_snake() {
  set_ticker(0);
  endwin(); // 删除 ncurses
  printf("对不起，你失败了\n");
  printf("你的分数为：%d\n", snake_score);
  printf("输入回车退出\n");
  getchar();
  exit(0);
}

// 设置食物的坐标
void set_food() {

  for (;;) {

    row_food = rand() % (row_max - 1);
    col_food = rand() % (col_max - 1);

    for (auto it = snake.cbegin();; ++it) {
      if (it == snake.cend()) {
        move(row_food, col_food);
        addch('*');
        move(row_max - 1, col_max - 1);
        return;
      }
      if (row_food == it->first && col_food == it->second)
        break;
    }
  }
}

// 移动贪吃蛇
void move_snake(int) {
  auto elem = snake.back();

  int row_next = elem.first;
  int col_next = elem.second;

  switch (direct) {
  case LEFT:
    --col_next;
    if (col_next < 0) {
      destroy_snake();
      exit(-1);
    }
    break;
  case RIGHT:
    ++col_next;
    if (col_next >= col_max) {
      destroy_snake();
      exit(-1);
    }
    break;
  case UP:
    --row_next;
    if (row_next < 0) {
      destroy_snake();
      exit(-1);
    }
    break;
  case DOWN:
    ++row_next;
    if (row_next >= row_max) {
      destroy_snake();
      exit(-1);
    }
    break;
  }

  if (row_next == row_food && col_next == col_food) { // 吃到食物
    ++snake_score;
    move(row_next, col_next);
    addch('o');
    snake.emplace_back(row_next, col_next);
    set_food();
    move(row_max - 1, col_max - 1);
    refresh();
    snake_time -= snake_time_reduce;
    if (snake_time < snake_time_lower)
      snake_time = snake_time_lower;
    set_ticker(snake_time); // 加快速度
  } else {                  // 没吃到食物
    for (const auto &data : snake)
      if (data.first == row_next && data.second == col_next) // 吃到自己
        destroy_snake();

    // 删除蛇尾
    elem = snake.front();
    move(elem.first, elem.second);
    addch(' ');
    snake.pop_front();

    // 添加蛇头
    move(row_next, col_next); // 移动光标到指定位置
    addch('o');               // 在指定位置添加字符
    move(row_max - 1, col_max - 1);
    snake.emplace_back(row_next, col_next);
    refresh();
  }
}

// 信号处理
void set_signal() {
  struct sigaction newhandler;

  newhandler.sa_handler = move_snake;
  newhandler.sa_flags = SA_RESTART;

  sigemptyset(&newhandler.sa_mask);

  if (sigaction(SIGALRM, &newhandler, NULL) == -1)
    perror("sigaction");
}

// 获取终端的长和宽
void get_row_col(int &row, int &col) {
  struct winsize wbuf;
  ioctl(0, TIOCGWINSZ, &wbuf);
  row = wbuf.ws_row;
  col = wbuf.ws_col;
}

// 初始化界面
void init_snake() {
  set_signal();

  initscr(); // 初始化 ncurses
  clear();   // 清屏

  get_row_col(row_max, col_max);

  snake.emplace_back(row_max / 2, col_max / 2);

  set_food();

  set_ticker(snake_time_higher);
}

void output_help() {

  printf("\n");
  printf("w 或 方向键向左 表示向左\n");
  printf("d 或 方向键向右 表示向右\n");
  printf("w 或 方向键向上 表示向上\n");
  printf("s 或 方向键向下 表示向下\n");
  printf("q 表示退出\n");
  printf("p 表示暂停 或 开始\n");
  printf("按回车开始\n");
  getchar();
}

int main() {

  output_help();

  init_snake();

  bool stop = false; // 是否暂停

  for (;;) {
    int user_direct = getchar();

    switch (user_direct) { // 方向键
    case '\033':
      getchar(); // 读取 '['
      switch (getchar()) {
      case 'D': // 方向键向左
        user_direct = LEFT;
        break;
      case 'C': // 方向键向右
        user_direct = RIGHT;
        break;
      case 'A': // 方向键向上
        user_direct = UP;
        break;
      case 'B': // 方向键向下
        user_direct = DOWN;
        break;
      }
      break;
    case 'a': // 左
      user_direct = LEFT;
      break;
    case 'd': // 右
      user_direct = RIGHT;
      break;
    case 'w': // 上
      user_direct = UP;
      break;
    case 's': // 下
      user_direct = DOWN;
      break;
    case 'q': // 退出
      destroy_snake();
      break;
    case 'p':              // 暂停 或 开始
      if (stop == false) { // 暂停
        stop = true;
        set_ticker(0);
      } else { // 开始
        stop = false;
        set_ticker(snake_time);
      }
      break;
    }

    switch (user_direct) {
    case LEFT:
      if (direct == RIGHT)
        break;
      direct = LEFT;
      break;
    case RIGHT:
      if (direct == LEFT)
        break;
      direct = RIGHT;
      break;
    case UP:
      if (direct == DOWN)
        break;
      direct = UP;
      break;
    case DOWN:
      if (direct == UP)
        break;
      direct = DOWN;
      break;
    }
  }

  return 0;
}

