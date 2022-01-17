#include <stdio.h>
#include "inc.h"

int main(void)
{
    int i = 0, j = 0;           //循环变量
    int xy_point[17][17] = {0}; //保存棋盘坐标
    int ret = 0;                //接收函数返回值

    fb_open();
    xres();
    yres();
    input_init();

    print();      //打印棋盘边框和背景
    print_line(); //打印棋盘

    while (1)
    {
        ret = play(xy_point, 1); //玩家1下棋
        if (ret < 0)
            break;
        else if (ret == 1)
        {
            printf("play1 win\n");
            break;
        }

        ret = play(xy_point, 2); //玩家2下棋
        if (ret < 0)
            break;
        else if (ret == 2)
        {
            printf("play2 win\n");
            break;
        }
    }

    input_recover();
    fb_close();

    return 0;
}
