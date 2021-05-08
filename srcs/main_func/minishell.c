/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:56 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/09 00:20:54 by lgimenez         ###   ########.fr       */
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
	while (commands[i])
	{
		st->cmd = ft_split_cmd(commands[i], ' ', st);
		free(commands[i]);
		if (first_check(st->cmd, st))
		{
			st->pipe = 0;
			ft_free_tab(st->cmd);
			return ;
		}
		do_routine(st);
		ft_free_tab(st->cmd);
		i++;
	}
}

void		minishell(t_struct *st)
{
	char	*cmdline;

	cmdline = NULL;
	shell_init();
	get_signals(st);
	while (!(st->exit))
	{
		cmdline = getcmdline(st);
		get_signals(st);
		if (!ft_parsecmdline(&cmdline, st))
		{
			st->input = ft_split_cmdline(cmdline, ';');
			free(cmdline);
			cmd_analysis(st->input, st);
			free(st->input);
		}
		shell_init();
	}
}
