#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 128

int main()
{
    int pipes[2];

    if (pipe(pipes) == -1)
    {
        perror("Pipe error");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork error");
        return 1;
    }
    else if (pid == 0) // Child process
    {
        close(pipes[1]); // Close the write-end of the pipe, not needed in the child
        char buffer[BUFFER_SIZE];
        int total = 0;
        ssize_t numRead;

        while ((numRead = read(pipes[0], buffer, BUFFER_SIZE - 1)) > 0)
        {
            buffer[numRead] = '\0'; // Null terminate the string
            if (buffer[0] == '+')
            {
                break;
            }
            else
            {
                int number = (int)strtol(buffer, NULL, 10);
                printf("Numero a sumar: %d\n", number);
                total += number;
            }
        }

        if (numRead == -1)
        {
            perror("Read error");
            close(pipes[0]);
            exit(EXIT_FAILURE);
        }

        printf("La suma total es igual a: %d\n", total);
        close(pipes[0]); // Close the read-end of the pipe
    }
    else // Parent process
    {
        close(pipes[0]); // Close the read-end of the pipe, not needed in the parent
        char input[BUFFER_SIZE];

        do
        {
            printf("Introduzca un numero (o '+' para terminar): ");
            fflush(stdout);
            if (fgets(input, BUFFER_SIZE, stdin) == NULL)
            {
                printf("Fgets error");
                break;
            }

            if (write(pipes[1], input, strlen(input)) == -1)
            {
                perror("Write error");
                break;
            }
        } while (input[0] != '+');

        close(pipes[1]); // Close the write-end of the pipe to send EOF to the child
        waitpid(pid, NULL, 0); // Wait for the child process to finish
    }

    return 0;
}
