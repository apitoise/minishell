/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:05:48 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/04 17:43:22 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"
#include <curses.h>
#include <term.h>

int	init_termcap(void)
{
	char	*termtype;
	int		ret;

	if	(!(termtype = getenv("TERM")))
	{
		ft_putstr_fd("TERM not defined\n", 2);
		return (1);
	}
	ret = tgetent(NULL, termtype);
	if (ret < 0)
	{
		ft_putstr_fd("Could not access the terminal data base\n", 2);
		return (1);
	}
	else if (!ret)
	{
		ft_putstr_fd("This terminal type is not defined\n", 2);
		return (1);
	}
	return (0);
}
