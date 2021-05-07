/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 11:46:18 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/07 14:05:06 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	ctrl_c(int useless)
{
	(void)useless;
	g_sig.sig_ret = 130;
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("\n", 1);
		kill(g_sig.pid, SIGINT);
		g_sig.pid = 0;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		shell_init();
	}
}
