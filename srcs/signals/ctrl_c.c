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
    ft_putstr_fd("^C\n", 1);
    shell_init();
    tputs(tgetstr("sc", NULL), 1, ft_putchar);
}