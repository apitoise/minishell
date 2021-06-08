/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmdline_dollarbis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:24:51 by lgimenez          #+#    #+#             */
/*   Updated: 2021/06/08 15:57:26 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	ft_dollar_alias_cpybis(char **tmp2, char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
		;
	if (!(*tmp2 = malloc(sizeof(char) * (i * 2 + 1))))
		return (1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\\' || str[i] == '"' || str[i] == '$')
		{
			(*tmp2)[j] = '\\';
			j++;
		}
		(*tmp2)[j] = str[i];
		j++;
	}
	(*tmp2)[j] = '\0';
	return (0);
}

static int	ft_dollar_alias_cpy(char **tmp, char **tmp2, t_struct *st)
{
	t_varlist	*tmplst;

	tmplst = st->lst;
	while (tmplst && ft_strcmp(*tmp, tmplst->name))
		tmplst = tmplst->next;
	if (!tmplst)
	{
		if (!(*tmp2 = malloc(sizeof(char))))
			return (1);
		(*tmp2)[0] = '\0';
	}
	else if (ft_dollar_alias_cpybis(tmp2, tmplst->content))
		return(1);
	return (0);
}

static int	ft_dollar_alias(char **tmp, t_struct *st)
{
	char		*tmp2;

	if ((*tmp)[0] == '\0')
	{
		if (!(tmp2 = malloc(sizeof(char) * 3)))
			return (1);
		tmp2[0] = '\\';
		tmp2[1] = '$';
		tmp2[2] = '\0';
	}
	else if (ft_dollar_alias_cpy(tmp, &tmp2, st))
		return (1);
	free(*tmp);
	*tmp = tmp2;
	return (0);
}

static void	ft_dollar_d_cpy(char **s1, int *i, char **tmp)
{
	int	j;

	if (((*s1)[*i] == '\'' || (*s1)[*i] == '"') && !ft_tkorqt(*s1, *i))
	{
		(*tmp)[0] = '\'';
		(*tmp)[1] = '\0';
	}
	else
	{
		j = 0;
		while ((*s1)[*i] && ft_isalnum((*s1)[*i]))
		{
			(*tmp)[j] = ((*s1)[*i]);
			j++;
			(*i)++;
		}
		(*tmp)[j] = '\0';
	}
}

int			ft_dollar_d(char **s1, int *i, char **s2, t_struct *st)
{
	char	*tmp;
	int		j;
	int		len;

	if ((*s1)[++(*i)] == '?')
	{
		if (!(tmp = ft_itoa(st->ret)))
			return (1);
		(*i)++;
	}
	else
	{
		j = *i;
		len = 0;
		while ((*s1)[j] && ft_isalnum((*s1)[j++]))
			len++;
		if (!(tmp = malloc(sizeof(char) * (len + 2))))
			return (1);
		ft_dollar_d_cpy(s1, i, &tmp);
		if (ft_dollar_alias(&tmp, st))
			return (ft_freestr(tmp));
	}
	if (ft_dollar_cat(s2, &tmp))
		return (ft_freestr(tmp));
	return (0);
}
