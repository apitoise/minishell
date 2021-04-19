/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:24:20 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/19 15:24:21 by apitoise         ###   ########.fr       */
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
