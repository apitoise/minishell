/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 09:14:26 by cnotin            #+#    #+#             */
/*   Updated: 2020/03/04 18:46:20 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_numlen(long n, int base)
{
	int i;

	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

char		*ft_itoa_base(long n, int base, int maj)
{
	char	*str;
	char	letter;
	long	digit;
	int		len;

	if (!n)
		return (ft_strdup("0"));
	letter = maj ? 'A' : 'a';
	len = ft_numlen(n, base);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	while (n)
	{
		digit = n % base;
		n /= base;
		str[len--] = (digit < 10) ? ('0' + digit) : (letter + digit - 10);
	}
	return (str);
}
