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
        dup2(new_pipe[1], st->stdout_fd);
        cmd = cmd_before_pipe(st->cmd, pipe_nb);
        do_builtin(cmd, st);
        dup2(new_pipe[0], st->stdin_fd);
        dup2(st->stdout_copy, st->stdout_fd);
        ft_free_tab(cmd);
        pipe_nb++;
    }
}

// void    do_pipe(t_struct *st)
// {
//     int     new_pipe[2];
//     int     pipe_nb;
//     char    **cmd;
//     pid_t   pid;

//     if (pipe(new_pipe) != 0)
//         return ;
//     pid = fork();
//     if (pid > 0)
//     {
//         close(new_pipe[1]);
//         dup2(new_pipe[0], STDOUT_FILENO);
//         cmd = cmd_before_pipe(st->cmd, 0);
//         do_builtin(cmd, st, pid);
//         ft_free_tab(cmd);
//         waitpid(pid, NULL, 0);
//     }
//     else if(pid == 0)
//     {
//         pipe_nb = 1;
//         while (pipe_nb <= st->pipe)
//         {
//             close(new_pipe[0]);
//             dup2(new_pipe[1], STDIN_FILENO);
//             cmd = cmd_before_pipe(st->cmd, pipe_nb);
//             do_builtin(cmd, st, pid);
//             ft_free_tab(cmd);
//             pipe_nb++;
//             waitpid(pid, NULL, 0);
//         }
//     }
// }