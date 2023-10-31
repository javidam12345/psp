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

    if (access(path, F_OK) == -1) {
        mkfifo(path, 0666);
    }

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

    printf("received %d", res);

    return 0;
}