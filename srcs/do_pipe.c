#include "../headers/minishell.h"
#include "../libft/libft.h"

static char **cmd_before_pipe(char **cmd, int pipe_nb)
{
    char    **res;
    int     i;
    int     save;
    int     j;

    i = 0;
    while (pipe_nb > 0 && cmd[i])
    {
        if (!ft_strcmp(cmd[i], "|"))
            pipe_nb--;
        i++;
    }
    save = i;
    while (cmd[i] && ft_strcmp(cmd[i], "|"))
        i++;
    if (!(res = (char **)malloc(sizeof(char *) * (i - save + 1))))
        return (NULL);
    j = 0;
    while (cmd[save] && ft_strcmp(cmd[save], "|"))
    {
        res[j] = ft_strdup(cmd[save]);
        save++;
        j++;
    }
    res[j] = NULL;
    return (res);
}

void    do_pipe(t_struct *st)
{
    int     new_pipe[2];
    int     pipe_nb;
    char    **cmd;

    if (pipe(new_pipe) != 0)
        return ;
    pipe_nb = 0;
    while (pipe_nb <= st->pipe)
    {
        st->stdout_fd = new_pipe[1];
        cmd = cmd_before_pipe(st->cmd, pipe_nb);
        if (!do_chevrons(cmd, st))
        {
            cmd = del_chevron(cmd);
            do_builtin(cmd, st);
            dup2(new_pipe[0], st->stdin_fd);
            dup2(st->stdout_copy, st->stdout_fd);
        }
        ft_free_tab(cmd);
        pipe_nb++;
    }
}