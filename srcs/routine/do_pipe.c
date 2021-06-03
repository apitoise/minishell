/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:02 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/02 16:35:13 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	exec_cmd(char ***cmd, int end, t_struct *st)
{
	char	*par[MAX_PARAM];
	int		new_pipe[2];
	int		i;

	if (end == 0)
		return ;
	else
	{
		if ((*cmd)[end] && !ft_strcmp((*cmd)[end], "|"))
		{
			if (pipe(new_pipe) == -1)
				return ;
			st->stdout_fd = new_pipe[1];
			if (!do_chevrons(*cmd, st))
			{
				*cmd = del_chevron(*cmd);
				i = 0;
				while (i < end)
				{
					par[i] = (*cmd)[i];
					i++;
				}
				par[end] = NULL;
				if (ft_strcmp((*cmd)[0], ""))
				{
					dup2(st->stdin_fd, STDIN_FILENO);
					dup2(st->stdout_fd, STDOUT_FILENO);
					ft_edit_cmd(par);
					do_builtin(par, st);
					if (st->stdin_fd != 0)
						close(st->stdin_fd);
					st->stdin_fd = new_pipe[0];
					if (st->stdout_fd != 1)
						close(st->stdout_fd);
					st->stdout_fd = st->stdout_copy;
					*cmd += end;
					return ;
				}
			}
		}
		else
		{
			ft_edit_cmd(*cmd);
			do_builtin(*cmd, st);
		}
		if (STDOUT_FILENO != 1)
			close(STDOUT_FILENO);
		if (dup2(st->stdout_copy, STDOUT_FILENO) < 0)
			return ;
		if (STDIN_FILENO != 0)
			close(STDIN_FILENO);
		if (dup2(st->stdin_copy, STDIN_FILENO) < 0)
			return ;
		*cmd += end;
	}
}

void		do_pipe(char **cmd, t_struct *st)
{
	int	i;
	
	while (*(cmd))
	{
		i = 0;
		while (cmd[i] && strcmp(cmd[i], ";") && strcmp(cmd[i], "|"))
			i++;
		exec_cmd(&cmd, i, st);
		if (*(cmd))
			cmd++;
	}
	if (STDOUT_FILENO != 1)
		close(STDOUT_FILENO);
	if (dup2(st->stdout_copy, STDOUT_FILENO) < 0)
		return ;
	if (STDIN_FILENO != 0)
		close(STDIN_FILENO);
	if (dup2(st->stdin_copy, STDIN_FILENO) < 0)
		return ;
}


// static char	**cmd_before_pipe(char **cmd, int pipe_nb)
// {
// 	char	**res;
// 	int		i;
// 	int		save;
// 	int		j;

// 	i = 0;
// 	while (pipe_nb > 0 && cmd[i])
// 	{
// 		if (!ft_strcmp(cmd[i], "|"))
// 			pipe_nb--;
// 		i++;
// 	}
// 	save = i;
// 	while (cmd[i] && ft_strcmp(cmd[i], "|"))
// 		i++;
// 	if (!(res = (char **)malloc(sizeof(char *) * (i - save + 1))))
// 		return (NULL);
// 	j = 0;
// 	while (cmd[save] && ft_strcmp(cmd[save], "|"))
// 		res[j++] = ft_strdup(cmd[save++]);
// 	res[j] = NULL;
// 	return (res);
// }

// void		do_pipe(t_struct *st)
// {
// 	int		new_pipe[2];
// 	int		pipe_nb;
// 	char	**cmd;

// 	if (pipe(new_pipe) != 0)
// 		return ;
// 	pipe_nb = 0;
// 	while (pipe_nb <= st->pipe)
// 	{
// 		st->stdout_fd = new_pipe[1];
// 		cmd = cmd_before_pipe(st->cmd, pipe_nb);
		// if (!do_chevrons(cmd, st))
		// {
		// 	cmd = del_chevron(cmd);
		// 	if (ft_strcmp(cmd[0], ""))
		// 	{
		// 		dup2(st->stdin_fd, STDIN_FILENO);
		// 		dup2(st->stdout_fd, STDOUT_FILENO);
		// 		ft_edit_cmd(cmd);
		// 		do_builtin(cmd, st);
		// 	}
// 			dup2(new_pipe[0], st->stdin_fd);
// 			dup2(st->stdout_copy, st->stdout_fd);
// 		}
// 		ft_free_tab(cmd);
// 		pipe_nb++;
// 	}
//	close(STDIN_FILENO);
//	close(STDOUT_FILENO);
//	dup2(st->stdin_copy, STDIN_FILENO);
//	dup2(st->stdout_copy, STDOUT_FILENO);
//}
