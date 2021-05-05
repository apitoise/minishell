/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:56 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/04 13:09:16 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void cmd_analysis(char **commands, t_struct *st)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		st->cmd = ft_split_cmd(commands[i], ' ', st);
		if (first_check(st->cmd))
			return ;
		do_routine(st);
		i++;
	}
}

void        minishell(t_struct *st)
{
	char    **commands;
	char    *cmdline;

	commands = NULL;
	cmdline = NULL;
	shell_init();
	while (!(st->exit))
	{
		cmdline = getcmdline(st);
		if (!ft_parsecmdline(&cmdline, st))
		{
			commands = ft_split_cmdline(cmdline, ';');
			cmd_analysis(commands, st);
		}
		shell_init();
	}
    ft_free_tab(st->env);
}
