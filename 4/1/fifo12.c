#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH1 "FIFO1"
#define PATH2 "FIFO2"

void fact(int *num){
    if (*num == 0)
    {
        *num = 1;
        return;
    }
    int res;
    int temp = *num;
    res = 1;
    while (temp > 1){
        res *= temp;
        temp--;
    }
    *num = res;
}


int main()
{
    int fd;
    int res;

    // -------- Read

    if (access(PATH1, F_OK) == -1 && access(PATH2, F_OK) == -1)
    {
        if(mkfifo(PATH1, 0666) == -1 || mkfifo(PATH2, 0666) == -1)
        {
            perror("fifo");
            return 1;
        }
    }

    if ((fd = open(PATH1, O_RDONLY)) == -1)
    {
        perror("open");
        return 1;
    }

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

    // Write ------

    if ((fd = open(PATH2, O_WRONLY)) == -1)
    {
        perror("open");
        return 1;
    }

    fact(&res);

    if (write(fd, &res,sizeof(int)) == -1)
    {
        perror("write");
        return 1;
    }

    if (close(fd))
    {
        perror("close");
        return 1;
    }

    return 0;
}