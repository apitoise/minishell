/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:22:15 by cnotin            #+#    #+#             */
/*   Updated: 2019/12/06 11:51:42 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ch;
	size_t			i;

	ch = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ch[i] = (unsigned char)c;
		i++;
	}
	return (ch);
}
