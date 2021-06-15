/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:24:06 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/12 13:39:07 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	option_n(char *str, int *n, int *option)
{
	int	i;

	if (str[0] == '-')
	{
		i = 0;
		while (str[++i])
		{
			if (str[i] != 'n')
			{
				*option = 1;
				return (0);
			}
		}
		*n = 1;
		return (1);
	}
	*option = 1;
	return (0);
}

int	ft_echo(char **cmd, t_struct *st)
{
	int	i;
	int	n;
	int	option;
	int	out;

	out = 1;
	if (st->pipe)
		out = st->stdout_fd;
	i = 1;
	n = 0;
	option = 0;
	while (cmd[i])
	{
		if (!(!option && option_n(cmd[i], &n, &option)))
		{
			ft_putstr_fd(cmd[i], out);
			if (cmd[i + 1])
				ft_putstr_fd(" ", out);
		}
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", out);
	st->ret = 0;
	return (0);
}
