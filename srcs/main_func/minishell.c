/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:56 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/31 00:56:47 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	cmd_analysis(char **commands, t_struct *st)
{
	int	i;

	i = 0;
	if (!commands[i])
		st->ret = 0;
	g_sig.cmdt = commands;
	while (commands[i])
	{
		if (commands[i])
			ft_split_cmd(commands[i], ' ', st, 0);
		if (first_check(st->cmd, st))
		{
			st->pipe = 0;
//			ft_free_tab(st->cmd);
			return ;
		}
		if (st->cmd[0])
			do_pipe(st->cmd, st);
		//ft_free_tab(st->cmd);
		i++;
	}
	ft_free_tab(commands);
	g_sig.cmdt = NULL;
}

void		minishell(t_struct *st)
{
	char	*cmdline;

	cmdline = NULL;
	shell_init();
	get_signals(st);
	while (!(st->exit))
	{
		cmdline = ft_termcap(st);
		get_signals(st);
		if (!ft_parsecmdline(&cmdline, st))
		{
			st->input = ft_split_cmdline(cmdline, ';');
			ft_freeptr((void**)&cmdline);
			cmd_analysis(st->input, st);
			st->input = NULL;
		}
		shell_init();
	}
}
