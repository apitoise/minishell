/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:58:41 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/12 15:07:48 by lgimenez         ###   ########.fr       */
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
		if (st->pipe == 0 && st->chevrons == 0) {
			dup2(st->stdout_copy, 1);
		} else
			dup2(st->stdout_fd, 1);
		dup2(st->stdin_fd, 0);
		ft_exec(cmd, filepath, st);
		close(0);
		close(1);
		ft_exit(cmd, st);
	}
	else
	{
		g_sig.pid = forking;
		st->childps = 1;
		waitpid(forking, &st->childret, 0);
		g_sig.pid = 0;
		free(filepath);
		if (st->pipe == 0) {
			dup2(st->stdin_copy, 0);
		}
	}
}
