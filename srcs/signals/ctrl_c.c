/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 11:46:18 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/04 13:56:22 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	delcmdt(void)
{
	int	i;

	i = -1;
	while (g_sig.cmdt[++i])
	{
		free(g_sig.cmdt[i]);
		g_sig.cmdt[i] = NULL;
	}
}

void	ctrl_c(int useless)
{
	(void)useless;
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("\n", 1);
		kill(g_sig.pid, SIGINT);
		if (g_sig.cmdt)
		{
			delcmdt();
			g_sig.cmdt = NULL;
		}
		g_sig.pid = 0;
	}
	else
	{
		if ((*g_sig.cmdl)->cmdline)
			(*g_sig.cmdl)->cmdline[0] = '\0';
		ft_putstr_fd("^C\n", 1);
		shell_init();
	}
}
