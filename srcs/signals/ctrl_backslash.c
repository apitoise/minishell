/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_backslash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:47:35 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/04 15:18:02 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	ctrl_backslash(int useless)
{
	(void)useless;
	if (g_sig.pid != 0)
	{
		printf("Quit (core dumped)\n");
		kill(g_sig.pid, SIGQUIT);
		g_sig.pid = 0;
	}
	else
		return ;
}
