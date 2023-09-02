/* SPDX-License-Identifier: GPL-2.0 */
#include "lattester.h"
#include "memaccess.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct timespec tstart, tend;
unsigned int c_store_start_hi, c_store_start_lo;
unsigned int c_ntload_start_hi, c_ntload_start_lo;
unsigned int c_ntload_end_hi, c_ntload_end_lo;
unsigned long c_store_start;
unsigned long c_ntload_start, c_ntload_end;
long pages, diff;

#define LFS_PERMRAND_ENTRIES 0x1000
uint32_t *lfs_random_array;
#define RAW_BEFORE_WRITE                                                                                               \
    clock_gettime(CLOCK_MONOTONIC_RAW, &tstart);                                                                       \
    asm volatile("rdtscp \n\t"                                                                                         \
                 "lfence \n\t"                                                                                         \
                 "mov %%edx, %[hi]\n\t"                                                                                \
                 "mov %%eax, %[lo]\n\t"                                                                                \
                 : [hi] "=r"(c_store_start_hi), [lo] "=r"(c_store_start_lo)                                            \
                 :                                                                                                     \
                 : "rdx", "rax", "rcx");
#define RAW_BEFORE_READ                                                                                                \
    asm volatile("rdtscp \n\t"                                                                                         \
                 "lfence \n\t"                                                                                         \
                 "mov %%edx, %[hi]\n\t"                                                                                \
                 "mov %%eax, %[lo]\n\t"                                                                                \
                 : [hi] "=r"(c_ntload_start_hi), [lo] "=r"(c_ntload_start_lo)                                          \
                 :                                                                                                     \
                 : "rdx", "rax", "rcx");
#define RAW_FINAL(job_name)                                                                                            \
    asm volatile("rdtscp \n\t"                                                                                         \
                 "lfence \n\t"                                                                                         \
                 "mov %%edx, %[hi]\n\t"                                                                                \
                 "mov %%eax, %[lo]\n\t"                                                                                \
                 : [hi] "=r"(c_ntload_end_hi), [lo] "=r"(c_ntload_end_lo)                                              \
                 :                                                                                                     \
                 : "rdx", "rax", "rcx");                                                                               \
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &tend) == 0) {                                                              \
        diff = (tend.tv_sec - tstart.tv_sec) * 1e9 + tend.tv_nsec - tstart.tv_nsec;                                    \
    }                                                                                                                  \
    c_store_start = (((unsigned long)c_store_start_hi) << 32) | c_store_start_lo;                                      \
    c_ntload_start = (((unsigned long)c_ntload_start_hi) << 32) | c_ntload_start_lo;                                   \
    c_ntload_end = (((unsigned long)c_ntload_end_hi) << 32) | c_ntload_end_lo;

int main() {
    int i;
    long long aggregated = 0, aggregated2 = 0;
    long seed = 0xdeadbeef1245678;
    uint64_t a = 0xfc0;
    int access_size = 64;
    int stride_size = 64;
    int delay = 64;
    int count = 32;
    for (i = 0; i < 100000; i++) {
        char *buf = malloc(4096 * 1024);
        buf = buf + 64 - (((long)buf) % 64);
        RAW_BEFORE_WRITE
        sizebw_store(buf, access_size, count, &seed, a);
        asm volatile("mfence \n" :::);
        RAW_FINAL("sizebw_store")
        aggregated += diff;
        aggregated2 += c_ntload_end - c_store_start;
    }

    printf("sizebw_store aggregated %lld %lld\n", aggregated / 100000 / count, aggregated2 / 100000 / count);
    aggregated = 0;
    aggregated2 = 0;
    for (i = 0; i < 100000; i++) {
        char *buf = malloc(4096 * 1024);
        buf = buf + 64 - (((long)buf) % 64);
        RAW_BEFORE_WRITE
        sizebw_load(buf, access_size, count, &seed, a);
        asm volatile("mfence \n" :::);
        RAW_FINAL("sizebw_load")
        aggregated += diff;
        aggregated2 += c_ntload_end - c_store_start;
    }
    printf("sizebw_load aggregated %lld %lld\n", aggregated / 100000 / count, aggregated2 / 100000 / count);
    aggregated = 0;
    aggregated2 = 0;

    for (i = 0; i < 100000; i++) {
        char *buf = malloc(4096 * 1024);
        buf = buf + 64 - (((long)buf) % 64);
        RAW_BEFORE_WRITE
        sizebw_storeclwb(buf, access_size, count, &seed, a);
        asm volatile("mfence \n" :::);
        RAW_FINAL("sizebw_storeclwb")
        aggregated += diff;
        aggregated2 += c_ntload_end - c_store_start;
    }
    printf("sizebw_storeclwb aggregated %lld %lld\n", aggregated / 100000 / count, aggregated2 / 100000 / count);
    aggregated = 0;
    aggregated2 = 0;
    for (i = 0; i < 100000; i++) {
        char *buf = malloc(4096 * 1024);
        buf = buf + 64 - (((long)buf) % 64);
        RAW_BEFORE_WRITE
        sizebw_nt(buf, access_size, count, &seed, a);
        asm volatile("mfence \n" :::);
        RAW_FINAL("sizebw_nt")
        aggregated += diff;
        aggregated2 += c_ntload_end - c_store_start;
    }
    printf("sizebw_nt aggregated %lld %lld\n", aggregated / 100000 / count, aggregated2 / 100000 / count);
    return 0;
}
