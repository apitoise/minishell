/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:56 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/07 16:16:55 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	ft_nb_w(char const *s, char c, int i)
{
	size_t	nb;
	char	spec;

	nb = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i += s[i] == '\\' ? 2 : 1;
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
				i += s[i] == '\\' ? 2 : 1;
		}
	}
	return (nb);
}

static char	*ft_malloc_chevron(const char *str, char c)
{
	int		i;
	char	*word;

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

static int	get_word_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c && s[i] != '>' && s[i] != '<'
			&& s[i] != '|')
		i += s[i] == '\\' ? 2 : 1;
	return (i);
}

static char	*ft_malloc_w(char const *s, char c)
{
	int		i;
	char	*word;

	if (!(word = (char *)malloc(sizeof(char) * get_word_len(s, c) + 1)))
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
	char	**tabl;
	int		i;
	char	spec;

	if (!s)
		return (NULL);
	i = 0;
	if (!(tabl = (char **)malloc(sizeof(char *) * (ft_nb_w(s, c, i) + 1))))
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && (*s == '>' || *s == '<' || *s == '|'))
		{
			st->pipe += *s == '|' ? 1 : 0;
			spec = *s;
			tabl[i] = ft_malloc_chevron(s, *s);
			i++;
			while (*s && *s == spec)
				s++;
		}
		if (*s && (*s != c && *s != '>'
					&& *s != '<' && *s != '|'))
		{
			tabl[i] = ft_malloc_w(s, c);
			i++;
			while (*s && (*s != c && *s != '>'
						&& *s != '<' && *s != '|'))
				s += *s == '\\' ? 2 : 1;
		}
	}
	tabl[i] = NULL;
	return (tabl);
}
