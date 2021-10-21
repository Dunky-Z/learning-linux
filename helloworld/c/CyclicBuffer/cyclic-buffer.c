#include "cyclic-buffer.h"

void cycbuff_init(CyCBuf *cycbuff, uint32_t size)
{
    memset(cycbuff->buf, 0, CYCBUFFSIZ);
    cycbuff->read = 0;
    cycbuff->write = 0;
    cycbuff->valid_size = 0;
    cycbuff->total_size = size;
    cycbuff->flag = 1; //can write
}

bool cycbuff_isfull(CyCBuf *cycbuff)
{
    if (cycbuff->valid_size == CYCBUFFSIZ)
        return true;
    return false;
}

bool cycbuff_isempty(CyCBuf *cycbuff)
{
    if (cycbuff->write == cycbuff->read)
        return true;
    return false;
}

void cycbuff_write(CyCBuf *cycbuff, uint8_t ch)
{
    // if (cycbuff_isfull(cycbuff))
    // {
    //     while (1)
    //     {
    //     }
    // }
    *(uint8_t *)((uint8_t *)cycbuff->buf + cycbuff->write) = ch;
    printf("server cycbuff write: %p\n", (uint8_t *)cycbuff->buf + cycbuff->write);
    printf("server cycbuff flag: %p\n", &(cycbuff->flag));

    cycbuff->write++;
    cycbuff->write %= CYCBUFFSIZ;
    cycbuff->valid_size++;
    cycbuff->flag = 0;
}

uint8_t cycbuff_read(CyCBuf *cycbuff)
{
    uint8_t ch;
    // if (cycbuff_isempty(cycbuff))
    // {
    //     while (1)
    //     {
    //     }
    // }
    // memcpy(&ch, (uint8_t *)cycbuff->buf, cycbuff->read + 1);
    printf("client read: %p\n", &(cycbuff->read));
    printf("client read: %d\n", (cycbuff->read));
    printf("client cycbuff buf: %p\n", ((uint8_t *)cycbuff->buf));
    printf("client cycbuff buff + read: %p\n", (uint8_t *)cycbuff->buf + cycbuff->read);
    printf("client cycbuff flag: %p\n", &(cycbuff->flag));
    ch = *(uint8_t *)((uint8_t *)cycbuff->buf + cycbuff->read);
    cycbuff->read++;
    cycbuff->read %= CYCBUFFSIZ;
    cycbuff->valid_size--;
    cycbuff->flag = 1;
    return ch;
}