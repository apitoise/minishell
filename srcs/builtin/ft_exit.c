/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:24:20 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/15 15:33:39 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	ft_free_hstab(t_history **hstab, int len)
{
	int	i;

	if (hstab)
	{
		i = -1;
		while (++i < len)
		{
			if (hstab[i]->cmdline)
				free(hstab[i]->cmdline);
			free(hstab[i]);
		}
		free(hstab);
	}
}

void	ft_free_st(t_struct *st)
{
	if (st->input)
		ft_free_tab(st->input);
	if (st->env)
		ft_free_tab(st->env);
	ft_varlstclear(&st->lst);
	ft_free_hstab(st->hstab, st->hslen);
}

static int	isargvalid(char *arg)
{
	int	i;

	if (!arg)
		return (1);
	i = -1;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return (1);
}

static void	exitwitharg(char **cmd, t_struct *st)
{
	if (!isargvalid(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_tab(cmd);
		ft_free_st(st);
		exit(2);
	}
	else if (cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		st->ret = 1;
	}
	else
	{
		st->ret = ft_atoi(cmd[1]);
		ft_free_tab(cmd);
		ft_free_st(st);
		exit(st->ret);
	}
}

void	ft_exit(char **cmd, int child, t_struct *st)
{
	int			out;

	out = 1;
	if (st->pipe)
		out = st->stdout_fd;
	if (!child)
		ft_putstr_fd("exit\n", out);
	if (cmd && cmd[1])
		exitwitharg(cmd, st);
	else
	{
		if (cmd)
			ft_free_tab(cmd);
		ft_free_st(st);
		exit(st->ret);
	}
}
