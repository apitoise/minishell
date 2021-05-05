/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:22:40 by lgimenez          #+#    #+#             */
/*   Updated: 2021/04/21 22:42:49 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	rmbslash(char **str)
{
	int i;
	int	j;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\\')
		{
			j = i;
			while ((*str)[j])
			{
				(*str)[j] = (*str)[j + 1];
				j++;
			}
		}
	}
}

static void	rmquote(char **str)
{
	int	i;
	int	j;

	i = 0;
	while ((*str)[i])
	{
		if (((*str)[i] == '\'' || (*str)[i] == '"'))
		{
			j = i;
			while ((*str)[j])
			{
				(*str)[j] = (*str)[j + 1];
				j++;
			}
		}
		else if ((*str)[i] == '\\')
			i += 2;
		else
			++i;
	}
}

void		ft_edit_cmd(t_struct *st)
{
	int	i;

	i = -1;
	while (st->cmd[++i])
	{
		rmquote(&(st->cmd[i]));
		rmbslash(&(st->cmd[i]));
	}
}