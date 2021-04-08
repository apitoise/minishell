/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:08 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/25 21:41:08 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

int	ft_pwd(char **cmd)
{
	char path[PATH_MAX];

	(void)cmd;
	if (!(getcwd(path, PATH_MAX)))
		return (ft_error(""));
	else
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}
