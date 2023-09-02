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
    c_ntload_end = (((unsigned long)c_ntload_end_hi) << 32) | c_ntload_end_lo;                                         \
    printf("[%s] count %ld total %ld ns, average %ld ns, cycle %ld - %ld - %ld.\n", #job_name, count, diff,            \
           diff / count, c_store_start, c_ntload_start, c_ntload_end);

int main() {
    char *buf = malloc(4096 * 1024);
    buf = buf + 64 - (((long)buf) % 64);
    int i;
    long seed = 0xdeadbeef1245678;
    uint64_t a = 0xfc0;
    int access_size = 64;
    int stride_size = 64;
    int delay = 64;
    int count = 32;

    //     for (i = 0; i < 8; i++) {
    //         buf[i] = 'a';
    //     }

    // RAW_BEFORE_WRITE
    // RAW_BEFORE_READ
    // seq(buf, access_size, stride_size, 0, count);
    // asm volatile("mfence \n" :::);
    // RAW_FINAL("raw-combined")

    //     RAW_BEFORE_WRITE
    //     RAW_BEFORE_READ
    //     stride_storeclwb(buf, access_size, stride_size, 0, count);
    //     asm volatile("mfence \n" :::);
    //     RAW_FINAL("raw-combined")

    // RAW_BEFORE_WRITE
    // RAW_BEFORE_READ
    // stride_load(buf, access_size, stride_size, 0, count);
    // asm volatile("mfence \n" :::);
    // RAW_FINAL("raw-combined")

    //     sizebw_nt(buf, 64, 128, &seed, a);
    //     stride_nt(buf, 64, 0, delay, count);

    //     RAW_BEFORE_WRITE
    //     RAW_BEFORE_READ
    //    sizebw_nt(buf, 64, 128, &seed,  a);
    //        asm volatile("mfence \n" :::);
    //     RAW_FINAL("raw-combined")

    RAW_BEFORE_WRITE
    RAW_BEFORE_READ
    sizebw_store(buf, access_size, count, &seed, a);
    asm volatile("mfence \n" :::);
    RAW_FINAL("raw-combined")
    return 0;
}
