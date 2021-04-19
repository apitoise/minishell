/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:08:46 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/19 15:08:51 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	check_str(char **cmd, int i, int j, char c)
{
	while(cmd[i])
	{
		while (cmd[i][j])
		{
			if (cmd[i][j] == c)
				return (1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

void		check_cmd(char **cmd, int i)
{
	int	j;
	int	ok;

	ok = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j] && !ok)
		{
			if (cmd[i][j] == '\'' || cmd[i][j] == '\"')
				ok = check_str(cmd, i, j + 1, cmd[i][j]);
			j++;
		}
		i++;
	}
}
