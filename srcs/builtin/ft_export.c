/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:07 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/19 21:03:24 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	create_list(char *name, char *content, int visible, t_varlist **lst)
{
	t_varlist	*current;
	t_varlist	*new;

	if (!(new = malloc(sizeof(t_varlist))))
		return (1);
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
	return (0);
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
		if (!is_alpha(arg[i]) && !(arg[i] == '+' && arg[i + 1] == '=' && i > 0))
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

static int	cat_list(char *name, char *content, t_varlist **lst)
{
	t_varlist	*current;
	char		*tmp;

	current = *lst;
	while (current && ft_strcmp(current->name, name))
		current = current->next;
	if (!current || !(tmp = ft_strjoin(current->content, content)))
		return (1);
	free(current->content);
	current->content = tmp;
	free(name);
	free(content);
	return (0);
}

static char	*getname(char *cmd, char c)
{
	char	*name;
	int		i;

	i = -1;
	while (cmd[++i] != c && cmd[i])
		;
	if (!cmd[i] || !(name = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = -1;
	while (cmd[++i] != c && cmd[i])
		name[i] = cmd[i];
	name[i] = '\0';
	if (!cmd[i])
	{
		free(name);
		return (NULL);
	}
	return (name);
}

static int	elem_error(char *name, char *content)
{
	if (name)
		free(name);
	if (content)
		free(content);
	return (1);
}

static int	elem_updatelist(char *name, char *content, int *flags, t_struct *st)
{
	if (!varexist(name, &st->lst))
	{
		if (create_list(name, content, flags[1], &st->lst))
			return (elem_error(name, content));
	}
	else if (flags[0])
	{
		if (cat_list(name, content, &st->lst))
			return (elem_error(name, content));
	}
	else
		modif_list(name, content, flags[1], &st->lst);
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
	if (cmd[i - 1] == '+')
	{
		if (!(name = getname(cmd, '+')))
			return (1);
		flags[0] = 1;
	}
	else if (!(name = getname(cmd, '=')))
		return (1);
	i += 1;
	if (!(content = malloc(sizeof(char) * ft_strlen(cmd + i) + 1)))
		return (elem_error(name, content));
	ft_strcpy(content, cmd + i);
	return (elem_updatelist(name, content, flags, st));
}

static void	create_elem(char **cmd, int f, int visible, t_struct *st)
{
	t_varlist	*current;

	while (cmd[++f])
	{
		if (!check_error(cmd[f]))
		{
			if (ft_strchr(cmd[f], '='))
				elem_getstrs(cmd[f], visible, st);
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
