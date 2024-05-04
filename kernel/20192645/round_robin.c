#include <stdio.h>
#include "round_robin.h"

#define MAX_PROCESSES 5
#define TIME_QUANTUM 4

void rr(process proc[], int n) {
    int time = 0;
    int left_processes = n;

    while (left_processes > 0) {
        for(int i = 0; i < n; i++) {
            if(proc[i].remaining_time > 0) {
                int time_used = (proc[i].remaining_time > TIME_QUANTUM) ? TIME_QUANTUM : proc[i].remaining_time;
                time += time_used;
                proc[i].remaining_time -= time_used;
                printf("CPU Bursting process %d for %d\n", proc[i].pid, time_used);
                if (proc[i].remaining_time == 0) {
                    proc[i].completion_time = time;
                    proc[i].turnaround_time = proc[i].completion_time;
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                    left_processes--;
                }
            }
        }
    }
}

int execute_scheduling() {
    process proc[MAX_PROCESSES] = {
        {1, 10, 10}, // PID, Burst time, Remaining time
        {2, 6, 6},
        {3, 2, 2},
        {4, 4, 4},
        {5, 8, 8}
    };

    int n = MAX_PROCESSES;

    printf("Initial State of Processes:\n");
    printf("PID\tBurst Time\t\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\n", proc[i].pid, proc[i].burst_time);
    }

    rr(proc, n);

    printf("\nPID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
    return 0;
}
