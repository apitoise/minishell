/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:21:18 by cnotin            #+#    #+#             */
/*   Updated: 2019/12/06 12:02:02 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	size_t			i;

	if (src == dst)
		return (dst);
	i = 0;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	if (csrc < cdst)
	{
		while (len--)
			cdst[len] = csrc[len];
	}
	else
	{
		while (i < len)
		{
			cdst[i] = csrc[i];
			i++;
		}
	}
	return (cdst);
}
