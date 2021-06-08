/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:10:52 by lgimenez          #+#    #+#             */
/*   Updated: 2021/06/07 21:12:26 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	ft_nb_w(char *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && !(s[i] == c && !ft_tkorqt(s, i)))
		{
			nb++;
			while (s[i] && !(s[i] == c && !ft_tkorqt(s, i)))
			{
				if (s[i] == '\\')
					i++;
				i++;
			}
		}
	}
	return (nb);
}

static char	*ft_malloc_w(char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && !(s[i] == c && !ft_tkorqt(s, i)))
	{
		if (s[i] == '\\')
			i++;
		i++;
	}
	if (!(word = (char *)malloc(sizeof(char) * (i * 2 + 1))))
		return (NULL);
	i = 0;
	while (s[i] && !(s[i] == c && !ft_tkorqt(s, i)))
	{
		word[i] = s[i];
		if (s[i] == '\\')
		{
			++i;
			word[i] = s[i];
		}
		++i;
	}
	word[i] = '\0';
	return (word);
}

char		**ft_split_cmdline(char *s, char c)
{
	char	**tabl;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (!(tabl = (char **)malloc(sizeof(char *) * (ft_nb_w(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j] && !(s[j] == c && !ft_tkorqt(s, j)))
		{
			tabl[i++] = ft_malloc_w(s + j, c);
			while (s[j] && !(s[j] == c && !ft_tkorqt(s, j)))
			{
				if (s[j] == '\\')
					j++;
				j++;
			}
		}
	}
	tabl[i] = NULL;
	return (tabl);
}
