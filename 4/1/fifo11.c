#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

#define PATH1 "FIFO1"
#define PATH2 "FIFO2"

int main()
{

    int fd;
    srand(time(NULL)); // set semilla
    int random_number = rand() % 10 + 1; // obtener ultimo elemento

    // write

    if (access(PATH1, F_OK) == -1 && access(PATH2, F_OK) == -1)
    {
        if(mkfifo(PATH1, 0666) == -1 || mkfifo(PATH2, 0666) == -1)
        {
            perror("fifo");
            return 1;
        }
    }

    if ((fd = open(PATH1, O_WRONLY)) == -1)
    {
        perror("open");
        return 1;
    }

    if (write(fd, &random_number,sizeof(int)) == -1)
    {
        perror("write");
        return 1;
    }

    if (close(fd))
    {
        perror("close");
        return 1;
    }

    // read

    if ((fd = open(PATH2, O_RDONLY)) == -1)
    {
        perror("open");
        return 1;
    }

    int res;

    if ((read(fd, &res, sizeof(int))) == -1)
    {
        perror("read");
        return 1;
    }

    if (close(fd))
    {
        perror("close");
        return 1;
    }

    printf("Result of factorial of %d -> %d", random_number, res);
    unlink(PATH1);
    unlink(PATH2);
    return 0;
}
