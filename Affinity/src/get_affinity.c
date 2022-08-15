#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/syscall.h>

int get_affinity_with_s(void)
{
    int i, nrcpus;
    cpu_set_t *pmask;
    size_t cpusize;
    unsigned long bitmask = 0;

    /* 获取逻辑CPU个数 */
    nrcpus = sysconf(_SC_NPROCESSORS_CONF);

    pmask = CPU_ALLOC(nrcpus);
    cpusize = CPU_ALLOC_SIZE(nrcpus);
    CPU_ZERO_S(cpusize, pmask);

    /* 获取CPU亲和性 */
    if (sched_getaffinity(0, cpusize, pmask) == -1) {
        perror("sched_getaffinity");
        CPU_FREE(pmask);
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < nrcpus; i++) {
        if (CPU_ISSET_S(i, cpusize, pmask)) {
            bitmask |= (unsigned long)0x01 << i;
            printf("processor #%d is set\n", i);
        }
    }
    printf("bitmask = %#lx\n", bitmask);

    CPU_FREE(pmask);
}

int get_affinity_without_s(void)
{
    int i, nrcpus;
    cpu_set_t mask;
    unsigned long bitmask = 0;

    CPU_ZERO(&mask);

    /* 获取CPU亲和性 */
    if (sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_getaffinity");
        exit(EXIT_FAILURE);
    }

    /* 获取逻辑CPU个数 */
    nrcpus = sysconf(_SC_NPROCESSORS_CONF);

    for (i = 0; i < nrcpus; i++) {
        if (CPU_ISSET(i, &mask)) {
            bitmask |= (unsigned long)0x01 << i;
            printf("processor #%d is set\n", i);
        }
    }
    printf("bitmask = %#lx\n", bitmask);
}

int set_process_affinity(void)
{
    int i, nrcpus;
    cpu_set_t mask;
    unsigned long bitmask = 0;

    CPU_ZERO(&mask);

    CPU_SET(0, &mask); /* add CPU0 to cpu set */
    CPU_SET(2, &mask); /* add CPU2 to cpu set */
    CPU_SET(3, &mask); /* add CPU3 to cpu set */

    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }

    CPU_ZERO(&mask);

    if (sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_getaffinity");
        exit(EXIT_FAILURE);
    }

    nrcpus = sysconf(_SC_NPROCESSORS_CONF);

    for (i = 0; i < nrcpus; i++) {
        if (CPU_ISSET(i, &mask)) {
            bitmask |= (unsigned long)0x01 << i;
            printf("processor #%d is set\n", i);
        }
    }
    printf("bitmask = %#lx\n", bitmask);
}

#define handle_error_en(en, msg)                                                                                                                     \
    do {                                                                                                                                             \
        errno = en;                                                                                                                                  \
        perror(msg);                                                                                                                                 \
        exit(EXIT_FAILURE);                                                                                                                          \
    } while (0)

int get_thread_affinity(void)
{
    int s, j;
    cpu_set_t cpuset;
    pthread_t thread;

    thread = pthread_self();

    /* Set affinity mask to include CPUs 0 to 7 */
    CPU_ZERO(&cpuset);
    for (j = 0; j < 8; j++)
        CPU_SET(j, &cpuset);

    s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) {
        handle_error_en(s, "pthread_setaffinity_np");
    }

    /* Check the actual affinity mask assigned to the thread */
    s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (s != 0) {
        handle_error_en(s, "pthread_getaffinity_np");
    }

    printf("Set returned by pthread_getaffinity_np() contained:\n");
    //CPU_SETSIZE 是定义在<sched.h>中的宏，通常是1024
    for (j = 0; j < CPU_SETSIZE; j++) {
        if (CPU_ISSET(j, &cpuset)) {
            printf("    CPU %d\n", j);
        }
    }
}

int set_thread_affinity(void)
{
    pid_t tid;
    int i, nrcpus;
    cpu_set_t mask;
    unsigned long bitmask = 0;

    CPU_ZERO(&mask);
    CPU_SET(0, &mask); /* add CPU0 to cpu set */
    CPU_SET(2, &mask); /* add CPU2 to cpu set */

    // 获取线程id
    tid = syscall(__NR_gettid); // or syscall(SYS_gettid);

    // 对指定线程id设置CPU亲和性
    if (sched_setaffinity(tid, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }

    nrcpus = sysconf(_SC_NPROCESSORS_CONF);

    for (i = 0; i < nrcpus; i++) {
        if (CPU_ISSET(i, &mask)) {
            bitmask |= (unsigned long)0x01 << i;
            printf("processor #%d is set\n", i);
        }
    }
}

int main(int argc, char *argv[])
{
    int fun_num;
    // 根据提示输入参数
    while (1) {
        printf("Please select a program: \n");
        printf("1. get_affinity_with_s\n");
        printf("2. get_affinity_without_s\n");
        printf("3. set_process_affinity\n");
        printf("4. get_thread_affinity\n");
        printf("5. set_thread_affinity\n");
        printf("0. exit\n");
        scanf("%d", &fun_num);
        switch (fun_num) {
        case 1:
            get_affinity_with_s();
            break;
        case 2:
            get_affinity_without_s();
            break;
        case 3:
            set_process_affinity();
            break;
        case 4:
            get_thread_affinity();
            break;
        case 5:
            set_thread_affinity();
            break;
        case 0:
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Please input the correct number\n");
            break;
        }
    }
}