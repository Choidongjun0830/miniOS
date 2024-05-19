#include <stdio.h>
#include <stdlib.h>
#include "memory_management.h"  // 이 파일에는 dyna_alloc 및 dyna_free 함수가 정의되어 있어야 합니다.
#include "scheduling.h"

void round_robin(Process *processes, int num_processes, int quantum) {
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < num_processes) {
        for (int i = 0; i < num_processes; ++i) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].mem_block_id == 0) {  // 메모리 할당 시도
                    processes[i].mem_block_id = dyna_alloc(processes[i].size, processes[i]);
                    if (processes[i].mem_block_id == -1) {
                        printf("Memory allocation failed for Process %d\n", processes[i].pid);
                        continue;  // 메모리 할당 실패시 다음 기회에 시도
                    }
                }
                print_memory_blocks();
                int execute_time = (processes[i].remaining_time > quantum) ? quantum : processes[i].remaining_time;
                printf(" P%d ", processes[i].pid);
                for (int j = 0; j < execute_time; ++j)
                    printf("||");

                printf("(%ds)", current_time + execute_time);
                current_time += execute_time;
                processes[i].remaining_time -= execute_time;

                if (processes[i].remaining_time == 0) {
                    printf("completed");
                    processes[i].completion_time = current_time;
                    completed_processes++;
                    dyna_free(processes[i].mem_block_id);  // 메모리 해제
                }
                printf("\n");
            }
        }
    }
}

int schedule() {
    int num_processes;
    int quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    Process *processes = (Process *)malloc(num_processes * sizeof(Process));

    printf("Enter process details:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d:\n", i + 1);
        printf("PID: ");
        scanf("%d", &processes[i].pid);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        printf("Process Size: ");
        scanf("%zu", &processes[i].size);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].mem_block_id = 0;  // 초기 메모리 할당 ID는 0 (미할당 상태)
    }

    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    round_robin(processes, num_processes, quantum);

    free(processes);
    return 0;
}