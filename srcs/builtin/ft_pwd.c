/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:24:31 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/04 16:03:17 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_pwd(char **cmd, t_struct *st)
{
	char	path[PATH_MAX];
	int	out = st->pipe ? st->stdout_fd : 1;

	(void)cmd;
	if (!(getcwd(path, PATH_MAX)))
		return (ft_error(""));
	else
	{
		ft_putstr_fd(path, out);
		ft_putstr_fd("\n", out);
	}
	return (0);
}
