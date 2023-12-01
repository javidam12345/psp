#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 128

int main(){

    int fds[2];
    if (pipe(fds) == -1)
    {
        perror("Error creating pipes");
        return 1;
    }
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork error");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        char buffer[BUFFER_SIZE];
        close(fds[1]); // Close unused write end

        ssize_t num_bytes = read(fds[0], buffer, BUFFER_SIZE - 1);
        if (num_bytes > 0)
        {
            buffer[num_bytes] = '\0'; // Null-terminate the string
            printf("Soy el proceso hijo con pid %d\n", getpid());
            printf("Fecha/hora: %s", buffer);
        }
        else
        {
            perror("Read error");
        }

        close(fds[0]); // Close read end
    }
    else
    {
        // Parent process
        close(fds[0]); // Close unused read end

        time_t hour;
        time(&hour);
        char *date = ctime(&hour);

        write(fds[1], date, strlen(date) + 1);
        close(fds[1]); // Close write end

        wait(NULL); // Wait for child process to finish
    }

    return 0;
}
