#include "../headers/minishell.h"
#include "../libft/libft.h"

static void     single_chevron(t_struct *st, int i)
{
    int new_fd;

    if (st->fd >= 0) {
        close(st->fd);
	}
	///!!!attention segfault
    if ((new_fd = open(st->cmd[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0)
        return ;
    close(STDOUT_FILENO);
    if (dup(new_fd) < 0) {
        return ;
	}
	close(new_fd);
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
