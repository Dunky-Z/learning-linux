#include "cyclic-buffer.h"

void cycbuff_init(CyCBuf *cycbuff)
{
    memset(cycbuff->buf, 0, CYCBUFFSIZ);
    cycbuff->read = 0;
    cycbuff->write = 0;
    cycbuff->valid_size = 0;
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
    cycbuff->buf[cycbuff->write] = ch;

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

    ch = cycbuff->buf[cycbuff->read];
    cycbuff->read++;
    cycbuff->read %= CYCBUFFSIZ;
    cycbuff->valid_size--;
    cycbuff->flag = 1;
    return ch;
}