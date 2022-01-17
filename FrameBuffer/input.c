#include "inc.h"

/***********************************************
结构体中保存了有关键盘操做或者终端设置的一些成员
old : 保存原始终端信息
new : 改变以后的终端信息
kb_fd : 保存键盘设备的设备号
ev : 保存输入设备的信息数据
************************************************/
struct
{
    struct termios old;
    struct termios new;
    int kb_fd;
    struct input_event ev;
} input_st;

/***********************************************
void input_init(void);
功  能 : 用来在接收输入值以前设置终端
返回值 : 无
参  数 : 无
************************************************/
void input_init(void)
{
    tcgetattr(0, &input_st.old);
    input_st.new = input_st.old;
    input_st.new.c_lflag &= ~ICANON;
    input_st.new.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &input_st.new);
}

/***********************************************
char *mystrcpy(char *dest, const char *src);
功  能 : 用来拷贝字符串,碰到尾0或者空格中止
返回值 : 指向dest的指针
参  数 : dest    拷贝的目标,dest指向拷贝的空间
         src    拷贝的源,指向要拷贝的字符串
************************************************/
char *mystrcpy(char *dest, const char *src)
{
    int i = 0;

    for (i = 0; src[i] != '\0' && src[i] != ' '; i++)
        dest[i] = src[i];
    dest[i] = '\0';

    return dest;
}

/***********************************************
void input_find_dev_file(char *buf_ev);
功  能 : 用来读取当前用户识别的键盘文件
返回值 : 无
参  数 : buf_ev    保存获取到的键盘设备文件名
************************************************/
void input_find_dev_file(char *buf_ev)
{
    FILE *fp = NULL;
    char buf[128] = {0};
    char *find_kb = "keyboard";
    char *find_ev = "event";
    char *p = NULL;

    fp = fopen("/proc/bus/input/devices", "r");

    while ((fgets(buf, sizeof(buf) - 1, fp)) != NULL)
    {
        p = strstr(buf, find_kb);
        if (p == NULL)
            continue;
        else
        {
            while ((fgets(buf, sizeof(buf) - 1, fp)) != NULL)
            {
                p = strstr(buf, find_ev);
                if (p == NULL)
                    continue;
                else
                {
                    mystrcpy(buf_ev, p);
                    break;
                }
            }
            break;
        }
    }

    fclose(fp);
}

/***********************************************
int input_choice_mode(int mode);
功  能 : 用来选择接收输入源的模式
返回值 : 0 表明使用键盘模式
         1 表明使用字符模式
         -1 表明选择模式失败
参  数 : KEYBOARDMODE    键盘模式
         CHARMODE        字符模式
************************************************/
int input_choice_mode(int mode)
{
    char dest[64] = "/dev/input/";
    char buf[8] = {0};
    switch (mode)
    {
    case KEYBOARDMODE:
        input_find_dev_file(buf);
        strcat(dest, buf);
        input_st.kb_fd = open(dest, O_RDONLY);
        if (input_st.kb_fd < 0)
        {
            perror("open()");
            return -1;
        }
        break;
    case CHARMODE:
        break;
    default:
        return -1;
    }
    return mode;
}

/***********************************************
int input_kb_mode(void);
功  能 : 获取键盘的键值,并返回
返回值 : 为了使用方便,返回[103上]
         返回[108下], 返回[105左]
         返回[106右], 返回[14落子]
         返回[16quit]
参  数 : 无
************************************************/
int input_kb_mode(void)
{
    read(input_st.kb_fd, &input_st.ev, sizeof(input_st.ev));
    if (input_st.ev.type == EV_KEY)
        if (input_st.ev.value == SYN_REPORT)
        {
            if (input_st.ev.code == 16)
            {
                tcsetattr(0, TCSANOW, &input_st.old);
                close(input_st.kb_fd);
            }
            return input_st.ev.code;
        }
    return 0;
}

/***********************************************
int input_char_mode(void);
功  能 : 获取键盘字符,并返回
返回值 : 为了使用方便,返回[w上]
         返回[s下], 返回[a左]
         返回[d右], 返回[' ']
         返回[qquit]
         请自行处理大小写
参  数 : 无
************************************************/
int input_char_mode(void)
{
    int val = 0;

    val = getchar();
    if (val == 'q' || val == 'Q')
        tcsetattr(0, TCSANOW, &input_st.old);
    return val;
}

/***********************************************
void input_recover(void);
功  能 : 用来恢复设置终端
返回值 : 无
参  数 : 无
************************************************/
void input_recover(void)
{
    tcsetattr(0, TCSANOW, &input_st.old);
}