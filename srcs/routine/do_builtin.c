/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:26:50 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/31 19:18:14 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	if_builtin(char **cmd, t_struct *st)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd, st);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd, st);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(st);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, st);
	else if (!ft_strcmp(cmd[0], "cd"))
	{
		if (cmd[2])
			ft_putstr_fd("minishell: cd: too many arguments\n", 1);
		else
			ft_cd(cmd[1], st);
	}
	else if (ft_strchr(cmd[0], '='))
		ft_export(cmd, st, 1);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, st, 2);
	else
		ft_checkpath(cmd, st);
}

void		do_builtin(char **cmd, t_struct *st)
{
	if (cmd[0])
		if_builtin(cmd, st);
	if (st->ret > 0)
		st->ret = st->ret / 256;
}
