#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    srand((unsigned int)time(NULL)); // Semilla para la generación de números aleatorios

    int pipe1[2], pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Error creando los pipes");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Error en fork");
        return 1;
    }

    if (pid == 0) { // Proceso hijo P2
        close(pipe1[1]);
        close(pipe2[0]);

        int num;
        if (read(pipe1[0], &num, sizeof(num)) < 0) {
            perror("Error leyendo de pipe1");
            exit(1);
        }
        close(pipe1[0]);

        int fact_result = factorial(num);
        if (write(pipe2[1], &fact_result, sizeof(fact_result)) < 0) {
            perror("Error escribiendo en pipe2");
            exit(1);
        }
        close(pipe2[1]);
        exit(0);
    } else { // Proceso padre P1
        close(pipe1[0]);
        close(pipe2[1]);

        int num = rand() % 11;
        printf("El proceso padre genera el numero %d en el pipe1\n", num);

        if (write(pipe1[1], &num, sizeof(num)) < 0) {
            perror("Error escribiendo en pipe1");
            exit(1);
        }
        close(pipe1[1]);

        int fact_result;
        if (read(pipe2[0], &fact_result, sizeof(fact_result)) < 0) {
            perror("Error leyendo de pipe2");
            exit(1);
        }
        printf("El factorial calculado por el proceso hijo: %d! = %d\n", num, fact_result);
        close(pipe2[0]);

        wait(NULL);
    }

    return 0;
}
