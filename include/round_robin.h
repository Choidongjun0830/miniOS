#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

typedef struct process {       
    int pid;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} process;

void rr(process proc[], int n); 

#endif // ROUND_ROBIN_H
