/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:54:59 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/31 04:16:12 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	get_signals(t_struct *st)
{
	signal(SIGQUIT, ctrl_backslash);
	signal(SIGINT, ctrl_c);
	if (g_sig.sig_ret != 0)
		st->ret = g_sig.sig_ret;
	g_sig.sig_ret = 0;
}
