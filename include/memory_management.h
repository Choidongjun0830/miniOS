#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PARTITION_SIZE 4096
#define NUM_PARTITIONS 10

extern void *partitions[NUM_PARTITIONS]; // 외부 선언 추가

void init_partitions();
void *allocate_memory();
void free_memory(void *memory);
void print_partitions();

#endif
