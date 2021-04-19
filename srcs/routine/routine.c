#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void        do_routine(t_struct *st)
{
    if (st->pipe > 0)
    {
        do_pipe(st);
        st->pipe = 0;
    }
    else
    {
        if (!do_chevrons(st->cmd, st))
        {
            st->cmd = del_chevron(st->cmd);
		    do_builtin(st->cmd, st);
        }
	}
	if (dup2(st->stdout_copy, STDOUT_FILENO) < 0)
		return ;
	if (dup2(st->stdin_copy, STDIN_FILENO) < 0)
		return ;
}