#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PARTITION_SIZE 4096
#define MAX_MEM_BLOCKS 10

typedef struct {
    void *addr; 
    size_t size;
    int id; //id
    int in_use_flag; //사용중
} MemoryBlock;

extern void *partitions[MAX_MEM_BLOCKS]; // 외부 선언 추가

void init_partitions();
void* fixed_allocate_memory();
void fixed_free_memory(void *memory);
void print_memory_blocks();
int dyna_alloc_ret_id(size_t size);
void dyna_free(int free_id);

#endif