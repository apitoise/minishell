/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:17 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 19:51:59 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	ft_exit(char **cmd)
{
	ft_putstr_fd("exit\n", 1);
	ft_free_tab(cmd);
	//a free au complet;
	exit(0);
	//return (0);
}
