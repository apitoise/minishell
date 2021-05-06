/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:24:20 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/19 15:24:21 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	ft_varlstclear(t_varlist **lst, void (*del)(void*))
{
	t_varlist *current;

	if (lst && del)
	{
		current = *lst;
		while (current)
		{
			del(current->content);
			del(current->name);
			free(current);
			current = current->next;
		}
	}
}

static void	ft_del_elem(void *content)
{
	free(content);
}

void		ft_exit(char **cmd, t_struct *st)
{
	if (cmd == NULL)
	{
		exit(EXIT_SUCCESS);
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	ft_free_tab(cmd);
	free(st->input);
	if (st->env)
		ft_free_tab(st->env);
	ft_varlstclear(&st->lst, &ft_del_elem);
	exit(EXIT_SUCCESS);
}
