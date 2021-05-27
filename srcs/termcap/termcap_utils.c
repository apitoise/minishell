/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:35:02 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/28 00:23:39 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	ft_freehs(t_history *new)
{
	if (new)
	{
		if (new->cmdline)
			free(new->cmdline);
		free(new);
		new = NULL;
	}
}

int		ft_nextline(t_history *new, t_struct *st)
{
	size_t	len;

	if (ft_getposition(st))
		return (1);
	len = 0;
	if (new)
		len = new->len;
	if ((st->startposx - 1 + len) % (unsigned int)st->ttywidth == 0)
	{
		if (st->posy == st->ttyheight)
		{
			tputs(tgoto(tgetstr("cm", NULL), 0, st->posy - 1), 1, &ft_putc);
			tputs(tgetstr("sf", NULL), st->ttyheight, &ft_putc);
		}
		else
			tputs(tgoto(tgetstr("cm", NULL), 0, st->posy), 1, &ft_putc);
	}
	return (0);
}

int		ft_tputsstr(char *str, t_history *new, t_struct *st)
{
	tputs(str, 1, &ft_putc);
	if (ft_nextline(new, st))
		return (1);
	return (0);
}

int		ft_isblank(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}

int		ft_putc(int c)
{
	write(1, &c, 1);
	return (0);
}
