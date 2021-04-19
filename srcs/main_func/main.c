/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:22:41 by cnotin            #+#    #+#             */
/*   Updated: 2021/04/08 13:09:47 by fcadet           ###   ########.fr       */
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
