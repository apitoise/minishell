/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:26:50 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/15 15:35:06 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	if_builtin(char **cmd, t_struct *st)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd, st);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd, 0, st);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd, st);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(st);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, st);
	else if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(cmd, st);
	else if (ft_strchr(cmd[0], '='))
		ft_export(cmd, st, 1);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, st, 2);
	else
		ft_checkpath(cmd, st);
}

void	do_builtin(char **cmd, t_struct *st)
{
	if (cmd[0])
	{
		if_builtin(cmd, st);
		if (st->childps)
		{
			if (WIFEXITED(st->childret))
				st->ret = WEXITSTATUS(st->childret);
			else if (WIFSIGNALED(st->childret))
				st->ret = WTERMSIG(st->childret) + 128;
			if (st->ret == 137)
				ft_putstr_fd("Killed\n", 1);
		}
		st->childps = 0;
		st->childret = 0;
	}
	else
		st->ret = 0;
}
