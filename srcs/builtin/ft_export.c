/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:07 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/13 00:30:40 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	create_list(char *name, char *content, int visible, t_varlist **lst)
{
	t_varlist	*current;
	t_varlist	*new;

	if	(!(new = malloc(sizeof(t_varlist))))
		return ;
	new->name = name;
	new->content = content;
	new->visible = visible;
	new->next = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

static int	varexist(char *str, t_varlist **lst)
{
	t_varlist	*current;

	if (*lst == NULL)
		return (0);
	else
	{
		current = *lst;
		while (current->next)
		{
			if (!ft_strcmp(current->name, str))
				return (1);
			else
				current = current->next;
		}
		if (!ft_strcmp(current->name, str))
			return (1);
		return (0);
	}
}

static int	id_notvalid(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	check_error(char *arg)
{
	int	i;

	if (arg[0] == '=')
		return (id_notvalid(arg));
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!is_alpha(arg[i]))
			return (id_notvalid(arg));
		i++;
	}
	return (0);
}

static void	modif_list(char *name, char *content, int visible, t_varlist **lst)
{
	t_varlist	*current;

	current = *lst;
	while (ft_strcmp(current->name, name) && current->next)
		current = current->next;
	free(current->content);
	current->content = content;
	free(name);
	if (visible == 1 && current->visible == 0)
		current->visible = 1;
}

static int	elem_contentyes(char *cmd, int visible, t_struct *st)
{
	int		i;
	char	*name;
	char	*content;

	i = -1;
	while (cmd[++i] != '=')
		;
	if (!(name = malloc(sizeof(char) * i + 1)))
		return (1);
	i = -1;
	while (cmd[++i] != '=')
		name[i] = cmd[i];
	name[i] = '\0';
	i += 1;
	if (!(content = malloc(sizeof(char) * ft_strlen(cmd + i) + 1)))
	{
		free(name);
		return (1);
	}
	ft_strcpy(content, cmd + i);
	if (!varexist(name, &st->lst))
		create_list(name, content, visible, &st->lst);
	else
		modif_list(name, content, visible, &st->lst);
	return (0);
}

static void	create_elem(char **cmd, int f, int visible, t_struct *st)
{
	t_varlist	*current;

	while (cmd[++f])
	{
		if (!check_error(cmd[f]))
		{
			if (ft_strchr(cmd[f], '='))
				elem_contentyes(cmd[f], visible, st);
			else
			{
				if (varexist(cmd[f], &st->lst))
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
					create_list(ft_strdup(cmd[f]), NULL, 1, &st->lst);
			}
		}
	}
}

void		ft_export(char **cmd, t_struct *st, int f)
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
