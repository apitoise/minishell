#include "../headers/minishell.h"
#include "../libft/libft.h"

static void     single_chevron(t_struct *st, int i)
{
    int new_fd;

    if (st->fd >= 0)
        close(st->fd);
    if ((new_fd = open(st->cmd[i + 1], O_RDWR | O_TRUNC | O_CREAT)) < 0)
    {
        write(st->stdout_copy, "ICI\n", 4);
        return ;
    }
    ft_putnbr_fd(new_fd, st->stdout_copy);
    close(STDOUT_FILENO);
    if (dup(new_fd) < 0)
    {
        write(st->stdout_copy, "ICIPP\n", 6);
        return ;
    }
    st->fd = new_fd;
    
}

static void     double_chevron(t_struct *st, int i)
{
    int new_fd;

    if ((new_fd = open(st->cmd[i + 1], O_CREAT)) < 0)
        return ;
    close(st->fd);
    if ((st->fd = dup2(st->fd, new_fd)) < 0)
        return ;
    close(new_fd);
}

void    do_chevrons(t_struct *st)
{
    int i;

	if (st->cmd[0] == NULL)
		return;
    i = 0;
    while(st->cmd[i])
    {
        if (!ft_strcmp(st->cmd[i], ">"))
            single_chevron(st, i);
        else if (!ft_strcmp(st->cmd[i], ">>"))
            double_chevron(st, i);
        // else if (!ft_strcmp(st->cmd[i], "<"))
        //     left_chevron(st, i);
        i++;
    }
}