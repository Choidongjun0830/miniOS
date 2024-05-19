#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int priority;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int completion_time;
    int mem_block_id;  // 할당된 메모리 블록 ID
    size_t size;
} Process;

Process createDefaultProcess() {
    Process p = {
        .pid = 0,
        .priority = 0,
        .burst_time = 0,
        .remaining_time = 0,
        .arrival_time = 0,
        .completion_time = 0,
        .mem_block_id = -1,  // 예: -1로 초기화하여 메모리 블록 ID가 아직 할당되지 않았음을 표시
        .size = 0
    };
    return p;
}

void round_robin(Process *processes, int num_processes, int quantum);
int schedule();

#endif