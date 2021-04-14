#include "../headers/minishell.h"
#include "../libft/libft.h"

static void     if_builtin(char **cmd, t_struct *st)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd, &st->lst, st);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(st);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, st);
	else if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(cmd[1], st);
	else if (ft_strchr(cmd[0], '='))
		ft_export(cmd, st, 1);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, st, 2);
	else
		ft_checkpath(cmd, st);
}

void            do_builtin(char **cmd, t_struct *st)
{
    if (cmd[0] == NULL)
	{
		cmd[0] = ft_strdup("");
		return ;
	}
    if (!ft_strcmp(cmd[0], ""))
        return ;
    if_builtin(cmd, st);
}