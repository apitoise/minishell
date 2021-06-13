/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:56 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/11 17:26:21 by apitoise         ###   ########.fr       */
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
			i += get_i(s[i]);
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
				i += get_i(s[i]);
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
	word = (char *)malloc(sizeof(char) * i + 1);
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
		i += get_i(s[i]);
	return (i);
}

static char	*ft_malloc_w(char const *s, char c)
{
	int		i;
	char	*word;

	word = (char *)malloc(sizeof(char) * get_word_len(s, c) + 1);
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

void	ft_split_cmd(char const *s, char c, t_struct *st, int i)
{
	char	spec;

	st->cmd = (char **)malloc(sizeof(char *) * (ft_nb_w(s, c, i) + 1));
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && (*s == '>' || *s == '<' || *s == '|'))
		{
			pipe_or_chevron(*s, st);
			spec = *s;
			st->cmd[i] = ft_malloc_chevron(s, *s);
			i++;
			while (*s && *s == spec)
				s++;
		}
		if (*s && (*s != c && *s != '>' && *s != '<' && *s != '|'))
		{
			st->cmd[i++] = ft_malloc_w(s, c);
			while (*s && (*s != c && *s != '>' && *s != '<' && *s != '|'))
				s += get_i(*s);
		}
	}
	st->cmd[i] = NULL;
}
