#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    int descriptor[2];
    char str_buffer[11];
    char buffer[BUFFER_SIZE]; // uso de signed por que solo trato con strings
    int acu = 0;
    int is_last = 0;

    if (pipe(descriptor) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t process = fork();


    if (process < 0){
        perror("fork");
        return 1;
    } else if (process == 0){
        close(descriptor[1]);
        do {
            memset(buffer, 0, BUFFER_SIZE);
            size_t amount = read(descriptor[0], buffer, BUFFER_SIZE);
            if (amount == -1) {
                perror("read");
                return 1;
            }
            if (strstr(buffer,"+")){
                is_last = 1;
            } else {
                acu += atoi(buffer);
                /*
                 * se entiende que el máximo que me pasara es INT, se entiende que no metera ninguna entero invaludo,
                 * no se controlan > MAX_INTEGER
                 * de todas formas seria preferible usar strtol
                 */
            }
        } while (!is_last);
        printf("Sum is equal to: %d", acu);
        close(descriptor[0]);
    } else {
        close(descriptor[0]);
        do {
            memset(buffer, 0, BUFFER_SIZE);
            scanf("%10s", str_buffer); // limito a 10 para evitar overflow de buffer
            write(descriptor[1],str_buffer, strlen(str_buffer) + 1);
        } while (strcmp(str_buffer,"+") != 0);
        close(descriptor[1]);
    }
    return 0;
}
