#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define KEYCODE_U 'A'
#define KEYCODE_D 'B'
#define KEYCODE_R 'C'
#define KEYCODE_L 'D'

int main(void) {
    struct termios raw;                                                       

    tcgetattr(0, &raw);               /* 将终端配置读入结构体 raw 中 */
    raw.c_lflag &= ~(ICANON|ECHO);    /* 设置字符不回显 */
    tcsetattr(0, TCSANOW, &raw);      /* 重新配置终端，参数 TCSANOW 表示配置立即更新 */

    puts("Reading from keyboard");
    puts("---------------------------");

    int ch;
    while ((ch=getchar()) != EOF) {
        if (ch == '\033' && (ch=getchar()) == '[') {
            switch (ch=getchar()) {
            case KEYCODE_L: printf("LEFT\n");                         break;
            case KEYCODE_R: printf("RIGHT\n");                        break;
            case KEYCODE_U: printf("UP\n");                           break;
            case KEYCODE_D: printf("DOWN\n");                         break; 
            default: printf("You input not Up,Down,left.or right\n"); break;
            }
       }
       else {
           printf("You input not Up,Down,left.or right\n");
        }
    }

    return 0;
}

