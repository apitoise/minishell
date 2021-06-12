/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:13 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/02 11:34:07 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	reset_in_out(int in, int out, t_struct *st)
{
	if (st->stdin_fd != 0)
		close(st->stdin_fd);
	st->stdin_fd = in;
	if (st->stdout_fd != 1)
		close(st->stdout_fd);
	st->stdout_fd = out;

}

void	launch_exec(char **args, t_struct *st)
{
	dup2(st->stdin_fd, 0);
	dup2(st->stdout_fd, 1);
	if (ft_strcmp(args[0], ""))
	{
		ft_edit_cmd(args);
		do_builtin(args, st);
	}
}

void	exec_cmd(char **cmd, int start, int end, t_struct *st)
{
	char	**args;
	int		new_pipe[2];
	int		i;

	if (end == 0)
		return ;
	else
	{
		if (!(args = (char **)malloc(sizeof(char *) * (end - start) + 1)))
			return ;
		i = 0;
		while (i < (end - start))
		{
			args[i] = cmd[start + i];
			i++;
		}
		args[i] = NULL;
		if (cmd[end] && !ft_strcmp(cmd[end], "|"))
		{
			if (pipe(new_pipe) == -1)
				return ;
			st->stdout_fd = new_pipe[1];
			launch_exec(args, st);
			reset_in_out(new_pipe[0], st->stdout_copy, st);
			free(args);
			return ;
		}
		else
			launch_exec(args, st);
//		if (st->stdin_fd != 0)
//			close(st->stdin_fd);
//		st->stdin_fd = 0;
//		if (st->stdout_fd != 1)
//			close(st->stdout_fd);
//		st->stdout_fd = 1;
		free(args);
		reset_in_out(0, 1, st);
		dup2(st->stdin_copy, 0);
		dup2(st->stdout_copy, 1);
	}
}

void	routine(t_struct *st)
{
	int	i;
	int	j;

	i = 0;
	while (st->cmd[i])
	{
		j = i;
		while (st->cmd[j] != NULL)
		{
			if (!ft_strcmp(st->cmd[j], "|") || !ft_strcmp(st->cmd[j], ";"))
				break ;
			j++;
		}
		exec_cmd(st->cmd, i, j, st);
		i = j;
		if (st->cmd[i])
			i++;
	}
	printf("OK\n");
//	reset_in_out(st->stdin_copy, st->stdout_copy, st);
}
