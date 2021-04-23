/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:28:04 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/23 18:08:53 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void print_tab(char **map)
{
	int i;

	i = -1;
	if (!map)
		return ;
	while (map && map[++i])
		ft_putendl_fd(map[i], 1);
}

void 			printlist_env(t_varlist **lst)
{
	t_varlist	*current;

	if (*lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		if (current->visible == 1)
		{
			if (current->content != NULL)
			{
				ft_putstr_fd(current->name, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(current->content, 1);
				ft_putchar_fd('\n', 1);
			}
		}
		current = current->next;
	}
}

static	void	putvar(char *name, char *content)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(name, 1);
	if (content)
	{
		ft_putstr_fd("=\"", 1);
		while (*content)
		{
			if (*content == '\\' || *content == '$')
				ft_putchar_fd('\\', 1);
			ft_putchar_fd(*content, 1);
			content++;
		}
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}

void 			printlist_export(t_varlist **lst)
{
	t_varlist	*current;
	t_varlist	tmp;
	char		*lastwrit;
	int		i;

	if (*lst == NULL)
		return ;
	current = *lst;
	lastwrit = "";
	tmp.name = "";
	while (current != NULL)
	{
		i = 0;
		while (lastwrit[i] == current->name[i] && lastwrit[i] && current->name[i])
			i++;
		if (current->name[i] > lastwrit[i])
		{
			if (!tmp.name[0] || tmp.name == lastwrit)
				tmp = *current;
			else
			{
				i = 0;
				while (tmp.name[i] == current->name[i] && tmp.name[i] && current->name[i])
					i++;
				if (current->name[i] < tmp.name[i])
					tmp = *current;
			}
		}
		if (current->next == NULL && tmp.name != lastwrit)
		{
			if (tmp.visible && ft_strcmp(tmp.name, "_"))
				putvar(tmp.name, tmp.content);
			lastwrit = tmp.name;
			current = *lst;
		}
		else
			current = current->next;
	}
}

