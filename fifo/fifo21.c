#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>


void fact(int *num){
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

    char *path = "fifo";

    if (access(path, F_OK) == -1)
    {
        if(mkfifo(path, 0666) == -1)
        {
            perror("fifo");
            return 1;
        }
    }

    if ((fd = open(path, O_RDONLY)) == -1)
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

    if ((fd = open(path, O_WRONLY)) == -1)
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