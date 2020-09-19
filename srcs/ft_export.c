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

void 			printList(t_varlist **lst)
{
	t_varlist	*current;

    if (*lst == NULL)
        return ;
    current = *lst;
    while (current != NULL)
    {
    	ft_putstr_fd(current->name, 1);
    	if (current->content != NULL)
    	{
    		ft_putchar_fd('=', 1);
    		ft_putstr_fd(current->content, 1);
    	}
    	ft_putchar_fd('\n', 1);
        current = current->next;
    }
}

static void		create_list(char *name, char *content, t_varlist **lst)
{
	t_varlist	*current;
	t_varlist	*new;

	new = malloc(sizeof(t_varlist));
	new->name = name;
	new->content = content;
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

static int			check_error(t_struct *st, int f)
{
	int	i;

	i = 0;
	while (st->cmd[f])
	{
		if (st->cmd[f][0] == '=')
		{
			ft_putstr_fd("bash: export: \"", 1);
			ft_putstr_fd(st->cmd[f], 1);
			ft_putstr_fd("\" : unvalable argument\n", 1);
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
			if (st->cmd[f][i] == '\0')
			{
				not_cmd(st->cmd[f], st);
				return (1);
			}
			f++;
		}
	}
	return (0);
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

static void		modif_list(char *name, char *content, t_varlist **lst)
{
	t_varlist	*current;

	current = *lst;
	while (ft_strcmp(current->name, name) && current->next)
		current = current->next;
	free(current->content);
	current->content = content;
	free(name);
}

void			create_elem(int f, t_struct *st)
{
	int			i;
	int			j;
	char		*name;
	char		*content;

	if (!(check_error(st, f)))
	{
		while (st->cmd[f])
		{
			i = 0;
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
				create_list(name, content, &st->lst);
			else
				modif_list(name, content, &st->lst);
			f++;
		}
	}
}

void			ft_export(t_struct *st, int f)
{
	if (f == 2)
	{
		if (!st->cmd[1])
			printList(&st->lst);
		else
			return (create_elem(1, st));
	}
	else
		return (create_elem(0, st));
}