/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:04:32 by cnotin            #+#    #+#             */
/*   Updated: 2019/12/06 11:47:46 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	if (!(p = (unsigned char *)malloc(sizeof(unsigned char) * (size * count))))
		return (NULL);
	while (i < size * count)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}
