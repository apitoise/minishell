/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:24:20 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/30 22:58:22 by lgimenez         ###   ########.fr       */
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

void	ft_varlstclear(t_varlist **lst)
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

void	ft_exit(char **cmd, t_struct *st)
{
	ft_putstr_fd("exit\n", 1);
	ft_free_tab(cmd);
	if (st->input)
		ft_free_tab(st->input);
	if (st->env)
		ft_free_tab(st->env);
	ft_varlstclear(&st->lst);
	ft_free_hstab(st->hstab, st->hslen);
	exit(EXIT_SUCCESS);
}
