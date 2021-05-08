/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:35:02 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/08 18:36:30 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_getwinsz(t_struct *st)
{
	struct winsize	ws;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
	{
		ft_putstr_fd("Could not get window size\n", 2);
		return (1);
	}
	st->ttywidth = ws.ws_col;
	st->ttyheight = ws.ws_row;
	return (0);
}

int	ft_putc(int c)
{
	write(1, &c, 1);
	return (0);
}
