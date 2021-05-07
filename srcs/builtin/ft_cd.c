/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:23:55 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/07 13:27:47 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void		modif_pwd(char *name, char *content, t_varlist **lst)
{
	t_varlist	*current;

	current = *lst;
	while (ft_strcmp(current->name, name) && current->next)
		current = current->next;
	current->content = content;
}

void			ft_cd(char *path, t_struct *st)
{
	int		test;
	char	newpwd[PATH_MAX];
	char	oldpwd[PATH_MAX];

	getcwd(oldpwd, PATH_MAX);
	modif_pwd("OLDPWD", oldpwd, &st->lst);
	if (!path)
		path = "../../../../../../../../";
	test = chdir(path);
	if (test == -1 && path)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		st->ret = 1;
	}
	getcwd(newpwd, PATH_MAX);
	modif_pwd("PWD", newpwd, &st->lst);
}
