#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

char calculate_nif_letter(int dni) {
    char letters[] = "TRWAGMYFPDXBNJZSQVHLCKE";
    return letters[dni % 23];
}

int main() {
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
        close(pipe1[0]);
        close(pipe2[1]);

        int dni;
        printf("Introduce el número de tu DNI: ");
        scanf("%d", &dni);

        if (write(pipe1[1], &dni, sizeof(dni)) < 0) {
            perror("Error escribiendo en pipe1");
            exit(1);
        }
        close(pipe1[1]);

        char nif_letter;
        if (read(pipe2[0], &nif_letter, sizeof(nif_letter)) < 0) {
            perror("Error leyendo de pipe2");
            exit(1);
        }
        close(pipe2[0]);

        printf("La letra del NIF es: %c\n", nif_letter);
    } else { // Proceso padre P1
        close(pipe1[1]);
        close(pipe2[0]);

        int dni;
        if (read(pipe1[0], &dni, sizeof(dni)) < 0) {
            perror("Error leyendo de pipe1");
            exit(1);
        }
        close(pipe1[0]);

        char nif_letter = calculate_nif_letter(dni);
        if (write(pipe2[1], &nif_letter, sizeof(nif_letter)) < 0) {
            perror("Error escribiendo en pipe2");
            exit(1);
        }
        close(pipe2[1]);

        wait(NULL);
    }

    return 0;
}
