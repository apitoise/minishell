/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:07 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/14 15:44:35 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	elem_updatelist(char *name, char *content, int *flags, t_struct *st)
{
	if (!xp_varexist(name, &st->lst))
	{
		if (xp_newlst(name, content, flags[1], &st->lst))
			return (elem_error(name, content));
	}
	else if (flags[0])
	{
		if (xp_catlist(name, content, &st->lst))
			return (elem_error(name, content));
	}
	else
		xp_modiflist(name, content, flags[1], &st->lst);
	return (0);
}

static int	elem_getstrsbis(char *cmd, int i, char **name, int (*flags)[2])
{
	if (cmd[i - 1] == '+')
	{
		*name = xp_getname(cmd, '+');
		if (!*name)
			return (1);
		(*flags)[0] = 1;
	}
	else
	{
		*name = xp_getname(cmd, '=');
		if (!*name)
			return (1);
	}
	return (0);
}

static int	elem_getstrs(char *cmd, int visible, t_struct *st)
{
	int		flags[2];
	int		i;
	char	*name;
	char	*content;

	flags[0] = 0;
	flags[1] = visible;
	name = NULL;
	content = NULL;
	i = -1;
	while (cmd[++i] != '=')
		;
	if (elem_getstrsbis(cmd, i, &name, &flags))
		return (1);
	i += 1;
	content = malloc(sizeof(char) * ft_strlen(cmd + i) + 1);
	ft_strcpy(content, cmd + i);
	return (elem_updatelist(name, content, flags, st));
}

static void	create_elem(char **cmd, int f, int visible, t_struct *st)
{
	t_varlist	*current;

	while (cmd[++f])
	{
		if (!xp_checkerror(cmd[f], st))
		{
			if (ft_strchr(cmd[f], '='))
				elem_getstrs(cmd[f], visible, st);
			else
			{
				if (xp_varexist(cmd[f], &st->lst))
				{
					current = st->lst;
					while (current)
					{
						if (!ft_strcmp(current->name, cmd[f]))
							current->visible = 1;
						current = current->next;
					}
				}
				else
					xp_newlst(ft_strdup(cmd[f]), NULL, 1, &st->lst);
			}
		}
	}
}

void	ft_export(char **cmd, t_struct *st, int f)
{
	if (f == 2)
	{
		if (!cmd[1])
			printlist_export(&st->lst);
		else
			return (create_elem(cmd, 0, 1, st));
	}
	else
		return (create_elem(cmd, -1, 0, st));
}
