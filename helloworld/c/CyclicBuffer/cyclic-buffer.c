#include "cyclic-buffer.h"

void cycbuff_init(CyCBuf *cycbuff, uint32_t size, uint8_t *shmptr)
{
    cycbuff->buf = shmptr;
    // memset(cycbuff->buf, 0, size);
    cycbuff->read = 0;
    cycbuff->write = 0;
    cycbuff->valid_size = 0;
    cycbuff->total_size = size;
}

bool cycbuff_isfull(CyCBuf *cycbuff)
{
    if (cycbuff->valid_size == cycbuff->total_size)
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
    *(uint8_t *)(cycbuff->buf + cycbuff->write) = ch;

    cycbuff->write++;
    cycbuff->write %= cycbuff->total_size;
    cycbuff->valid_size++;
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

    ch = *(uint8_t *)(cycbuff->buf + cycbuff->read);
    cycbuff->read++;
    cycbuff->read %= cycbuff->total_size;
    cycbuff->valid_size--;

    return ch;
}