#include "../headers/minishell.h"
#include "../libft/libft.h"

void        do_routine(t_struct *st)
{
    int     err;

    err = do_chevrons(st);
	if (!err)
	{
		st->cmd = del_chevron(st);
        if (st->pipe > 0)
            do_pipe(st);
        else
		    do_builtin(st->cmd, st, -1);
	}
	if (dup2(st->stdout_copy, STDOUT_FILENO) < 0)
		return ;
	if (dup2(st->stdin_copy, STDIN_FILENO) < 0)
		return ;
}