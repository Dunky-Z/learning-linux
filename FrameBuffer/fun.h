#ifndef __FUN_H
#define __FUN_H

#define KEYBOARDMODE 0
#define CHARMODE 1

typedef struct cir
{
    int x;
    int y;
    int r;
    int player_color;
} Player;

int ifset(int (*arr)[17], int *x, int *y);
void draw_circle(int x, int y, int r, int color);
int is_win(int arr[][17], int x, int y, int mode);
void print();
void print_line();
void print_intime(int (*xy_point)[17], Player q);
void _set(int *x, int *y);
int play(int (*xy_point)[17], int mode);

#endif