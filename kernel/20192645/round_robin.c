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
                printf("Process %d is running. Time: %d\n", proc[i].pid, time);
                int time_used = (proc[i].remaining_time > TIME_QUANTUM) ? TIME_QUANTUM : proc[i].remaining_time;
                time += time_used;
                proc[i].remaining_time -= time_used;
<<<<<<< Updated upstream

=======
                
>>>>>>> Stashed changes
                if (proc[i].remaining_time == 0) {
                    proc[i].completion_time = time;
                    left_processes--;
                    printf("Process %d is Terminated. Time: %d\n", proc[i].pid, time);
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

    printf("Time Quantum is %d\n", TIME_QUANTUM);
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
