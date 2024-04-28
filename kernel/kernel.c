#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "system.h"
#include "forkProgram.h"
#include "ipcProgram.h"
#include "calculate_pi.h"
#include "memory_management.h"

void print_minios(char* str);

int main() {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;
    init_partitions();

    while(1) {
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");

        if (strcmp(input,"exit") == 0) {
            break;
        }

        if (strcmp(input,"minisystem") == 0){
            minisystem();
        }
        else if (strcmp(input,"userInfo") == 0){
            userInfo();
        }
        else if (strcmp(input,"forkProgram") == 0){
            forkProgram();
        }
        else if (strcmp(input,"ipcProgram") == 0) {
            ipcProgram();
        }
	    else if (strcmp(input,"montecarlo") == 0) {
	        montecarlo();
	    }
        else if (strcmp(input,"fixed allocate") == 0) {
            void *mem = allocate_memory(); //allocate한 mem 주소 list?
            if (mem != NULL) {
                printf("Memory allocated at %p\n", mem);
            }
        }
        else if (strcmp(input,"fixed free") == 0) {
            printf("Enter memory address to free: ");
            void *addr;
            scanf("%p", &addr);
            free_memory(addr);
        }
        else if (strcmp(input, "print partitions") == 0) {
            print_partitions();
        }
        else if (strcmp(input,"fixed_memory") == 0) {
            fixedsize_memory_management();
        }
        else system(input);
    }

    // 메모리 해제
    free(input);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
