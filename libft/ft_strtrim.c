/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:37:06 by cnotin            #+#    #+#             */
/*   Updated: 2020/04/23 17:07:39 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static size_t	ft_trim(char const *set, char c)
{
	size_t		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i] || c == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	size_t		len;
	char		*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (ft_trim(set, s1[start]))
	{
		if (s1[start] == '\0')
			return (ft_strdup(""));
		start++;
	}
	end = ft_strlen((char *)s1) - 1;
	while (ft_trim(set, s1[end]))
		end--;
	len = end - start + 1;
	res = ft_substr(s1, start, len);
	return (res);
}
