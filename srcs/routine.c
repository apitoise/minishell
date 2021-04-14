#include "../headers/minishell.h"
#include "../libft/libft.h"

void    do_routine(t_struct *st)
{
    int     err;
   // int     pipe_nb;

    err = do_chevrons(st);
	if (!err)
	{
		st->cmd = del_chevron(st);
        // if (st->pipe > 0)
        // {
        //     pipe_nb = 0;
        //     while (st->pipe > 0)
        //     {
        //         cmd = cmd_before_pipe(st->cmd);
        //         do_builtin(st);
        //     }
        // }
        // else
		    do_builtin(st->cmd, st);
	}
	if (dup2(st->stdout_copy, STDOUT_FILENO) < 0)
		return ;
	if (dup2(st->stdin_copy, STDIN_FILENO) < 0)
		return ;
}