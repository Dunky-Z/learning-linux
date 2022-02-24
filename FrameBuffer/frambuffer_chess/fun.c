#include <stdio.h>
#include <stdlib.h>
#include "fun.h"
#include "input.h"
#include "fb_draw.h"

int color = 0x000000;       //棋盘线颜色    黑色
int back_color = 0xFFFFFF;  //棋盘背景颜色    白色
int play1_color = 0xCC9966; // 0x00BFFF;            //玩家1棋子颜色
int play2_color = 0x000000; // 0xFFBBFF;            //玩家2棋子颜色

Player c = {0, 0, 20, 0x00BFFF};

int ifset(int (*arr)[17], int *x, int *y)
{
    if ((*x) > 16)
        *x = 0;
    if ((*x) < 0)
        *x = 16;
    if ((*y) > 16)
        *y = 0;
    if ((*y) < 0)
        *y = 16;
    if (arr[(*x)][(*y)] == 1 || arr[(*x)][(*y)] == 2)
        return 1;
    return 0;
}

void draw_circle(int x, int y, int r, int color)
{
    int x0, y0;

    for (x0 = x - r; x0 <= x + r; x0++)
    {
        for (y0 = y - r; y0 <= y + r; y0++)
        {
            if ((x0 - x) * (x0 - x) + (y0 - y) * (y0 - y) <= r * r)
                fb_draw_point(x0, y0, color);
        }
    }
}

int is_win(int arr[][17], int x, int y, int mode)
{
    int i = 0, j = 0, sum = 0;

    for (i = x; i < x + 5 && i <= 16; i++) //判断横向可否赢
    {
        if (arr[i + 1][y] == mode)
            sum++;
        else
            break;
    }
    for (i = x; i > x - 5 && i >= 0; i--)
    {
        if (arr[i - 1][y] == mode)
            sum++;
        else
            break;
    }
    if (sum >= 4)
        return 1;
    else
        sum = 0;

    for (i = y; i < y + 5 && i <= 16; i++) //判断纵向可否赢
    {
        if (arr[x][i + 1] == mode)
            sum++;
        else
            break;
    }
    for (i = y; i >= y - 5 && i >= 0; i--)
    {
        if (arr[x][i - 1] == mode)
            sum++;
        else
            break;
    }
    if (sum >= 4)
        return 1;
    else
        sum = 0;

    j = y;
    for (i = x; i < x + 5 && i <= 16; i++) //判断撇可否赢
    {
        if (arr[i + 1][j - 1] == mode)
            sum++;
        else
            break;
        j--;
    }
    j = y;
    for (i = x; i > x - 5 && i >= 0; i--)
    {
        if (arr[i - 1][j + 1] == mode)
            sum++;
        else
            break;
        j++;
    }
    if (sum >= 4)
        return 1;
    else
        sum = 0;

    j = y;
    for (i = x; i < x + 5 && i <= 16; i++) //判断捺可否赢
    {
        if (arr[i + 1][j + 1] == mode)
            sum++;
        else
            break;
    }
    j = y;
    for (i = x; i > x - 5 && i >= 0; i--)
    {
        if (arr[i - 1][j - 1] == mode)
            sum++;
        else
            break;
        j--;
    }
    if (sum >= 4)
        return 1;

    return 0;
}

void print() //打印棋盘
{
    int i = 0, j = 0;

    for (i = 510; i <= 1410; i++) //打印棋盘背景颜色
    {
        for (j = 90; j <= 990; j++)
            fb_draw_point(i, j, back_color);
    }

    for (i = 530; i <= 1390; i++) //打印棋盘外边框 上
    {
        for (j = 110; j <= 113; j++)
            fb_draw_point(i, j, color);
    }

    for (i = 530; i <= 1390; i++) //打印棋盘外边框 下
    {
        for (j = 970; j <= 973; j++)
            fb_draw_point(i, j, color);
    }

    for (i = 530; i <= 533; i++) //打印棋盘外边框 左
    {
        for (j = 110; j <= 970; j++)
            fb_draw_point(i, j, color);
    }

    for (i = 1390; i >= 1385; i--) //打印棋盘外边框 右
    {
        for (j = 112; j <= 970; j++)
            fb_draw_point(i, j, color);
    }
}

void print_line()
{
    int i = 0, j = 0;

    for (i = 560; i <= 1360; i++) //打印棋盘线条
    {
        for (j = 140; j <= 940; j += 50)
            fb_draw_point(i, j, color);
    }

    for (i = 560; i <= 1360; i += 50)
    {
        for (j = 140; j <= 940; j++)
            fb_draw_point(i, j, color);
    }
}

void print_intime(int (*xy_point)[17], Player q)
{
    int i = 0, j = 0, c = 0, d = 0, x = 0, y = 0;

    for (i = 560, x = 0; i <= 1360; i += 50, x++)
    {
        for (j = 140, y = 0; j <= 940; j += 50, y++)
        {
            if (xy_point[x][y] == 1)
                draw_circle(i, j, q.r, play1_color);
            else if (xy_point[x][y] == 2)
                draw_circle(i, j, q.r, play2_color);
            else if (xy_point[x][y] == 0)
            {
                draw_circle(i, j, q.r, back_color);
                for (c = i + 20, d = j; c >= i - 20; c--)
                {
                    if (c < 560 || c > 1360)
                        continue;
                    fb_draw_point(c, d, color);
                }
                for (d = j + 20, c = i; d >= j - 20; d--)
                {
                    if (d < 140 || d > 940)
                        continue;
                    fb_draw_point(c, d, color);
                }
            }
        }
    }
}

void _set(int *x, int *y)
{
    (*x)++;
    if ((*x) == 17)
    {
        (*x) = 0;
        (*y)++;
        if ((*y) == 17)
            (*y) = 0;
    }
}

int play(int (*xy_point)[17], int mode)
{
    int ret = 0, flag = 0, val = 0, tmpx = 0, tmpy = 0;

    flag = input_choice_mode(CHARMODE);

    c.x = 0;
    c.y = 0;
    while (ifset(xy_point, &c.x, &c.y))
        _set(&c.x, &c.y);
    xy_point[c.x][c.y] = mode;
    print_intime(xy_point, c);
LEAP:
    if (flag == 0)
    {
        val = input_kb_mode();
        switch (val)
        {
        case 103:
            tmpy = c.y;
            tmpx = c.x;
            c.y--;
            while (ifset(xy_point, &c.x, &c.y))
                _set(&c.x, &c.y);
            xy_point[tmpx][tmpy] = 0;
            break;
        case 108:
            tmpy = c.y;
            tmpx = c.x;
            c.y++;
            while (ifset(xy_point, &c.x, &c.y))
                _set(&c.x, &c.y);
            xy_point[tmpx][tmpy] = 0;
            break;
        case 105:
            tmpx = c.x;
            tmpy = c.y;
            c.x--;
            while (ifset(xy_point, &c.x, &c.y))
                _set(&c.x, &c.y);
            xy_point[tmpx][tmpy] = 0;
            break;
        case 106:
            tmpx = c.x;
            tmpy = c.y;
            c.x++;
            while (ifset(xy_point, &c.x, &c.y))
                _set(&c.x, &c.y);
            xy_point[tmpx][tmpy] = 0;
            break;
        case 14:
            ret = 1;
            break;
        case 16:
            exit(0);
        }
    }
    else if (flag == 1)
    {
        val = input_char_mode();
        switch (val)
        {
        case 'W':
        case 'w':
            tmpx = c.x;
            tmpy = c.y;
            c.y--;
            while (ifset(xy_point, &c.x, &c.y))
                _set(&c.x, &c.y);
            xy_point[tmpx][tmpy] = 0;
            break;
        case 'S':
        case 's':
            tmpx = c.x;
            tmpy = c.y;
            c.y++;
            while (ifset(xy_point, &c.x, &c.y))
                _set(&c.x, &c.y);
            xy_point[tmpx][tmpy] = 0;
            break;
        case 'A':
        case 'a':
            tmpx = c.x;
            tmpy = c.y;
            c.x--;
            while (ifset(xy_point, &c.x, &c.y))
                _set(&c.x, &c.y);
            xy_point[tmpx][tmpy] = 0;
            break;
        case 'D':
        case 'd':
            tmpx = c.x;
            tmpy = c.y;
            c.x++;
            while (ifset(xy_point, &c.x, &c.y))
                _set(&c.x, &c.y);
            xy_point[tmpx][tmpy] = 0;
            break;
        case ' ':
            ret = 1;
            break;
        case 'q':
            exit(0);
        }
    }
    xy_point[c.x][c.y] = mode;
    print_intime(xy_point, c);
    if (ret != 1)
        goto LEAP;
    if (is_win(xy_point, c.x, c.y, mode))
        return mode;
    return 0;
}