/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:52:11 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/31 22:46:09 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	cd_getoldpwd(char **path, t_struct *st)
{
	t_varlist	*current;

	current = st->lst;
	while (current && ft_strcmp(current->name, "OLDPWD"))
		current = current->next;
	if (!current)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 1);
		return (1);
	}
	if (!(*path = ft_strdup(current->content)))
		return (1);
	return (0);
}
