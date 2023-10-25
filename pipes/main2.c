#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int descriptor[2];
    char str_buffer[11];
    unsigned char buffer[BUFFER_SIZE];
    size_t read_bytes;

    pid_t process = fork();
    if (pipe(descriptor) == -1) {
        perror("pipe");
        return 1;
    }

    if (process < 0){
        perror("fork");
        return 1;
    } else if (process){
        close(descriptor[1]);
        do {
            memset(buffer, 0, BUFFER_SIZE);
            read_bytes = read(descriptor[0],buffer,BUFFER_SIZE);

        } while (read_bytes > 0);
        close(descriptor[0]);
    } else {
        while (){
            memset(buffer, 0, BUFFER_SIZE);

            scanf("%s", str_buffer);
        }
        close(descriptor[0]);
    }
    return 0;
}
