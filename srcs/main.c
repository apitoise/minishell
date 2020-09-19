/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:22:41 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 19:31:00 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

int		isok(t_struct *st, char *str)
{
	int		i;
	int		len;

	len = ft_strlen(str);
	i = ft_strlen(st->s) - 1;
	if (i == len)
		return (0);
	if (i > len && (st->s[len + 1] != '\n'
		|| st->s[len + 1] != ' ' || st->s[len + 1] != '\0'))
		return (1);
	else
		return (0);
}

void	if_builtin(t_struct *st)
{
	if (st->cmd[0] == NULL)
	{
		st->cmd[0] = ft_strdup("");
		return;
	}
	else if (!ft_strcmp(st->cmd[0], "pwd"))
		ft_pwd(st->cmd);
	else if (!ft_strcmp(st->cmd[0], "echo"))
		ft_echo(st->cmd, &st->lst, st);
	else if (!ft_strcmp(st->cmd[0], "exit"))
		ft_exit(st->cmd);
	else if (!ft_strcmp(st->cmd[0], "env"))
		ft_env(st->env);
	else if (!ft_strcmp(st->cmd[0], "unset"))
		ft_unset(st);
	else if (!ft_strcmp(st->cmd[0], "cd"))
		ft_cd(st->cmd[1], st);
	else if (ft_strchr(st->cmd[0], '='))
		ft_export(st, 1);
	else if (!ft_strcmp(st->cmd[0], "export"))
		ft_export(st, 2);
	else
		not_cmd(st->cmd[0], st);
}

int		main(int ac, char **av, char **env)
{
	t_struct	st;
	int			ret;
	char		*tmp;

	(void)ac;
	(void)av;
	tmp = NULL;
	init_struct(&st, env);
	shell_init();
	while (!(st.exit))
	{
		while ((ret = get_next_line(1, &tmp)) > 0 && !(st.exit))
		{
			st.cmd = ft_split(tmp, ' ');
			if_builtin(&st);
			shell_init();
		}
	}
	ft_free_tab(st.env);
	return (0);
}


