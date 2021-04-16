/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 19:38:00 by cnotin            #+#    #+#             */
/*   Updated: 2020/06/29 19:38:03 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (-1);
	i = 0;
	j = 0;
	while (((unsigned char)s1[i] == (unsigned char)s2[j]) && (s1[i] || s2[j]))
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
