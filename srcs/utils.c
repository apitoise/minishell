/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 22:30:02 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 18:41:00 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

char			*ft_trim(char const *s1)
{
	size_t		end;
	size_t		len;
    size_t      start;
	char		*res;
    char        c;

    start = 0;
    c = 34;
	if (!s1)
		return (NULL);
	if (s1[start] == '\0')
		return (ft_strdup(""));
    while (s1[start] == c)
	    start++;
	end = ft_strlen((char *)s1) - 1;
	while (s1[end] == c)
		end--;
	len = end - start + 1;
	res = ft_substr(s1, start, len);
	return (res);
}

void print_tab(char **map)
{
    int i;

    i = 0;
    if (!map)
        return ;
    while (map && map[i])
    {
        ft_putendl_fd(map[i++], 1);
    }
}