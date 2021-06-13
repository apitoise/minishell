/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:02 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/14 16:32:26 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	exec_cmd(char **cmd, t_struct *st)
{
	ft_edit_cmd(cmd);
	do_builtin(cmd, st);
}

static void	reset_in_out(int in, int out, t_struct *st)
{
	if (st->stdin_fd != 0)
		close(st->stdin_fd);
	st->stdin_fd = in;
	if (st->stdout_fd != 1)
		close(st->stdout_fd);
	st->stdout_fd = out;
}

static char	**cmd_before_pipe(char **cmd, int pipe_nb)
{
	char	**res;
	int		i;
	int		save;
	int		j;

	i = 0;
	while (pipe_nb > 0 && cmd[i])
	{
		if (!ft_strcmp(cmd[i], "|"))
			pipe_nb--;
		i++;
	}
	save = i;
	while (cmd[i] && ft_strcmp(cmd[i], "|"))
		i++;
	res = (char **)malloc(sizeof(char *) * (i - save + 1));
	j = 0;
	while (cmd[save] && ft_strcmp(cmd[save], "|"))
		res[j++] = ft_strdup(cmd[save++]);
	res[j] = NULL;
	return (res);
}

void	do_pipe(t_struct *st)
{
	int		new_pipe[2];
	int		pipe_nb;
	char	**cmd;

	pipe_nb = 0;
	while (pipe_nb <= st->pipe)
	{
		if (pipe_nb == st->pipe)
			st->pipe = 0;
		if (pipe(new_pipe) != 0)
			return ;
		st->stdout_fd = new_pipe[1];
		cmd = cmd_before_pipe(st->cmd, pipe_nb);
		if (!do_chevrons(cmd, st))
		{
			cmd = del_chevron(cmd);
			if (ft_strcmp(cmd[0], ""))
				exec_cmd(cmd, st);
			reset_in_out(new_pipe[0], 1, st);
		}
		ft_free_tab(cmd);
		pipe_nb++;
	}
	reset_in_out(0, 1, st);
}
