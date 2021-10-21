#include "cyclic-buffer.h"

void cycbuff_init(CyCBuf *cycbuff)
{
    memset(cycbuff->buf, 0, CYCBUFFSIZ);
    cycbuff->read = 0;
    cycbuff->write = 0;
    cycbuff->valid_size = 0;
    // cycbuff->flag = 1; //can write
}

bool cycbuff_isfull(CyCBuf *cycbuff)
{
    if (cycbuff->valid_size == CYCBUFFSIZ)
        return true;
    return false;
}

bool cycbuff_isempty(CyCBuf *cycbuff)
{
    if (cycbuff->write == cycbuff->read && cycbuff->valid_size != CYCBUFFSIZ)
        return true;
    return false;
}

void cycbuff_write(CyCBuf *cycbuff, uint8_t ch)
{
    while (cycbuff_isfull(cycbuff))
        ;
    cycbuff->buf[cycbuff->write] = ch;
    cycbuff->write++;
    cycbuff->write %= CYCBUFFSIZ;
    cycbuff->valid_size++;
}

uint8_t cycbuff_read(CyCBuf *cycbuff)
{
    uint8_t ch;
    while (cycbuff_isempty(cycbuff))
        ;
    ch = cycbuff->buf[cycbuff->read];
    cycbuff->read++;
    cycbuff->read %= CYCBUFFSIZ;
    cycbuff->valid_size--;
    return ch;
}