/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:21 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/27 12:06:37 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

int		ft_error(char *s)
{
	ft_putstr_fd(s, 2);
	//ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
	return (errno);
}

void	not_cmd(char *str, t_struct *st)
{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" : command not found\n", 2);
		st->ret = 127;
}