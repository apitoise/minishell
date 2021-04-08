/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:22:41 by cnotin            #+#    #+#             */
/*   Updated: 2021/04/08 13:09:47 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

static void	cmd_analysis(char **commands, t_struct *st)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		st->cmd = ft_split_cmd(commands[i], ' ');
		if (first_check(st))
			return ;
		do_chevrons(st);						
		do_builtin(st);
		if (dup2(st->stdout_copy, STDOUT_FILENO) < 0)
			return ;
		i++;
	}
<<<<<<< HEAD
	else if (!ft_strcmp(st->cmd[0], "pwd"))
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
=======
>>>>>>> arthur
}

int			main(int ac, char **av, char **env)
{
	t_struct	st;
	int			ret;
	char		*tmp;
	char		**commands;

	(void)ac;
	(void)av;
	tmp = NULL;
	commands = NULL;
	init_struct(&st, env);
	shell_init();
	while (!(st.exit))
	{
		while ((ret = get_next_line(1, &tmp)) > 0 && !(st.exit))
		{
			commands = ft_split(tmp, ';');
			cmd_analysis(commands, &st);
			shell_init();
		}
	}
	ft_free_tab(st.env);
	return (0);
}
