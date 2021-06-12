/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:24:57 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/12 01:25:46 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	create_list(char *name, char *content, t_varlist **lst)
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
	int		i;
	int		j;

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
		content[j++] = env[i++];
	content[j] = '\0';
	create_list(name, content, &st->lst);
}

static void	init_shlvl(t_struct *st)
{
	t_varlist	*current;
	int			tmp1;
	char		*tmp2;
	int			i;

	current = st->lst;
	while(current && ft_strcmp(current->name, "SHLVL"))
		current = current->next;
	if (current && current->content && current->content[0])
	{
		tmp1 = 0;
		i = -1;
		while (current->content[++i])
		{
			if (!ft_isdigit(current->content[i]))
				return ;
			tmp1 = tmp1 * 10 + (current->content[i] - '0');
		}
		tmp1++;
		if (!(tmp2 = ft_itoa(tmp1)))
			return ;
		free(current->content);
		current->content = tmp2;
	}
}

void		init_lstenv(char **env, t_struct *st)
{
	int			i;

	i = -1;
	while (env[++i])
		create_elem(env[i], st);
	init_shlvl(st);
}

char		**get_env(char **env)
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

void		ft_env(t_struct *st)
{
	printlist_env(&st->lst);
}
