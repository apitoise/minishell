/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_ediths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:20:53 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/28 00:09:45 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	ft_hstabcpy(t_history **tmp, t_struct *st)
{
	size_t	i;

	i = 0;
	while (i < st->hslen)
	{
		tmp[i] = st->hstab[i];
		++i;
	}
}

static int	ediths_resize(t_history **new, t_struct *st)
{
	t_history	**tmp;

	if (st->hslen + 1 > st->hscapacity)
	{
		tmp = malloc(sizeof(t_history *) * (st->hscapacity * 2));
		ft_hstabcpy(tmp, st);
		free(st->hstab);
		st->hstab = tmp;
		st->hscapacity *= 2;
	}
	st->hstab[st->hslen] = *new;
	st->hslen++;
	return (0);
}

int	tc_ediths(t_history **new, t_struct *st)
{
	if (!st->hstab)
	{
		st->hstab = malloc(sizeof(t_history *));
		st->hstab[0] = *new;
		st->hslen = 1;
		st->hscapacity = 1;
	}
	else if (ft_strcmp(st->hstab[st->hslen - 1]->cmdline, (*new)->cmdline))
	{
		if (ediths_resize(new, st))
			return (1);
	}
	else
	{
		ft_freehs(*new);
		*new = st->hstab[st->hslen - 1];
	}
	return (0);
}
