/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:32 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 18:41:19 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

int	ft_echo(char **cmd)
{
	int	i;
	int n;
	char *res;

	i = 1;
	n = 0;
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
		n = 1;
	i += n;
	while (cmd[i])
	{
		res = ft_trim(cmd[i]);
		ft_putstr_fd(res, 2);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		free(res);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (0);
}
