#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_p2 = fork(); // P1 crea a P2

    if (pid_p2 == -1) {
        perror("fork"); // Error al realizar fork
        return 1;
    } else if (pid_p2 == 0) {
        // Este es el proceso P2
        pid_t pid_p3 = fork(); // P2 crea a P3

        if (pid_p3 == -1) {
            perror("fork"); // Error al realizar fork
            return 1;
        } else if (pid_p3 == 0) {
            // Este es el proceso P3
            printf("Proceso P3: PID %d, PID del padre (P2) %d\n", getpid(), getppid());
            // P3 podría realizar más acciones aquí si fuera necesario
        } else {
            // P2 esperando a P3
            waitpid(pid_p3, NULL, 0);
            printf("Proceso P2: PID %d, PID del padre (P1) %d\n", getpid(), getppid());
        }
    } else {
        // P1 esperando a P2
        waitpid(pid_p2, NULL, 0);
        printf("Proceso P1: PID %d, PID del hijo (P2) %d\n", getpid(), pid_p2);
    }
    return 0;
}
