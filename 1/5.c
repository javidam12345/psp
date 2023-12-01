/*
    Ejercicio mp5.c - Análisis y explicación detallada

    a) Jerarquía de procesos:
       El proceso padre crea un primer hijo y posiblemente un segundo hijo.
       El proceso padre imprime "AAA".
       El primer hijo imprime "BBB".
       El proceso padre, después de crear el primer hijo, intenta crear otro hijo.
       Si tiene éxito, hay un segundo hijo que también imprime "CCC".
       Adicionalmente, el proceso padre imprime "CCC".

       Jerarquía:
       [Proceso Padre (PID 1000)]
              | "AAA"
              +---- fork() ----> [Primer Hijo (PID 1001)]
              |                   | "BBB"
              +---- fork() ----> [Segundo Hijo (PID 1002)]
                                    | "CCC"
              | "CCC" (por el proceso padre)

    b) Salida esperada del código:
       La salida esperada será "AAA\nBBB\nCCC\nCCC\n".
       "AAA" es impreso por el proceso padre.
       "BBB" es impreso por el primer hijo.
       "CCC" es impreso por el proceso padre y el segundo hijo.

       La salida podría tener otro orden debido al paralelismo y a la planificación del sistema operativo,
       pero siempre habrá dos "CCC", uno por el padre y otro por el segundo hijo.

    c) Corrección para que los procesos padres se ejecuten al final:
       Para lograr que el proceso padre imprima su salida después de que todos sus hijos hayan terminado,
       se debe incluir una llamada a wait(NULL) después de la creación del segundo hijo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {
    pid_t pid1, pid2;

    // El proceso padre imprime "AAA"
    printf("AAA \n");

    // Se bifurca el proceso: se crea un primer proceso hijo
    pid1 = fork();

    if (pid1 == -1) {
        // En caso de error al bifurcar
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {
        // El primer hijo imprime "BBB"
        printf("BBB \n");
        exit(0); // El primer hijo termina su ejecución aquí
    } else {
        // El proceso padre crea otro proceso hijo
        pid2 = fork();

        if (pid2 == -1) {
            // En caso de error al bifurcar
            perror("fork");
            exit(1);
        }

        if (pid2 == 0) {
            // El segundo hijo imprime "CCC"
            printf("CCC \n");
            exit(0); // El segundo hijo termina su ejecución aquí
        } else {
            // El proceso padre espera al primer y segundo hijo
            wait(NULL); // Espera al primer hijo
            wait(NULL); // Espera al segundo hijo
        }

        // El proceso padre imprime "CCC"
        printf("CCC \n");
    }

    exit(0);
}
