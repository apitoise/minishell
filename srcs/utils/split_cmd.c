/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:56 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/20 19:00:57 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	ft_nb_w(char const *s, char c)
{
	size_t	i;
	size_t	nb;
    char    spec;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
		{
			if (s[i] == '\\')
				i++;
			i++;
		}
        if (s[i] && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
        {
            spec = s[i];
            nb++;
            while (s[i] && s[i] == spec)
                i++;
        }
		if (s[i] && s[i] != c)
		{
			nb++;
			while (s[i] && s[i] != c && s[i] != '>' && s[i] != '<'
            && s[i] != '|')
			{
				if (s[i] == '\\')
					i++;
				i++;
			}
		}
	}
	return (nb);
}

static char *ft_malloc_chevron(const char *str, char c)
{
    int     i;
    char    *word;

    i = 0;
    while (str[i] && str[i] == c)
        i++;
    if (!(word = (char *)malloc(sizeof(char) * i + 1)))
        return (NULL);
    i = 0;
    while (str[i] && str[i] == c)
    {
        word[i] = str[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

static char	*ft_malloc_w(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c && s[i] != '>' && s[i] != '<'
    && s[i] != '|')
	{
		if (s[i] == '\\')
			i++;
		i++;
	}
	if (!(word = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c && s[i] != '>' && s[i] != '<'
    && s[i] != '|')
	{
		if (s[i] == '\\')
		{
			word[i] = s[i];
			word[i + 1] = s[i + 1];
			i += 2;
		}
		else
		{
			word[i] = s[i];
			i++;
		}
	}
	word[i] = '\0';
	return (word);
}

char		**ft_split_cmd(char const *s, char c, t_struct *st)
{
	char	**tab;
	int		i;
    char    spec;

	if (!s)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (ft_nb_w(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
        if (*s && (*s == '>' || *s == '<' || *s == '|'))
        {
			if (*s == '|')
				st->pipe++;
            spec = *s;
            tab[i] = ft_malloc_chevron(s, *s);
            i++;
            while (*s && *s == spec)
                s++;
        }
		if (*s && (*s != c && *s != '>'
        && *s != '<' && *s != '|'))
		{
			tab[i] = ft_malloc_w(s, c);
			i++;
			while (*s && (*s != c && *s != '>'
            && *s != '<' && *s != '|'))
			{
				if (*s == '\\')
					s++;
				s++;
			}
		}
	}
	tab[i] = NULL;
	return (tab);
}
