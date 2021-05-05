/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:54:59 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/05 14:55:05 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void    get_signals(t_struct *st)
{
	signal(SIGQUIT, ctrl_backslash);
	signal(SIGINT, ctrl_c);
	if (sig.sig_ret != 0)
		st->ret = sig.sig_ret;
    sig.sig_ret = 0;
}