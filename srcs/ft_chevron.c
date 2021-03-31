#include "../headers/minishell.h"
#include "../libft/libft.h"

static void     single_chevron(t_struct *st, int i, int with_echo)
{
    printf("%d", with_echo);
    open(st->cmd[i + 1], O_TRUNC);
    open(st->cmd[i + 1], O_CREAT);
}

static void     double_chevron(t_struct *st, int i, int with_echo)
{
    printf("%d", with_echo);
    open(st->cmd[i + 1], O_CREAT);
}

int       ft_chevron(t_struct *st, int i)
{
    int with_echo;

    with_echo = 0;
    if (!st->cmd[i + 1])
        return printf("bash: Syntax error: new line unexpected\n");
    with_echo = 0;
    if (!(ft_strcmp(st->cmd[i], "echo")))
        with_echo = 2;
    if (!(ft_strcmp(st->cmd[i], ">")))
        single_chevron(st, i, with_echo);
    else
        double_chevron(st, i, with_echo);
    i += 2 + with_echo;
    if (st->cmd[i])
    {
        if ((!(ft_strcmp(st->cmd[i], ">"))) || (!(ft_strcmp(st->cmd[i], ">>"))))
            return ft_chevron(st, i);
    }
//    return printf("bash: %s: not found\n", st->cmd[i]);
    return (0);
}