/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_editcmdl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:20:53 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/27 23:57:33 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	delone(t_history *new, t_struct *st)
{
	int	i;

	if (new->cmdline && new->cmdline[0])
	{
		i = -1;
		while (new->cmdline[++i])
			;
		new->cmdline[--i] = '\0';
		new->len--;
		if (ft_getposition(st))
			return (1);
		if (st->posx == 1 && st->posy != 1)
		{
			tputs(tgoto(tgetstr("cm", NULL), st->ttywidth, st->posy - 2),
				1, &ft_putc);
			tputs(tgetstr("dc", NULL), 1, &ft_putc);
		}
		else
		{
			tputs(tgetstr("le", NULL), 1, &ft_putc);
			tputs(tgetstr("dc", NULL), 1, &ft_putc);
		}
	}
	return (0);
}

static int	vector(t_history *new, char *buff)
{
	char	*tmp;

	if (new->cmdline == NULL)
	{
		if (!(new->cmdline = malloc(sizeof(char) + 1)))
			return (1);
		new->capacity = 1;
		ft_strcpy(new->cmdline, buff);
		new->len = 1;
	}
	else
	{
		if (new->len + 1 > new->capacity)
		{
			if (!(tmp = malloc(sizeof(char) * (new->capacity * 2 + 1))))
				return (1);
			ft_strcpy(tmp, new->cmdline);
			free(new->cmdline);
			new->cmdline = tmp;
			new->capacity *= 2;
		}
		ft_strcat(new->cmdline, buff);
		new->len++;
	}
	return (0);
}

int			tc_editcmdl(char *buff, t_history *new, t_struct *st)
{
	if (buff[0] == 127)
	{
		if (delone(new, st))
			return (1);
	}
	else if ((buff[0] != '\n' && vector(new, buff))
			|| (ft_tputsstr(buff, new, st)))
		return (1);
	return (0);
}
