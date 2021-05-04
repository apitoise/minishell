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
	while (commands[i])
	{
		st->cmd = ft_split_cmd(commands[i], ' ', st);
		if (first_check(st->cmd, st))
			return ;
		do_routine(st);
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
	while (!(st->exit))
	{
		signal(SIGQUIT, ctrl_backslash);
		signal(SIGINT, ctrl_c);
		if (sig.sig_ret != 0)
			st->ret = sig.sig_ret;
		while ((ret = get_next_line(1, &tmp)) > 0 && !(st->exit))
		{
			get_history(tmp, &st->history);
			if (!ft_parsecmdline(&tmp, st))
			{
				commands = ft_split_cmdline(tmp, ';');
				cmd_analysis(commands, st);
			}
			shell_init();
		}
	}
}
