#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    int fd;
    int res;
    srand(time(NULL)); // set semilla
    int randomNumber = rand() % 10 + 1; // obtener ultimo elemento

    // -------- Write

    char *path = "fifo";
    if (access(path, F_OK) == -1) {
        mkfifo(path, 0666);
    }

    if ((fd = open(path, O_WRONLY)) == -1){
        perror("open");
        return 1;
    }

    int test = 7;
    if (write(fd, &test,sizeof(int)) == -1){
        perror("write");
        return 1;
    }

    if (close(fd))
    {
        perror("close");
        return 1;
    }

    // --------------- READ

    if ((fd = open(path, O_RDONLY)) == -1){
        perror("open");
        return 1;
    }

    if ((read(fd, &res, sizeof(int))) == -1){
        perror("read");
        return 1;
    }
    if (close(fd))
    {
        perror("close");
        return 1;
    }

    printf("Factorial de %d es %d", randomNumber, res);
    return 0;
}