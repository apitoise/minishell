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
    	ft_putchar_fd('=', 1);
    	ft_putstr_fd(current->content, 1);
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

void			create_elem(char **cmd, t_varlist **lst, int f)
{
	int			i;
	int			j;
	char		*name;
	char		*content;

	i = 0;
	while (cmd[f][i] != '=')
	{
		if (!is_ok(cmd[f][i]))
			i++;
		else
			return ;
	}
	name = malloc(sizeof(char) * i + 1);
	i = 0;
	while (cmd[f][i] != '=')
	{
		name[i] = cmd[f][i];
		i++;
	}
	name[i] = '\0';
	i += 1;
	content = malloc(sizeof(char) * ft_strlen(cmd[f] + i) + 1);
	j = 0;
	while (cmd[f][i])
	{
		content[j] = cmd[f][i];
		i++;
		j++;
	}
	content[j] = '\0';
	if (!is_same(name, lst))
		return (create_list(name, content, lst));
	else
		return (modif_list(name, content, lst));
}

void			ft_export(char **cmd, t_varlist **lst, int f)
{
	if (f == 2)
	{
		if (!cmd[1])
			printList(lst);
		else
			return (create_elem(cmd, lst, 1));
	}
	else
		return (create_elem(cmd, lst, 0));
}