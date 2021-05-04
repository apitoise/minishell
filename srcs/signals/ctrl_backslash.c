/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_backslash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:47:35 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/03 13:47:37 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void    ctrl_backslash(int useless)
{
    (void)useless;
    sig.sig_ret = 131;
    if (sig.pid != 0)
    {
        printf("Quit (core dumped)\n");
        kill(sig.pid, SIGQUIT);
        sig.pid = 0;
    }
    else
        return ;
}