/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:13 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/25 21:23:14 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

static void		create_list(char *name, char *content, int visible, t_varlist **lst)
{
	t_varlist	*current;
	t_varlist	*new;

	new = malloc(sizeof(t_varlist));
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

static int		is_ok(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (0);
	else
		return (1);
} 

static int		is_same(char *str, t_varlist **lst)
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

static int			check_error(t_struct *st, int f)
{
	int	i;

	i = 0;
	while (st->cmd[f])
	{
		if (st->cmd[f][0] == '=')
		{
			ft_putstr_fd("bash: export: \"", 2);
			ft_putstr_fd(st->cmd[f], 2);
			ft_putstr_fd("\" : unvalable argument\n", 2);
			return (1);
		}
		else
		{
			while (st->cmd[f][i] != '=' && st->cmd[f][i])
			{
				if (!is_ok(st->cmd[f][i]))
					i++;
				else
				{
					not_cmd(st->cmd[f], st);
					return (1);
				}
			}
			f++;
		}
	}
	return (0);
}

static void		modif_list(char *name, char *content, int visible, t_varlist **lst)
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

void			create_elem(int f, int visible, t_struct *st)
{
	int			i;
	int			j;
	char		*name;
	char		*content;
	t_varlist	*current;

	if (check_error(st, f))
		return ;
	while (st->cmd[f])
	{
		if (ft_strchr(st->cmd[f], '='))
		{
			i = 0;
			while (st->cmd[f][i] != '=')
				i++;
			if (!(name = malloc(sizeof(char) * i + 1)))
				return ;
			i = 0;
			while (st->cmd[f][i] != '=')
			{
				name[i] = st->cmd[f][i];
				i++;
			}
			name[i] = '\0';
			i += 1;
			if (!(content = malloc(sizeof(char) * ft_strlen(st->cmd[f] + i) + 1)))
				return ;
			j = 0;
			while (st->cmd[f][i])
			{
				content[j] = st->cmd[f][i];
				i++;
				j++;
			}
			content[j] = '\0';
			if (!is_same(name, &st->lst))
				create_list(name, content, visible, &st->lst);
			else
				modif_list(name, content, visible, &st->lst);
		}
		else
		{
			if (is_same(st->cmd[f], &st->lst))
			{
				current = st->lst;
				while (current->next)
				{
					if (!ft_strcmp(current->name, st->cmd[f]))
					{
						current->visible = 1;
						return ;
					}
					else
						current = current->next;
				}
				if (!ft_strcmp(current->name, st->cmd[f]))
					current->visible = 1;
			}
			else
				create_list(st->cmd[f], NULL, 1, &st->lst);
		}
		f++;
	}
}

void			ft_export(t_struct *st, int f)
{
	if (f == 2)
	{
		if (!st->cmd[1])
			printlist_export(&st->lst);
		else
			return (create_elem(1, 1, st));
	}
	else
		return (create_elem(0, 0, st));
}
