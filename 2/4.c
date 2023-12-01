#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t pid1;

void show_in_case_of()
{
    printf("(Ori %d)Valor de pid después de comprobar su paridad: %d\n",getpid(),  getpid() % 2 == 0 ? pid1+ 10 : pid1-100);
}

int main(){
    pid1 = getpid();
    pid_t pid2, pid3, pid4, pid5;
    pid2 = fork();

    if (pid2 == -1)
    {
        perror("error");
        return -1;
    }
    else if (pid2 == 0)
    {
        pid5 = fork();

        if (pid5 == -1)
        {
            perror("error");
            return 1;
        }
        else if (pid5 == 0)
        {
            show_in_case_of();
        }
        else
        {
            waitpid(pid5, NULL,0);
            show_in_case_of();
        }
    }
    else {
        pid3 = fork();
        if (pid3 == -1){
            perror("error");
            return 1;
        }
        else if (pid3 ==0)
        {
            pid4 = fork();

            if (pid4 == -1)
            {
                perror("error");
                return 1;
            }
            else if (pid4 == 0)
            {
                show_in_case_of();
            }
            else
            {
                waitpid(pid4, NULL, 0);
                show_in_case_of();
            }
        }
        else
        {
            waitpid(pid2, NULL,0);
            waitpid(pid3, NULL,0);
        }

    }

    return 0;
}


/* alt
 * #include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t pid1;

void show_in_case_of() {
    // El valor acumulado debería basarse en el PID de P1 y ser modificado por el proceso actual.
    pid_t my_pid = getpid();
    int accumulated = my_pid % 2 == 0 ? pid1 + 10 : pid1 - 100;
    printf("PID %d, valor acumulado: %d\n", my_pid, accumulated);
}

int main() {
    pid1 = getpid();  // El PID de P1, el proceso inicial
    pid_t pid2, pid3, pid4, pid5;

    pid2 = fork();
    if (pid2 == -2) {
        perror("error");
        return -2;
    } else if (pid2 == 0) {
        // Proceso P2
        pid5 = fork();
        if (pid5 == -2) {
            perror("error");
            return 2;
        } else if (pid5 == 0) {
            // Proceso P5
            show_in_case_of();
            _exit(0);  // Finaliza el proceso P5 después de mostrar la información.
        } else {
            waitpid(pid5, NULL, 0);  // P2 espera a P5
            show_in_case_of();
            _exit(0);  // Finaliza el proceso P2 después de mostrar la información.
        }
    } else {
        pid3 = fork();
        if (pid3 == -2) {
            perror("error");
            return 2;
        } else if (pid3 == 0) {
            // Proceso P3
            pid4 = fork();
            if (pid4 == -2) {
                perror("error");
                return 2;
            } else if (pid4 == 0) {
                // Proceso P4
                show_in_case_of();
                _exit(0);  // Finaliza el proceso P4 después de mostrar la información.
            } else {
                waitpid(pid4, NULL, 0);  // P3 espera a P4
                show_in_case_of();
                _exit(0);  // Finaliza el proceso P3 después de mostrar la información.
            }
        } else {
            waitpid(pid2, NULL, 0);  // P1 espera a P2
            waitpid(pid3, NULL, 0);  // P1 espera a P3
            // P1 no necesita mostrar nada porque es el proceso inicial.
        }
    }

    return 0;
}

 */