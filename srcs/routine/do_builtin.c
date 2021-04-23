/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:26:50 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/22 16:27:13 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	if_builtin(char **cmd, t_struct *st)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd, st);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(st);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, st);
	else if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(cmd[1], st);
	else if (ft_strchr(cmd[0], '='))
		ft_export(cmd, st, 1);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, st, 2);
	else
		ft_checkpath(cmd, st);
}

void		do_builtin(char **cmd, t_struct *st)
{
	pid_t	pid;

	if (cmd[0] == NULL)
		cmd[0] = ft_strdup("");
	else if (!ft_strcmp(cmd[0], ""))
		not_cmd(cmd[0], st);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(st->stdin_fd, STDIN_FILENO);
			dup2(st->stdout_fd, STDOUT_FILENO);
			if_builtin(cmd, st);
			close(STDOUT_FILENO);
			close(STDIN_FILENO);
		}
		else
			waitpid(pid, &st->ret, 0);
	}
}
