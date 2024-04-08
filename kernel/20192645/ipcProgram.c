#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024
#define READ_END 0
#define WRITE_END 1

int ipcProgram() {
  char write_msg[BUFFER_SIZE] = "Greetings";
  char read_msg[BUFFER_SIZE];
  int fd[2];
  pid_t pid;
  
  if(pipe(fd) == -1) {
    fprintf(stderr, "Pipe failed");
    return 1;
  }
  
  pid = fork();
  if(pid < 0) {
    fprintf(stderr, "Fork failed");
    return 1;
  }
  if(pid == 0) {
    printf("child's pid is %d\n", getpid());
    close(fd[READ_END]);
    write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
    close(fd[WRITE_END]);
  }
  else {
    printf("parent's pid is %d\n", getpid());
    close(fd[WRITE_END]);
    read(fd[READ_END], read_msg, BUFFER_SIZE);
    printf("messege is (%s)\n", read_msg);
    close(fd[READ_END]);
  }
  return 0;
}
