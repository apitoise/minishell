#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int     main()
{
    int     fd1[2];
    unsigned char    buff[256];
    int     i;

    if (pipe(fd1) != 0)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 256; i++)
        buff[i] = i;
    if (write(fd1[1], buff, 256) != 256)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }
    if (read(fd1[0], buff, 256) != 256)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 256; i++)
    {
        if (buff[i] != i)
        {
            printf("Error: i = %d, buff[i] = %d\n", i, buff[i]);
            exit(EXIT_FAILURE);
        }
    }
        printf("OK\n");
    return EXIT_SUCCESS;
}