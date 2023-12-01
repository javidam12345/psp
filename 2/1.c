/*
 *
 * a) ¿Cuál será el orden de ejecución de los procesos? ¿Será siempre el mismo?

El orden de ejecución de los procesos dependerá del sistema operativo y de cómo planifique los procesos.
 No siempre será el mismo debido al paralelismo y la naturaleza de los procesos concurrentes.
 Sin embargo, la estructura del árbol de procesos garantizará que P1 cree a P2 y P3, y que P3 cree a P4.
 Los procesos padre esperarán a sus procesos hijo correspondientes debido a las llamadas a wait() y waitpid().
 Esto asegura que P2 terminará antes que P1, y P4 terminará antes que P3, pero P2 puede terminar antes o después que P4,
 y P3 puede terminar antes o después que P1, dependiendo de la programación del sistema operativo y de cuándo se ejecute el código exit(0) de cada proceso hijo.
 */


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void print_whatever() {
    pid_t id = getpid(); // Obtenemos el PID del proceso actual
    if (id % 2 == 0) {
        printf("Soy par y el proceso mio es %d y el de mi padre es %d\n", id, getppid());
    } else {
        printf("Soy impar y el proceso mio es %d\n", id);
    }
}

int main() {
    pid_t p2_pid = fork(); // P1 crea a P2

    if (p2_pid == -1) {
        perror("error en fork de P2");
        return 1;
    } else if (p2_pid == 0) { // Proceso P2
        print_whatever(); // P2 imprime su información
        exit(0); // Asegura que P2 termina después de imprimir su información
    } else {
        pid_t p3_pid = fork(); // P1 crea a P3
        if (p3_pid == -1) {
            perror("error en fork de P3");
            return 1;
        } else if (p3_pid == 0) { // Proceso P3
            pid_t p4_pid = fork(); // P3 crea a P4
            if (p4_pid == -1) {
                perror("error en fork de P4");
                return 1;
            } else if (p4_pid == 0) { // Proceso P4
                print_whatever(); // P4 imprime su información
                exit(0); // Asegura que P4 termina después de imprimir su información
            } else {
                wait(NULL); // P3 espera a P4
                print_whatever(); // P3 imprime su información
                exit(0); // Asegura que P3 termina después de imprimir su información y esperar a P4
            }
        } else {
            waitpid(p2_pid, NULL, 0); // P1 espera a P2
            waitpid(p3_pid, NULL, 0); // P1 espera a P3
            print_whatever(); // P1 imprime su información
        }
    }
    return 0;
}

