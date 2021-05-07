/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:13 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/07 14:02:26 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	do_routine(t_struct *st)
{
	if (st->pipe > 0)
	{
		do_pipe(st);
		st->pipe = 0;
	}
	else
	{
		if (!do_chevrons(st->cmd, st))
		{
			st->cmd = del_chevron(st->cmd);
			if (ft_strcmp(st->cmd[0], ""))
			{
				ft_edit_cmd(st);
				do_builtin(st->cmd, st);
			}
		}
	}
	if (dup2(st->stdout_copy, STDOUT_FILENO) < 0)
		return ;
	if (dup2(st->stdin_copy, STDIN_FILENO) < 0)
		return ;
}
