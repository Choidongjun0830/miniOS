#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

<<<<<<< Updated upstream
typedef struct process {
=======
typedef struct process {       
>>>>>>> Stashed changes
    int pid;
    int burst_time;
    int remaining_time;
    int completion_time;
} process;

<<<<<<< Updated upstream
void rr(process proc[], int n);
=======
void rr(process proc[], int n); 
>>>>>>> Stashed changes
int execute_scheduling();

#endif // ROUND_ROBIN_H
