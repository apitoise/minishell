/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmdline_addbslash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:24:51 by lgimenez          #+#    #+#             */
/*   Updated: 2019/12/06 12:03:31 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	ft_addbslash_loopqt(char **s, int *i, char **tmp, int *j)
{
	if (ft_tkorqt(*s, *i) == 1)
	{
		(*tmp)[*j] = '\\';
		(*tmp)[*j + 1] = '"';
		*j += 2;
	}
	else
	{
		(*tmp)[*j] = '"';
		(*j)++;
	}
}

static void	ft_addbslash_looptk(char **s, int *i, char **tmp, int *j)
{
	if (ft_tkorqt(*s, *i) == 2)
	{
		(*tmp)[*j] = '\\';
		(*tmp)[*j + 1] = '\'';
		*j += 2;
	}
	else
	{
		(*tmp)[*j] = '\'';
		(*j)++;
	}
}

static void	ft_addbslash_loopbs(char **s, int *i, char **tmp, int *j)
{
	if (!ft_tkorqt(*s, *i) || (ft_tkorqt(*s, *i) == 2
		&& ((*s)[*i + 1] == '\\' || (*s)[*i + 1] == '$'
		|| (*s)[*i + 1] == '"')))
	{
		(*tmp)[*j] = (*s)[*i];
		(*tmp)[*j + 1] = (*s)[*i + 1];
		*j += 2;
		(*i)++;
	}
	else
	{
		(*tmp)[*j] = '\\';
		(*tmp)[*j + 1] = '\\';
		*j += 2;
	}
}

static void	ft_addbslash_loop(char **s, char **tmp)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while ((*s)[++i])
	{
		if ((*s)[i] == '\\')
			ft_addbslash_loopbs(s, &i, tmp, &j);
		else if ((*s)[i] == '\'')
			ft_addbslash_looptk(s, &i, tmp, &j);
		else if ((*s)[i] == '"')
			ft_addbslash_loopqt(s, &i, tmp, &j);
		else if (ft_isspechar((*s)[i]) && ft_tkorqt(*s, i))
		{
			(*tmp)[j] = '\\';
			(*tmp)[j + 1] = (*s)[i];
			j += 2;
		}
		else
			(*tmp)[j++] = (*s)[i];
	}
	(*tmp)[j] = '\0';
}

int			ft_addbslash(char **s)
{
	char	*tmp;
	int		i;
	int		nbrbackslash;

	i = -1;
	nbrbackslash = 0;
	while ((*s)[++i])
	{
		if (ft_isspechar((*s)[i]))
			nbrbackslash++;
	}
	if (!(tmp = malloc(sizeof(char) * (ft_strlen(*s) + nbrbackslash + 1))))
		return (1);
	ft_addbslash_loop(s, &tmp);
	free(*s);
	*s = tmp;
	return (0);
}
