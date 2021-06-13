/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:37 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/04 16:38:23 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	bis(t_struct *st)
{
	st->ret = 0;
	st->childps = 0;
	st->childret = 0;
	st->startposx = 0;
	st->ttywidth = 0;
	st->ttyheight = 0;
	st->posx = 0;
	st->posy = 0;
	st->hstab = NULL;
	st->hslen = 0;
	st->hscapacity = 0;
	st->hsindex = 0;
}

void	init_struct(t_struct *st, char **env)
{
	st->exit = 0;
	st->s = NULL;
	st->cmd = NULL;
	st->input = NULL;
	st->lst = NULL;
	st->result = NULL;
	st->stdout_copy = dup(1);
	st->stdin_copy = dup(0);
	st->stdout_fd = dup(1);
	st->stdin_fd = dup(0);
	st->pipe = 0;
	st->chevrons = 0;
	st->env = get_env(env);
	init_lstenv(env, st);
	bis(st);
}
