/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:37 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/19 15:27:38 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_struct(t_struct *st, char **env)
{
	st->exit = 0;
	st->s = NULL;
	st->cmd = NULL;
	st->lst = NULL;
	st->result = NULL;
	st->stdout_copy = dup(1);
	st->stdin_copy = dup(0);
	st->stdout_fd = dup(1);
	st->stdin_fd = dup(0);
	st->pipe = 0;
	st->env = get_env(env);
	st->ret = 0;
	init_lstenv(env, st);
	return ;
}
