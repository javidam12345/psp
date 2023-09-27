#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid; 
  
    pid = fork();

    if (pid == 0) {
        printf("Javier Aragoneses\n"); 
    } 
    else {
        wait(NULL);  
        
        printf("PID del proceso hijo: %d\n", pid);
        printf("PID del proceso padre: %d\n", getpid());
    }

    return 0;
}
