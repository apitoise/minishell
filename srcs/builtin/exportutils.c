/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:07 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/08 02:08:21 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	xp_newlst(char *name, char *content, int visible, t_varlist **lst)
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
	return (0);
}

int	xp_checkerror(char *arg, t_struct *st)
{
	int	i;

	if (!ft_isalpha(arg[0]))
		return (xp_idnotvalid(arg, st));
	i = 0;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]))
			return (xp_idnotvalid(arg, st));
		i++;
	}
	if (arg[i] == '+' && arg[i + 1] != '=')
		return (xp_idnotvalid(arg, st));
	return (0);
}

void	xp_modiflist(char *name, char *content, int visible, t_varlist **lst)
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

int	xp_catlist(char *name, char *content, t_varlist **lst)
{
	t_varlist	*current;
	char		*tmp;

	current = *lst;
	while (current && ft_strcmp(current->name, name))
		current = current->next;
	tmp = ft_strjoin(current->content, content);
	if (!current)
		return (1);
	free(current->content);
	current->content = tmp;
	free(name);
	free(content);
	return (0);
}

char	*xp_getname(char *cmd, char c)
{
	char	*name;
	int		i;

	i = -1;
	while (cmd[++i] != c && cmd[i])
		;
	name = malloc(sizeof(char) * i + 1);
	if (!cmd[i])
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
