/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:23:55 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/04 19:56:27 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	modif_pwd(char *name, char *content, t_varlist **lst)
{
	t_varlist	*current;

	current = *lst;
	while (ft_strcmp(current->name, name) && current)
		current = current->next;
	if (current && current->content)
	{
		free(current->content);
		current->content = content;
	}
}

static int	gethomevalue(char **path, t_struct *st)
{
	t_varlist	*current;
	char		*home;
	char		*tmp;

	current = st->lst;
	while (current && ft_strcmp(current->name, "HOME"))
		current = current->next;
	if (current)
		home = current->content;
	else if (!(home = getenv("HOME")))
		return (1);
	cd_deltilde(*path);
	if (!(tmp = ft_strjoin(home, *path)))
		return (1);
	free(*path);
	*path = tmp;
	return (0);
}

static void	gotopath(char *path, t_struct *st)
{
	int		ret;
	char	buff[PATH_MAX];
	char	*newpwd;

	ret = chdir(path);
	if (ret == -1 && path)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		st->ret = 1;
	}
	free(path);
	getcwd(buff, PATH_MAX);
	newpwd = ft_strdup(buff);
	modif_pwd("PWD", newpwd, &st->lst);
}

static void	editpath(char *cmd, t_struct *st)
{
	char	buff[PATH_MAX];
	char	*oldpwd;
	char	*path;

	if (!cmd)
	{
		if (!(path = malloc(sizeof(char) * 2)))
			return ;
		path[0] = '~';
		path[1] = '\0';
	}
	else if (!ft_strcmp(cmd, "-"))
	{
		if (cd_getoldpwd(&path, st))
			return ;
	}
	else if (!(path = ft_strdup(cmd)))
		return ;
	if (path[0] == '~' && gethomevalue(&path, st))
		return (ft_freeptr((void**)&path));
	getcwd(buff, PATH_MAX);
	oldpwd = ft_strdup(buff);
	modif_pwd("OLDPWD", oldpwd, &st->lst);
	gotopath(path, st);
}

void		ft_cd(char **cmd, t_struct *st)
{
	if (cmd[2])
	{
	  	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		st->ret = 1;
	}
	else
		editpath(cmd[1], st);
}
