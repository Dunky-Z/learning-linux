#ifndef __FB_DRAW_H
#define __FB_DRAW_H

int fb_open(void);
void fb_close(void);
void fb_draw_point(int x, int y, unsigned int color);

int xres(void);
int yres(void);

#endif