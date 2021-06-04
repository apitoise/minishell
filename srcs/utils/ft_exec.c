/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:58:41 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/04 16:34:31 by lgimenez         ###   ########.fr       */
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
		dup2(st->stdin_fd, STDIN_FILENO);
		dup2(st->stdout_fd, STDOUT_FILENO);
		ft_exec(cmd, filepath, st);
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		exit(st->ret);
	}
	else
	{
		g_sig.pid = forking;
		st->childps = 1;
		waitpid(forking, &st->childret, 0);
		g_sig.pid = 0;
		free(filepath);
	}
}
