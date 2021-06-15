/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_chevron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:26:28 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/07 13:45:51 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	single_chevron(char **cmd, t_struct *st, int i)
{
	int	new_fd;

	if (st->stdout_fd >= 0)
		close(st->stdout_fd);
	new_fd = open(cmd[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (new_fd < 0)
		return ;
	if (dup2(new_fd, STDOUT_FILENO) < 0)
		return ;
	st->was_chevr = 1;
}

static void	double_chevron(char **cmd, t_struct *st, int i)
{
	int	new_fd;

	if (st->stdout_fd >= 0)
		close(st->stdout_fd);
	new_fd = open(cmd[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (new_fd < 0)
		return ;
	if (dup2(new_fd, STDOUT_FILENO) < 0)
		return ;
	st->was_chevr = 1;
}

static int	left_chevron(char **cmd, t_struct *st, int i)
{
	int	new_fd;

	if (st->stdin_fd >= 0)
		close(st->stdin_fd);
	new_fd = open(cmd[i + 1], O_RDONLY, 0666);
	if (new_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (dup2(new_fd, STDIN_FILENO) < 0)
		return (0);
	st->was_lchevr = 1;
	return (0);
}

int	do_chevrons(char **cmd, t_struct *st)
{
	int	i;
	int	err;

	if (cmd[0] == NULL)
		return (0);
	i = 0;
	err = 0;
	st->chevrons = 0;
	while (cmd[i] && err == 0)
	{
		if (!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>")
			|| !ft_strcmp(cmd[i], "<"))
			st->chevrons++;
		if (!ft_strcmp(cmd[i], ">"))
			single_chevron(cmd, st, i);
		else if (!ft_strcmp(cmd[i], ">>"))
			double_chevron(cmd, st, i);
		else if (!ft_strcmp(cmd[i], "<"))
			err = left_chevron(cmd, st, i);
		i++;
	}
	return (err);
}
