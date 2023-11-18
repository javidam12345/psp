#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    pid_t pid_p2, pid_p3;

    pid_p2 = fork(); // P1 crea a P2

    if (pid_p2 == -1) {
        perror("Error en fork para P2");
        return 1;
    } else if (pid_p2 == 0) {
        // Este es P2
        sleep(10); // P2 duerme por 10 segundos
        printf("Soy el proceso P2, despierto!\n");
    } else {
        // En P1 después de crear a P2
        pid_p3 = fork(); // P1 crea a P3

        if (pid_p3 == -1) {
            perror("Error en fork para P3");
            return 1;
        } else if (pid_p3 == 0) {
            // Este es P3
            printf("Soy el proceso P3 btw. Mi PID es %d y el de mi padre es %d\n", getpid(), getppid());
        } else {
            // En P1, esperando primero a P2 y luego a P3
            waitpid(pid_p2, NULL, 0); // Espera específicamente por P2
            waitpid(pid_p3, NULL, 0); // Espera específicamente por P3
            printf("Soy el proceso P1, todos mis hijos han terminado.\n");
        }
    }
    return 0;
}
