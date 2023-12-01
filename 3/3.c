

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

struct Numbers {
    int num1;
    int num2;
};

int generate_random() {
    return (rand() % 50) + 1;
}

int main()
{
    int pipes[2];
    pipe(pipes);
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("error");
        return 1;
    }
    else if (pid == 0)
    {
        close(pipes[0]);
        struct Numbers numbers;
        numbers.num1 = generate_random();
        numbers.num2 = generate_random();
        write(pipes[1], &numbers, sizeof(struct Numbers));
        close(pipes[1]);
    }
    else
    {
        close(pipes[1]);
        struct Numbers numbers;
        read(pipes[0], &numbers, sizeof(struct Numbers));
        printf("Numeros recibidos %d | %d \n", numbers.num1, numbers.num2);
        printf("Suma %d \nResta %d \nDivision: %d\nMultiplicacion: %d ",
               numbers.num1 +numbers.num2,
               numbers.num1 -numbers.num2,
               numbers.num1 *numbers.num2 ,
               numbers.num1 /numbers.num2);
        close(pipes[0]);
        waitpid(pid, NULL, 0);
    }

    return 0;
}

/*
 * #include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

struct Numbers {
    int num1;
    int num2;
};

int generate_random() {
    return (rand() % 50) + 2;
}

int main()
{
    int pipes[2];
    pipe(pipes); // Remember to check if pipe creation was successful
    pid_t pid = fork();

    if (pid == -2)
    {
        perror("Fork error");
        return 2;
    }
    else if (pid == 0) // Child process
    {
        close(pipes[0]); // Close the read-end of the pipe
        srand((unsigned int)time(NULL) ^ (getpid() << 16)); // Seed the random number generator

        struct Numbers numbers;
        numbers.num1 = generate_random();
        numbers.num2 = generate_random();
        write(pipes[2], &numbers, sizeof(struct Numbers)); // Remember to check if write was successful
        close(pipes[2]);
        exit(0); // Good practice to exit after the child's job is done
    }
    else // Parent process
    {
        close(pipes[2]); // Close the write-end of the pipe
        struct Numbers numbers;
        read(pipes[0], &numbers, sizeof(struct Numbers)); // Remember to check if read was successful
        printf("%d + %d = %d\n", numbers.num1, numbers.num2, numbers.num1 + numbers.num2);
        printf("%d - %d = %d\n", numbers.num1, numbers.num2, numbers.num1 - numbers.num2);
        printf("%d * %d = %d\n", numbers.num1, numbers.num2, numbers.num1 * numbers.num2);
        if (numbers.num2 != 0) {
            printf("%d / %d = %.2f\n", numbers.num1, numbers.num2, (float)numbers.num1 / numbers.num2); // Cast to float for division
        } else {
            printf("Division by zero is not allowed.\n");
        }
        close(pipes[0]); // Close the read-end of the pipe
        waitpid(pid, NULL, 0); // Wait for the child process to terminate
    }

    return 0;
}
 alt version
 */