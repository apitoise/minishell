/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmdline_rmbslash.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:24:51 by lgimenez          #+#    #+#             */
/*   Updated: 2019/12/06 12:03:31 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_rmbslash(char **s, int i, int j)
{
	char	*tmp;

	if (!(tmp = malloc(sizeof(char) * (ft_strlen(*s) + 1))))
		return (1);
	while ((*s)[++i])
	{
		if ((*s)[i] == '\\' && ft_isspechar((*s)[i + 1]))
		{
			tmp[j] = (*s)[i];
			tmp[j + 1] = (*s)[i + 1];
			j += 2;
			i++;
		}
		else if ((*s)[i] != '\\')
		{
			tmp[j] = (*s)[i];
			j++;
		}
	}
	tmp[j] = '\0';
	free(*s);
	*s = tmp;
	return (0);
}
