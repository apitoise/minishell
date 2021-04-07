#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd;

    fd = open("essai.dup", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(STDOUT_FILENO);
    if (dup(fd) < 0)
    {
        perror("dup");
        exit(EXIT_FAILURE);
    }
    close(fd);
    execlp("env", "env", NULL);
    perror("execlp");
    exit(EXIT_FAILURE);
}