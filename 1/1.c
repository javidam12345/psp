#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void show_name() {
    pid_t result;
    result = fork();

    if (result == 0) {
        // Proceso hijo
        printf("Mi nombre es Javier\n");
    } else {
        // Proceso padre
        wait(NULL); // Espera a que el proceso hijo termine
        printf("Proceso hijo es: %d\n", result);
        printf("Mi pid proceso padre es: %d\n", getpid());
    }
}

int main() {
    show_name();
    return 0;
}
