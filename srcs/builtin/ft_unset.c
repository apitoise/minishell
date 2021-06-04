/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:35:19 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/04 16:04:40 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	isidvalid(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]))
		return (0);
	i = 0;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

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
		if (!isidvalid(cmd[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			st->ret = 1;
		}
		ft_clrelem(cmd, st, i);
		i++;
	}
	return (0);
}
