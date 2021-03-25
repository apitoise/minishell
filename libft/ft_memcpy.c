/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:20:21 by cnotin            #+#    #+#             */
/*   Updated: 2019/12/06 12:17:20 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	size_t			len;

	len = 0;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	if (!cdst && !csrc)
		return (NULL);
	while (len < n)
	{
		cdst[len] = csrc[len];
		len++;
	}
	return (cdst);
}
