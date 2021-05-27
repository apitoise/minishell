/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_getposition.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:20:53 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/28 00:18:19 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	getposition_atoi(char *buff, int i, t_struct *st)
{
	int	pow;

	st->posx = 0;
	st->posy = 0;
	--i;
	pow = 1;
	while (buff[i] != ';')
	{
		st->posx = st->posx + (buff[i] - '0') * pow;
		pow *= 10;
		--i;
		if (i < 0)
			return (1);
	}
	--i;
	pow = 1;
	while (buff[i] != '[')
	{
		st->posy = st->posy + (buff[i] - '0') * pow;
		pow *= 10;
		--i;
		if (i < 0)
			return (1);
	}
	return (0);
}

int			ft_getposition(t_struct *st)
{
	char	buff[30];
	char	c;
	int		i;

	if (write(1, "\033[6n", 4) == -1)
		return (1);
	i = -1;
	c = 0;
	while (c != 'R')
	{
		if (read(0, &c, 1) < 1)
			return (1);
		buff[++i] = c;
	}
	if (i < 2)
		return (1);
	if (getposition_atoi(buff, i, st))
		return (1);
	return (0);
}
