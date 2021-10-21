#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;

#define CYCBUFFSIZ 500

typedef struct CyclicBuffer
{
    uint8_t buf[CYCBUFFSIZ];
    uint8_t read;
    uint8_t write;
    uint32_t valid_size;
<<<<<<< Updated upstream
=======
    uint32_t total_size;
    uint32_t flag;
>>>>>>> Stashed changes
} CyCBuf;

void cycbuff_init(CyCBuf *cycbuff, uint32_t size);
bool cycbuff_isfull(CyCBuf *cycbuff);
bool cycbuff_isempty(CyCBuf *cycbuff);
void cycbuff_write(CyCBuf *cycbuff, uint8_t ch);
uint8_t cycbuff_read(CyCBuf *cycbuff);