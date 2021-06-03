/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:58:41 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/02 12:14:39 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	ft_exec(char **cmd, char *filepath, t_struct *st)
{
	if (execve(filepath, cmd, st->env) == -1)
	{
		free(filepath);
		not_cmd(cmd, st);
	}
}

void	ft_fork(char **cmd, char *filepath, t_struct *st)
{
	pid_t	forking;

	forking = fork();
	if (forking == 0)
	{
		ft_exec(cmd, filepath, st);
		exit(st->ret);
	}
	else
	{
		g_sig.pid = forking;
		waitpid(forking, &st->ret, 0);
		g_sig.pid = 0;
		free(filepath);
	}
}
