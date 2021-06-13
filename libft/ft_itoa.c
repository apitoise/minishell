/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:06:55 by cnotin            #+#    #+#             */
/*   Updated: 2020/03/03 14:45:39 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_nb_len(long n)
{
	int		count;

	count = 0;
	if (n <= 0)
	{
		count++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(long n)
{
	char	*res;
	long	i;

	i = ft_nb_len(n);
	res = (char *)malloc(sizeof(char) * i + 1);
	if (n == -2147483648)
		return ("-2147483648");
	res[i] = '\0';
	i--;
	if (n == 0)
		res[i] = '0';
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		res[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	return (res);
}
