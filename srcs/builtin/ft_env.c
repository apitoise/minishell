/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:26 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 21:26:30 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void		create_list(char *name, char *content, t_varlist **lst)
{
	t_varlist	*current;
	t_varlist	*new;

	new = malloc(sizeof(t_varlist));
	new->name = name;
	new->content = content;
	new->visible = 1;
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

static void	create_elem(char *env, t_struct *st)
{
	char	*name;
	char	*content;
	int	i;
	int	j;

	i = 0;
	while (env[i] != '=')
		i++;
	if (!(name = malloc(sizeof(char) * (i + 1))))
		return ;
	i = 0;
	while (env[i] != '=')
	{
		name[i] = env[i];
		i++;
	}
	name[i] = '\0';
	i += 1;
	if (!(content = malloc(sizeof(char) * (ft_strlen(env + i) + 1))))
		return ;
	j = 0;
	while (env[i])
	{
		content[j] = env[i];
		i++;
		j++;
	}
	content[j] = '\0';
	create_list(name, content, &st->lst);
}

void	init_lstenv(char **env, t_struct *st)
{
	int	i;

	i = 0;
	while (env[i])
	{
		create_elem(env[i], st);
		i++;
	}
}

char	**get_env(char **env)
{
	int		nb_vars;
	int		i;
	char	**our_env;

	nb_vars = 0;
	while (env[nb_vars])
		nb_vars++;
	if (!(our_env = (char **)malloc(sizeof(char *) * (nb_vars + 1))))
		return (NULL);
	i = 0;
	while (i < nb_vars)
	{
		our_env[i] = ft_strdup(env[i]);
		i++;
	}
	our_env[i] = NULL;
	return (our_env);
}

void	ft_env(t_struct *st)
{
	printlist_env(&st->lst);
}
