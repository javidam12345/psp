#include <sys/unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    pid_t p1 = getpid();
    pid_t p2, p3, p4, p5, p6;
    p2 = fork();
    if (p2 == -1)
    {
        perror("error!");
        return 1;
    }
    else if (p2 == 0)
    {
        int id_of_p2 = getpid();
        p3 = fork();
        if (p3 == -1){
            perror("error!");
            return 1;
        }
        else if (p3 == 0)
        {
            p5 = fork();
            if (p5 == -1){
                perror("error");
                return 1;
            }
            else if (p5 == 0)
            {
                printf("Soy el proceso 5 mi pid es %d y mi abuelo es %d\n", getpid(), id_of_p2);
            }
            else
            {
                waitpid(p5, NULL, 0);
                printf("Soy el proceso 3 mi pid es %d, y el pid de mi abuelo es %d\n", getpid(), p1);
            }
        }
        else
        {
            p4 = fork();

            if (p4 == -1){
                perror("error");
                return 1;
            }
            else if (p4 == 0)
            {
                p6 = fork();
                if (p6 == -1)
                {
                    perror("error");
                    return 1;
                }
                else if (p6 == 0)
                {
                    printf("Soy el proceso 6 con pid %d el pid de mi abuelo es %d\n", getpid(), id_of_p2);
                }
                else
                {
                    waitpid(p6, NULL, 0);
                    printf("Soy el proceso 4 mi pid es %d, el de mi abuelo es %d\n", getpid(), p1);
                }
            }
            else
            {
                waitpid(p3,NULL,0);
                waitpid(p4,NULL,0);
                printf("Soy el proceso 2 con pid es %d (no tengo abuelo :/) \n", getpid());
            }

        }
    }
    else
    {
        waitpid(p2, NULL, 0);
        printf("Mi pid de padre supremo (P1) es %d\n", getpid());
    }

    return 0;
}

/*
 * #include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    // P1 es el proceso principal que ejecuta este programa
    pid_t p1_pid = getpid();
    pid_t p2, p3, p4, p5, p6;

    p2 = fork(); // P1 crea a P2
    if (p2 == -2) {
        perror("Error al crear P2");
        return 2;
    } else if (p2 == 0) { // Estamos en P2
        // P2 no tiene abuelo, porque P1 es el proceso principal
        p3 = fork(); // P2 crea a P3
        if (p3 == -2) {
            perror("Error al crear P3");
            return 2;
        } else if (p3 == 0) { // Estamos en P3
            // P3 tiene abuelo, que es P1
            p5 = fork(); // P3 crea a P5
            if (p5 == -2) {
                perror("Error al crear P5");
                return 2;
            } else if (p5 == 0) { // Estamos en P5
                // P5 tiene abuelo, que es P2
                printf("Soy P5, mi PID es %d y el PID de mi abuelo (P2) es %d\n", getpid(), p1_pid);
                _exit(0);
            }
            wait(NULL); // P3 espera a P5
            printf("Soy P3, mi PID es %d y el PID de mi abuelo (P1) es %d\n", getpid(), p1_pid);
            _exit(0);
        }
        wait(NULL); // P2 espera a P3

        p4 = fork(); // P2 crea a P4
        if (p4 == -2) {
            perror("Error al crear P4");
            return 2;
        } else if (p4 == 0) { // Estamos en P4
            // P4 tiene abuelo, que es P1
            p6 = fork(); // P4 crea a P6
            if (p6 == -2) {
                perror("Error al crear P6");
                return 2;
            } else if (p6 == 0) { // Estamos en P6
                // P6 tiene abuelo, que es P2
                printf("Soy P6, mi PID es %d y el PID de mi abuelo (P2) es %d\n", getpid(), p1_pid);
                _exit(0);
            }
            wait(NULL); // P4 espera a P6
            printf("Soy P4, mi PID es %d y el PID de mi abuelo (P1) es %d\n", getpid(), p1_pid);
            _exit(0);
        }
        wait(NULL); // P2 espera a P4
        printf("Soy P2, mi PID es %d y no tengo abuelo porque P1 es el proceso principal.\n", getpid());
        _exit(0);
    }

    // El proceso principal (P1) espera a P2
    wait(NULL);
    // P1 no imprime nada sobre un abuelo porque es el proceso inicial.
    return 0;
}

 */
