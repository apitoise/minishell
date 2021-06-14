/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:36:54 by lgimenez          #+#    #+#             */
/*   Updated: 2021/06/14 18:04:33 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	init_shlvl(t_struct *st)
{
	t_varlist	*current;
	int			tmp1;
	char		*tmp2;
	int			i;

	current = st->lst;
	while (current && ft_strcmp(current->name, "SHLVL"))
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
		tmp2 = ft_itoa(tmp1);
		free(current->content);
		current->content = tmp2;
	}
}

int	elem_error(char *name, char *content)
{
	if (name)
		free(name);
	if (content)
		free(content);
	return (1);
}

int	homenotset(t_struct *st)
{
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	st->ret = 1;
	return (1);
}

void	modif_pwd(char *name, char *content, t_varlist **lst)
{
	t_varlist	*current;

	current = *lst;
	while (current && ft_strcmp(current->name, name))
		current = current->next;
	if (current && current->content)
	{
		free(current->content);
		current->content = content;
	}
	else
		free(content);
}

int	gethomevaluebis(t_varlist *current, char **home, int par, t_struct *st)
{
	if (current)
	{
		if (current->content)
			*home = current->content;
		else
			return (homenotset(st));
	}
	else
	{
		if (par)
			return (homenotset(st));
		*home = getenv("HOME");
		if (!*home)
			return (1);
	}
	return (0);
}
