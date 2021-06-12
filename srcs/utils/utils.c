/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:28:04 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/11 23:34:49 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void		print_tab(char **map)
{
	int i;

	i = -1;
	if (!map)
		return ;
	while (map && map[++i])
		ft_putendl_fd(map[i], 1);
}

void		printlist_env(t_varlist **lst)
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

static char	*print_it(t_varlist ***lst, t_varlist **cur, t_varlist *tmp)
{
	int	i;

	*cur = **lst;
	if (!ft_strcmp(tmp->name, "_"))
		return (tmp->name);
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(tmp->name, 1);
	if (tmp->content)
	{
		ft_putstr_fd("=\"", 1);
		i = -1;
		while (tmp->content[++i])
		{
			if (tmp->content[i] == '\\' || tmp->content[i] == '"'
			|| tmp->content[i] == '$')
				write(1, "\\", 1);
			write(1, &(tmp->content[i]), 1);
		}
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
	return (tmp->name);
}

static int	print_bis(t_varlist *tmp, t_varlist *current, char *lw, int i)
{
	if (!tmp->name[0] || tmp->name == lw)
		*tmp = *current;
	else
	{
		i = 0;
		while (tmp->name[i] == current->name[i] && tmp->name[i]
				&& current->name[i])
			i++;
		if (current->name[i] < tmp->name[i])
			*tmp = *current;
	}
	return (i);
}

void		printlist_export(t_varlist **lst)
{
	t_varlist	*current;
	t_varlist	tmp;
	char		*lastwrit;
	int			i;

	if (*lst == NULL)
		return ;
	current = *lst;
	lastwrit = "";
	tmp.name = "";
	while (current != NULL)
	{
		i = 0;
		while (lastwrit[i] == current->name[i] && lastwrit[i]
				&& current->name[i])
			i++;
		if (current->name[i] > lastwrit[i])
			print_bis(&tmp, current, lastwrit, i);
		if (current->next == NULL && tmp.name != lastwrit && tmp.visible == 1)
			lastwrit = print_it(&lst, &current, &tmp);
		else
			current = current->next;
	}
}
