/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:36 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 19:30:11 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

void	ft_cd(char *path, t_struct *st)
{
	int		test;

	test = chdir(path);
	if (test == -1 && path)
	{
		ft_putstr_fd("bash: cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(strerror(errno), 1);
		ft_putchar_fd('\n', 1);
		st->ret = 1;
	}
}
