/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varlstclear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 23:37:23 by lgimenez          #+#    #+#             */
/*   Updated: 2021/06/04 23:39:28 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	ft_varlstclear(t_varlist **lst)
{
	if (lst && *lst)
	{
		if ((*lst)->next)
			ft_varlstclear((t_varlist **)&(*lst)->next);
		free((*lst)->name);
		if ((*lst)->content)
			free((*lst)->content);
		free(*lst);
	}
}
