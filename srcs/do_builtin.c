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

static char      **ft_subtab(t_struct *st)
{
    int     i;
    int     len;
    char    **res;

    i = 0;
    while (!ft_strcmp(st->cmd[i], ">")
    || !ft_strcmp(st->cmd[i], ">>")
    || !ft_strcmp(st->cmd[i], "<"))
            i += 2;
    len = 0;
    while (st->cmd[i + len])
        len++;
    if (!(res = (char**)malloc(sizeof(char *) * (len + 1))))
        return (NULL);
    len = 0;
    while (st->cmd[i])
    {
        res[len] = ft_strdup(st->cmd[i]);
        free(st->cmd[i]);
        i++;
        len++;
    }
    return (res);
}

static int      no_builtin(t_struct *st)
{
    int i;

    i = 0;
    while (!ft_strcmp(st->cmd[i], ">")
    || !ft_strcmp(st->cmd[i], ">>")
    || !ft_strcmp(st->cmd[i], "<"))
    {
        if (!st->cmd[i + 2])
            return (1);
        else
            i += 2;
    }
    return (0);
}

void            do_builtin(t_struct *st)
{
    if (st->cmd[0] == NULL)
	{
		st->cmd[0] = ft_strdup("");
		return ;
	}
    if ((no_builtin(st)) == 1)
        return ;
    if (!ft_strcmp(st->cmd[0], ">")
    || !ft_strcmp(st->cmd[0], ">>")
    || !ft_strcmp(st->cmd[0], "<"))
        st->cmd = ft_subtab(st);
    if_builtin(st);
}