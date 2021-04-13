#include "../headers/minishell.h"
#include "../libft/libft.h"

static void     single_chevron(t_struct *st, int i)
{
    int new_fd;

    if (st->stdout_fd >= 0)
        close(st->stdout_fd);
    if ((new_fd = open(st->cmd[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0)
        return ;
    close(STDOUT_FILENO);
    if (dup(new_fd) < 0)
        return ;
    st->stdout_fd = new_fd;
	close(new_fd);
}

static void     double_chevron(t_struct *st, int i)
{
    int new_fd;

    if (st->stdout_fd >= 0) 
        close(st->stdout_fd);
    if ((new_fd = open(st->cmd[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0666)) < 0)
        return ;
    close(STDOUT_FILENO);
    if (dup(new_fd) < 0)
        return ;
    st->stdout_fd = new_fd;
	close(new_fd);
}

static int     left_chevron(t_struct *st, int i)
{
    int new_fd;

    if (st->stdin_fd >= 0)
        close(st->stdin_fd);
    if ((new_fd = open(st->cmd[i + 1], O_RDONLY, 0666)) < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(st->cmd[i + 1], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (1);
    }
    close(STDIN_FILENO);
    if (dup(new_fd) < 0)
        return (0);
    st->stdin_fd = new_fd;
    close(new_fd);
    return (0);
}

int    do_chevrons(t_struct *st)
{
    int i;
    int err;

	if (st->cmd[0] == NULL)
		return (0);
    i = 0;
    err = 0;
    while(st->cmd[i] && err == 0)
    {
        if (!ft_strcmp(st->cmd[i], ">"))
            single_chevron(st, i);
        else if (!ft_strcmp(st->cmd[i], ">>"))
            double_chevron(st, i);
        else if (!ft_strcmp(st->cmd[i], "<"))
            err = left_chevron(st, i);
        i++;
    }
    return (err);
}
