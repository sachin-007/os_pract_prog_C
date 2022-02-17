#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
 
#define STACK_SIZE (1024 * 1024)
 
static char child_stack[STACK_SIZE];
char* const child_args[] = {
     "/bin/bash",
     NULL
};
 
int child_main(void* args) {
           printf("In the child process!\n");
     execv(child_args[0], child_args);
     return 1;
}
 
int main(){
           printf("Program start:\n");
     int child_pid = clone(child_main, child_stack + STACK_SIZE, SIGCHLD, NULL);
     waitpid(child_pid, NULL, 0);
           printf("Exited\n");
     return 0;
}
/*Output
[root@mast ~]#  gcc -Wall uts.c -o uts.o && ./uts.o
 The program starts:
 In the child process!
[root@mast ~]# exit*/

