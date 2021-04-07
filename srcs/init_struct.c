/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:22:58 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/25 21:30:59 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	init_struct(t_struct *st, char **env)
{
	st->exit = 0;
	st->s = NULL;
	st->cmd = NULL;
	st->lst = NULL;
	st->result = NULL;
	st->fd = 1;
	st->env = get_env(env);
	st->ret = 0;
	init_lstenv(env, st);
	return ;
}
