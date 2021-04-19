/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:08:34 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/19 15:08:36 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_pwd(char **cmd)
{
	char path[PATH_MAX];

	(void)cmd;
	if (!(getcwd(path, PATH_MAX)))
		return (ft_error(""));
	else
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
