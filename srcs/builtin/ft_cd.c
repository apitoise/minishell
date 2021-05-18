/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:23:55 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/19 01:32:53 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void		modif_pwd(char *name, char *content, t_varlist **lst)
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

void			ft_cd(char *path, t_struct *st)
{
	int		ret;
	char	buff[PATH_MAX];
	char	*newpwd;
	char	*oldpwd;

	getcwd(buff, PATH_MAX);
	oldpwd = ft_strdup(buff);
	modif_pwd("OLDPWD", oldpwd, &st->lst);
	if (!path)
		path = "../../../../../../../../";
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
	getcwd(buff, PATH_MAX);
	newpwd = ft_strdup(buff);
	modif_pwd("PWD", newpwd, &st->lst);
}
