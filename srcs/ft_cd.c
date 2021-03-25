/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:36 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 19:30:11 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

static void		modif_pwd(char *name, char *content, t_varlist **lst)
{
	t_varlist	*current;

	current = *lst;
	while (ft_strcmp(current->name, name) && current->next)
		current = current->next;
	free(current->content);
	current->content = content;
}

void    		ft_cd(char *path, t_struct *st)
{
        int             test;
        char 			newpwd[PATH_MAX];
        char    		oldpwd[PATH_MAX];

        getcwd(oldpwd, PATH_MAX);
		modif_pwd("OLDPWD", oldpwd, &st->lst);
        if (!path)
                path = "../../../../../../../../";
        test = chdir(path);
        if (test == -1 && path)
        {
                ft_putstr_fd("bash: cd: ", 1);
                ft_putstr_fd(path, 1);
                ft_putstr_fd(": ", 1);
                ft_putstr_fd(strerror(errno), 1);
                ft_putchar_fd('\n', 1);
                st->ret = 1;
        }
    	getcwd(newpwd, PATH_MAX);
        modif_pwd("PWD", newpwd, &st->lst);
}