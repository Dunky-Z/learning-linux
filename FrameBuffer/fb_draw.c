#include "inc.h"

/***********************************************
结构体中保存了有关操做framebuffer设备所需的成员
fix : 本地的fb数据
var : 可变的fb数据
bpp : 一个像素点所占位数
fd  : 保存fb文件的文件描述符
fbp : 获取映射空间地址
fbpi: 获取映射空间地址
************************************************/
struct
{
    struct fb_fix_screeninfo fix; //本地fb数据
    struct fb_var_screeninfo var; //可变fb数据
    unsigned int bpp;             //一个像素点所占位数
    int fd;                       //保存fb文件的文件描述符
    unsigned char *fbp;           //获取映射空间地址
    unsigned int *fbpi;           //获取映射空间地址
} fb_st;

/***********************************************
int fb_open(void);
功  能 : 把fb文件打开,经过ioctl控制fb设备
         经过mmap映射fb文件
返回值 : 无
参  数 : 成功返回0, 失败返回-1
************************************************/
int fb_open(void)
{
    int ret;

    fb_st.fd = open("/dev/fb0", O_RDWR);
    if (-1 == fb_st.fd)
    {
        perror("open");
        goto error;
    }

    /* get fb_var_screeninfo */
    ret = ioctl(fb_st.fd, FBIOGET_VSCREENINFO, &fb_st.var);
    if (-1 == ret)
    {
        perror("ioctl(fb_st.var)");
        goto close_fd;
    }

    fb_st.bpp = fb_st.var.bits_per_pixel >> 3;

    /* get fb_fix_screeninfo */
    ret = ioctl(fb_st.fd, FBIOGET_FSCREENINFO, &fb_st.fix);
    if (-1 == ret)
    {
        perror("ioctl(fb_st.fix)");
        goto close_fd;
    }

    /* get framebuffer start address */
    fb_st.fbp = mmap(0, fb_st.fix.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb_st.fd, 0);
    if ((void *)-1 == fb_st.fbp)
    {
        perror("mmap");
        goto close_fd;
    }

    return 0;

close_fd:
    close(fb_st.fd);
error:
    return -1;
}

/***********************************************
void fb_close();
功  能 : 解除设备文件的映射,关闭文件
返回值 : 无
参  数 : 无
************************************************/
void fb_close()
{
    munmap(fb_st.fbp, fb_st.fix.smem_len);
    close(fb_st.fd);
}

/***********************************************
void fb_draw_point(int x, int y, int color);
功  能 : 经过framebuff画点
返回值 : 无
参  数 : x        横坐标
         y        纵坐标
         color    要显示的颜色(现只支持白色0xFF    黑色0x00)
************************************************/
void fb_draw_point(int x, int y, unsigned int color)
{
    unsigned long offset;

    offset = fb_st.bpp * x + y * fb_st.fix.line_length;
    // memset(fb_st.fbp + offset, color, fb_st.bpp);
    fb_st.fbpi = (unsigned int *)(fb_st.fbp + offset);
    *(fb_st.fbpi) = color;
}

/***********************************************
int xres(void);
功  能 : 获取x轴坐标
返回值 : 获取到的x轴坐标
参  数 : 无
************************************************/
int xres(void)
{
    return fb_st.var.xres;
}

/***********************************************
int yres(void);
功  能 : 获取y轴坐标
返回值 : 获取到的y轴坐标
参  数 : 无
************************************************/
int yres(void)
{
    return fb_st.var.yres;
}