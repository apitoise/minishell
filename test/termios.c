#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <curses.h>

int main(void)
{
    struct termios  config;
    int             i;

    printf("FLUSH DANS 1 secondes\n");
    sleep(1);
    printf("FLUSH !\n");
    tcgetattr(STDIN_FILENO, &config);
    config.c_lflag &=  ~(ICANON);
    config.c_cc[VMIN] = 1;
    config.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &config);
    while ((i = fgetc(stdin)) != EOF)
        printf("%02X", i);
    return (EXIT_SUCCESS);
}