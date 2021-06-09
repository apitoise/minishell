/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_winsz.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:35:02 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/28 00:01:50 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_getwinsz(t_struct *st)
{
	struct winsize	ws;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
	{
	//	ft_putstr_fd("Could not get window size\n", 2);
		return (1);
	}
	st->ttywidth = ws.ws_col;
	st->ttyheight = ws.ws_row;
	return (0);
}

int	ft_winszdiff(t_history *new, t_struct *st)
{
	int oldwidth;
	int oldheight;

	oldwidth = st->ttywidth;
	oldheight = st->ttyheight;
	if (ft_getwinsz(st))
		return (-1);
	if (oldwidth != st->ttywidth || oldheight != st->ttyheight)
	{
		tputs(tgetstr("cl", NULL), st->ttyheight, &ft_putc);
		if (ft_tputsstr("@minishell> ", NULL, st))
			return (-1);
		if (new->cmdline && ft_tputsstr(new->cmdline, new, st))
			return (-1);
		return (1);
	}
	return (0);
}
