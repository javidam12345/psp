#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void show_information() {
    pid_t current_pid = getpid();
    pid_t father_pid = getppid();
    printf("Soy el pid %d, el de mi padre es %d y la suma es %d\n", current_pid, father_pid, current_pid + father_pid);
}

int main() {
    pid_t pid2, pid3, pid4;

    // P1 crea a P2
    pid2 = fork();
    if (pid2 == -1) {
        perror("error en fork de P2");
        return 1;
    } else if (pid2 == 0) { // Estamos en P2
        // P2 crea a P3
        pid3 = fork();
        if (pid3 == -1) {
            perror("error en fork de P3");
            return 1;
        } else if (pid3 == 0) { // Estamos en P3
            // P3 crea a P4
            pid4 = fork();
            if (pid4 == -1) {
                perror("error en fork de P4");
                return 1;
            } else if (pid4 == 0) { // Estamos en P4
                // P4 muestra su información y termina
                show_information();
                exit(0);
            } else {
                // P3 espera a P4
                waitpid(pid4, NULL, 0);
                // P3 muestra su información y termina
                show_information();
                exit(0);
            }
        } else {
            // P2 espera a P3
            waitpid(pid3, NULL, 0);
            // P2 muestra su información y termina
            show_information();
            exit(0);
        }
    } else {
        // P1 espera a P2
        waitpid(pid2, NULL, 0);
        // P1 muestra su información
        show_information();
    }

    return 0;
}
