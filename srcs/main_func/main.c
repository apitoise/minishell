/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:46 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/06 20:00:55 by lgimenez         ###   ########.fr       */
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
	if (init_termcap(&st))
		return (1);
	minishell(&st);
	return (0);
}
