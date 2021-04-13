#include "../headers/minishell.h"
#include "../libft/libft.h"

static void     if_builtin(t_struct *st)
{
	if (!ft_strcmp(st->cmd[0], "pwd"))
		ft_pwd(st->cmd);
	else if (!ft_strcmp(st->cmd[0], "echo"))
		ft_echo(st->cmd, &st->lst, st);
	else if (!ft_strcmp(st->cmd[0], "exit"))
		ft_exit(st->cmd);
	else if (!ft_strcmp(st->cmd[0], "env"))
		ft_env(st);
	else if (!ft_strcmp(st->cmd[0], "unset"))
		ft_unset(st);
	else if (!ft_strcmp(st->cmd[0], "cd"))
		ft_cd(st->cmd[1], st);
	else if (ft_strchr(st->cmd[0], '='))
		ft_export(st, 1);
	else if (!ft_strcmp(st->cmd[0], "export"))
		ft_export(st, 2);
	else
		ft_checkpath(st);
}

void            do_builtin(t_struct *st)
{
    if (st->cmd[0] == NULL)
	{
		st->cmd[0] = ft_strdup("");
		return ;
	}
    if (!ft_strcmp(st->cmd[0], ""))
        return ;
    if_builtin(st);
}