#include <stdbool.h>
#include <string.h>
#include "cachelab.h"
#include "getopt.h"

static int S; // 组个数
static int s; // 组占的位数
static int E;
static int B;
static int hits = 0;
static int misses = 0;
static int evictions = 0;

typedef struct _CacheLine {
    unsigned tag;
    struct _CacheLine *next;
    struct _CacheLine *prev;
} CacheLine;

typedef struct _Cache {
    CacheLine *head;
    CacheLine *tail;
    int *size;
} Cache;

static Cache *cache;

void parse_option(int argc, char **argv, char **fileName)
{
    int option;
    while ((option = getopt(argc, argv, "s:E:b:t:")) != -1) {
        switch (option) {
        case 's':
            s = atoi(optarg);
            // 传入的参数为占用的bit，需要转换为10进制
            S = 1 << s;
        case 'E':
            E = atoi(optarg);
        case 'b':
            B = atoi(optarg);
        case 't':
            strcpy(*fileName, optarg);
        }
    }
}

void initialize_cache()
{
    cache = malloc(S * sizeof(*cache));
    for (int i = 0; i < S; i++) {
        cache[i].head = malloc(sizeof(CacheLine));
        cache[i].tail = malloc(sizeof(CacheLine));

        cache[i].head->next = cache[i].tail;
        cache[i].tail->prev = cache[i].head;
        (cache[i].size) = (int *)malloc(sizeof(int));
        *(cache[i].size) = 0;
    }
}

/*!
 * @breif Add a new CacheLine to the Cache first line
 * @param nodeToDel CacheLine to be deleted
 * @param curLru  Current Cache
 */
void insert_first_line(CacheLine *node, Cache *curLru)
{
    node->next = curLru->head->next;
    node->prev = curLru->head;

    curLru->head->next->prev = node;
    curLru->head->next = node;

    *(curLru->size) = *(curLru->size) + 1;
}

void evict(CacheLine *nodeToDel, Cache *curLru)
{
    nodeToDel->next->prev = nodeToDel->prev;
    nodeToDel->prev->next = nodeToDel->next;
    *(curLru->size) = *(curLru->size) - 1;
}

void update(unsigned address)
{
    unsigned int mask = 0xFFFFFFFF;
    unsigned int maskSet = mask >> (32 - s);
    // 取出组索引
    unsigned int targetSet = ((maskSet) & (address >> B));
    // 取出标记
    unsigned int targetTag = address >> (s + B);

    Cache curLru = cache[targetSet];

    // 查找是否存与当前标记位相同的缓存行
    CacheLine *cur = curLru.head->next;
    bool found = 0;
    while (cur != curLru.tail) {
        if (cur->tag == targetTag) {
            found = true;
            break;
        }
        cur = cur->next;
    }

    if (found) {
        hits++;
        evict(cur, &curLru);
        insert_first_line(cur, &curLru);
        printf("> hit!, set: %d \n", targetSet);
    } else {
        CacheLine *newNode = malloc(sizeof(CacheLine));
        newNode->tag = targetTag;
        if (*(curLru.size) == E) { // 如果缓存已满，则删除最后一个缓存行
            evict(curLru.tail->prev, &curLru);
            insert_first_line(newNode, &curLru);
            evictions++;
            misses++;
            printf("> evic && miss set:%d\n", targetSet);
        } else {
            misses++;
            insert_first_line(newNode, &curLru);
            printf("> miss %d\n", targetSet);
        }
    }
}

void cache_simulate(char *fileName)
{
    // 分配并初始化S组缓存
    initialize_cache();

    FILE *file = fopen(fileName, "r");
    char op;
    unsigned int address;
    int size;

    while (fscanf(file, " %c %x,%d", &op, &address, &size) > 0) {
        printf("%c, %x %d\n", op, address, size);
        switch (op) {
        case 'L':
            update(address);
            break;
        case 'M':
            update(address);
        case 'S':
            update(address);
            break;
        }
    }
}

int main(int argc, char **argv)
{
    char *fileName = malloc(100 * sizeof(char));

    parse_option(argc, argv, &fileName);
    cache_simulate(fileName);
    printSummary(hits, misses, evictions);
    return 0;
}
