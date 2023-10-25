#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void fact(int *num){
    int res;
    int temp = *num;
    res = 1;
    while (temp > 1){
        res *= temp;
        temp--;
    }
    *num = res;
}

int main() {
    pid_t process;
    int pipe1[2];
    int pipe2[2];
    int num_from_father = 5;

    if (pipe(pipe1)){
        perror("pipe1");
        return 1;
    }
    if (pipe(pipe2)){
        perror("pipe2");
        return 1;
    }
    process = fork();

    if (process < 0){
        perror("process");
        return 1;
    } else if (process == 0){
        int num;

        num = 0;
        close(pipe1[1]);
        close(pipe2[0]);

        size_t res = read(pipe1[0],&num ,sizeof(int));
        close(pipe1[0]);
        if (res == -1){
            perror("read");
            close(pipe2[1]);
            return 1;
        } else {
            fact(&num);
            write(pipe2[1], &num,sizeof(int)); // envio directamente enteros sin convertir a string entendiendo que ambas maquinas estan en la misma arquitectura
        }
        close(pipe2[1]);
    } else {
        close(pipe1[0]);
        write(pipe1[1], &num_from_father,sizeof(int));
        close(pipe1[1]);
        int res;
        size_t read_res = read(pipe2[0], &res, sizeof(int));
        if (read_res == -1){
            perror("father_read");
            close(pipe2[0]);
            return 1;
        }
        printf("Result of father sent by child: %d",res);
        close(pipe2[0]);
    }

    return 0;
}
