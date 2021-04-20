/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:24:51 by cnotin            #+#    #+#             */
/*   Updated: 2021/04/20 16:33:11 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	ft_nb_w(char const *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			nb++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (nb);
}

static char	*ft_malloc_w(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(word = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char		**ft_split_cmdline(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (ft_nb_w(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
		{
			if (*(s++) == '\\')
				s++;
		}
		if (*s && *s != c)
		{
			tab[i] = ft_malloc_w(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
