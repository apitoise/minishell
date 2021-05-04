/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 11:46:18 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/27 11:46:21 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void    ctrl_c(int useless)
{
    (void)useless;
    sig.sig_ret = 130;
    sig.exit_status = 1;
    if (sig.pid != 0)
    {
        ft_putstr_fd("\n", 1);
        kill(sig.pid, SIGINT);
        sig.pid = 0;
    }
    else
    {
        ft_putstr_fd("\n", 1);
        shell_init();
    }
}