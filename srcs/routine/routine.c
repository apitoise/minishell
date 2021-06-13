/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:13 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/13 19:04:56 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	reset_fd(t_struct *st)
{
	if (dup2(st->stdout_copy, STDOUT_FILENO) < 0)
		return ;
	if (dup2(st->stdin_copy, STDIN_FILENO) < 0)
		return ;
}

void	do_routine(t_struct *st)
{
	if (st->pipe > 0)
	{
		do_pipe(st);
		st->pipe = 0;
	}
	else if (st->chevrons > 0)
	{
		if (!do_chevrons(st->cmd, st))
		{
			st->cmd = del_chevron(st->cmd);
			if (ft_strcmp(st->cmd[0], ""))
			{
				ft_edit_cmd(st->cmd);
				do_builtin(st->cmd, st);
			}
		}
	}
	else
	{
		ft_edit_cmd(st->cmd);
		do_builtin(st->cmd, st);
	}
	reset_fd(st);
}
