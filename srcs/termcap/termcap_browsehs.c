/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_browsehs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:20:53 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/29 18:30:28 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static char	*dupcmdl(char *s1, size_t capacity)
{
	char	*s2;
	int		i;

	if (!s1 || ft_strlen(s1) > capacity)
		return (NULL);
	s2 = (char *)malloc(sizeof(char) * (capacity + 1));
	i = -1;
	while (s1[++i])
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}

static void	delcmdline(t_history *new, t_struct *st)
{
	int	startposx;
	int	nbrlines;
	int	i;

	startposx = st->startposx - 1;
	nbrlines = (startposx + new->len) / st->ttywidth;
	if (new->cmdline)
	{
		free(new->cmdline);
		new->cmdline = NULL;
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, st->posy - 1), 1, &ft_putc);
	i = 1;
	while (nbrlines-- && ++i)
	{
		tputs(tgetstr("ce", NULL), 1, &ft_putc);
		tputs(tgoto(tgetstr("cm", NULL), 0, st->posy - i), 1, &ft_putc);
	}
	while (startposx--)
		tputs(tgetstr("nd", NULL), 1, &ft_putc);
	tputs(tgetstr("ce", NULL), 1, &ft_putc);
}

static int	replaceline(t_history *new, t_struct *st)
{
	if (ft_getposition(st))
		return (1);
	delcmdline(new, st);
	if (!st->hsindex)
		ft_bzero(new, sizeof(t_history));
	else if (st->hsindex > 0)
	{
		if ((new->cmdline = dupcmdl(st->hstab[st->hslen - st->hsindex]->cmdline,
					st->hstab[st->hslen - st->hsindex]->capacity)) == NULL)
			return (1);
		new->len = st->hstab[st->hslen - st->hsindex]->len;
		new->capacity = st->hstab[st->hslen - st->hsindex]->capacity;
		if (ft_tputsstr(new->cmdline, new, st))
			return (1);
	}
	return (0);
}

int	tc_browsehs(char c, t_history *new, t_struct *st)
{
	if (c == 'A' && st->hsindex < st->hslen)
		st->hsindex++;
	else if (c == 'B' && st->hsindex > 0)
		st->hsindex--;
	else
		return (0);
	return (replaceline(new, st));
}
