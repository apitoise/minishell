/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:29 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/22 16:17:21 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int		ft_error(char *s)
{
	ft_putstr_fd(s, 2);
	//ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
	return (errno);
}

void	not_cmd(char *str, t_struct *st)
{
//		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" : command not found\n", 2);
		st->ret = 127;
}
