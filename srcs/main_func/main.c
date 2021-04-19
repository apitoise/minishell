/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:10:30 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/19 15:10:32 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int			main(int ac, char **av, char **env)
{
	t_struct	st;

	(void)ac;
	(void)av;
	init_struct(&st, env);
	minishell(&st);
	return (0);
}
