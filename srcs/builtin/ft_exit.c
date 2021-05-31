/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:24:20 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/31 10:19:02 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	get_ret(char *arg)
{
	int	i;

	if (arg)
	{
		i = 0;
		while (arg[i])
		{
			if (ft_isdigit(arg[i]))
				i++;
			else
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(arg, 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				return (2);
			}
		}
		return (ft_atoi(arg));
	}
	else
		return (0);
}

void		ft_free_hstab(t_history **hstab, int len)
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

void		ft_varlstclear(t_varlist **lst)
{
	if (lst && *lst)
	{
		if ((*lst)->next)
			ft_varlstclear((t_varlist **)&(*lst)->next);
		free((*lst)->name);
		if ((*lst)->content)
			free((*lst)->content);
		free(*lst);
	}
}

void		ft_exit(char **cmd, t_struct *st)
{
	int	ret;

	ft_putstr_fd("exit\n", 1);
	ret = get_ret(cmd[1]);
	ft_free_tab(cmd);
	ft_freeptr((void**)&st->input);
	if (st->env)
		ft_free_tab(st->env);
	ft_varlstclear(&st->lst);
	ft_free_hstab(st->hstab, st->hslen);
	exit(ret);
}
