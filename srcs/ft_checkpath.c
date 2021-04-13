/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 21:23:13 by lgimenez          #+#    #+#             */
/*   Updated: 2020/08/25 21:23:14 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

static void	ft_freepathtab(char **pathtab)
{
	int	i;

	i = 0;
	while (pathtab[i])
	{
		free(pathtab[i]);
		pathtab[i] = NULL;
		i++;
	}
	free(pathtab);
	pathtab = NULL;
}

static void	ft_exec(char *filepath, t_struct *st)
{
	pid_t	p;

	p = fork();
	if (p > 0)
		waitpid(p, NULL, 0);
	else if (p == 0)
	{
		if (execve(filepath, st->cmd, st->env) == -1)
			printf("Error!!\n"); //must deal with error
	}
	else
		printf("Error!\n"); //must deal with error
}

static int	ft_checkfile(char *filepath)
{
	struct stat	buff;

	return (!stat(filepath, &buff));
}

static char	*ft_finalpath(char *s1, char *s2)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(s1, "/");
	tmp2 = ft_strjoin(tmp1, s2);
	free(tmp1);
	return (tmp2);
}

static void	ft_checkpath2(char *path, t_struct *st)
{
	char	**pathtab;
	char	*filepath;
	int		i;

	pathtab = ft_split(path, ':');
	filepath = NULL;
	i = 0;
	while (pathtab[i])
	{
		filepath = ft_finalpath(pathtab[i], st->cmd[0]);
		if (ft_checkfile(filepath))
		{
			ft_exec(filepath, st);
			free(filepath);
			return ;
		}
		else
		{
			free(filepath);
			filepath = NULL;
			i++;
		}
	}
	not_cmd(st->cmd[0], st);
	ft_freepathtab(pathtab);
}

void		ft_checkpath(t_struct *st)
{
	t_varlist	*tmp;

	tmp = st->lst;
	while (ft_strcmp(tmp->name, "PATH") && tmp)
		tmp = tmp->next;
	if (!tmp)
	{
		not_cmd(st->cmd[0], st);
	}
	else
		ft_checkpath2(tmp->content, st);
}
