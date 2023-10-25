#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    pid_t process;
    int descriptor[2];
    size_t readBytes;
    unsigned char buffer[BUFFER_SIZE];

    if (pipe(descriptor) == -1) {
        perror("pipe");
        return 1;
    }

    process = fork();
    if (process < 0) {
        perror("fork");
        return 1;
    }

    if (process == 0) {
        pid_t current_pid = getpid();
        printf("I'm child process with pid: %d\n", current_pid);
        close(descriptor[1]);
        do {
            memset(buffer, 0, BUFFER_SIZE);  // Limpiar el buffer
            readBytes = read(descriptor[0], buffer, BUFFER_SIZE - 1);
            if (readBytes > 0) {
                printf("%s", buffer);
            }
        } while (readBytes > 0);
        close(descriptor[0]);
    } else {
        close(descriptor[0]);
        time_t t;
        time(&t);
        char *date = ctime(&t);
        write(descriptor[1], date, strlen(date) + 1);
        close(descriptor[1]);
    }

    return 0;
}
