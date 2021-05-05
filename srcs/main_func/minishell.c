/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:56 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/19 15:25:57 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void cmd_analysis(char **commands, t_struct *st)
{
	int	i;

	i = 0;
	if (!commands[i])
		st->ret = 0;
	while (commands[i])
	{
		st->cmd = ft_split_cmd(commands[i], ' ', st);
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

void        minishell(t_struct *st)
{
    char    **commands;
    char    *tmp;
	int		ret;

    commands = NULL;
    tmp = NULL;
    shell_init();
	get_signals(st);
	while (!(st->exit))
	{
		while ((ret = get_next_line(1, &tmp)) > 0 && !(st->exit))
		{
			get_signals(st);
			if (!ft_parsecmdline(&tmp, st))
			{
				commands = ft_split_cmdline(tmp, ';');
				cmd_analysis(commands, st);
				ft_free_tab(commands);
				free(tmp);
			}
			shell_init();
		}
	}
}
