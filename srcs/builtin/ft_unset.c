/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:09:33 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/19 15:09:35 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_clrelem(char **cmd, t_struct *st, int i)
{
	t_varlist	*curelem;
	t_varlist	*prvelem;

	if (st->lst == NULL)
		return (0);
	curelem = st->lst;
	prvelem = NULL;
	while (ft_strcmp(curelem->name, cmd[i]) && curelem->next)
	{
		prvelem = curelem;
		curelem = curelem->next;
	}
	if (!ft_strcmp(curelem->name, cmd[i]))
	{
		free(curelem->name);
		free(curelem->content);
		if (prvelem)
			prvelem->next = curelem->next;
		else
			st->lst = curelem->next;
		free(curelem);
	}
	return (0);
}

int	ft_unset(char **cmd, t_struct *st)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_clrelem(cmd, st, i);
		i++;
	}
	return (0);
}
