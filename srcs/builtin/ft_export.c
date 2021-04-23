/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:07 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/23 18:44:05 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	create_list(char *name, char *content, int visible, t_varlist **lst)
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

static int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
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

static void	create_elem(char **cmd, int f, int visible, t_struct *st)
{
	int			i;
	int			j;
	char		*name;
	char		*content;
	t_varlist	*current;

	while (cmd[f])
	{
		if (!check_error(cmd[f]))
		{
			if (ft_strchr(cmd[f], '='))
			{
				i = 0;
				while (cmd[f][i] != '=')
					i++;
				if (!(name = malloc(sizeof(char) * i + 1)))
					return ;
				i = 0;
				while (cmd[f][i] != '=')
				{
					name[i] = cmd[f][i];
					i++;
				}
				name[i] = '\0';
				i += 1;
				if (!(content = malloc(sizeof(char) * ft_strlen(cmd[f] + i) + 1)))
					return ;
				j = 0;
				while (cmd[f][i])
				{
					content[j] = cmd[f][i];
					i++;
					j++;
				}
				content[j] = '\0';
				if (!varexist(name, &st->lst))
					create_list(name, content, visible, &st->lst);
				else
					modif_list(name, content, visible, &st->lst);
			}
			else
			{
				if (varexist(cmd[f], &st->lst))
				{
					current = st->lst;
					while (current->next)
					{
						if (!ft_strcmp(current->name, cmd[f]))
							current->visible = 1;
						current = current->next;
					}
					if (!ft_strcmp(current->name, cmd[f]))
						current->visible = 1;
				}
				else
					create_list(cmd[f], NULL, 1, &st->lst);
			}
		}
		f++;
	}
}

void		ft_export(char **cmd, t_struct *st, int f)
{
	if (f == 2)
	{
		if (!cmd[1])
			printlist_export(&st->lst);
		else
			return (create_elem(cmd, 1, 1, st));
	}
	else
		return (create_elem(cmd, 0, 0, st));
}
