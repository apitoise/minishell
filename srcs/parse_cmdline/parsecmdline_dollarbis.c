/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmdline_dollarbis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:24:51 by lgimenez          #+#    #+#             */
/*   Updated: 2021/06/14 15:19:30 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	ft_dollar_alias_cpybis(char **tmp2, char *str, int toq)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	*tmp2 = malloc(sizeof(char) * (i * 2 + 1));
	ft_dollar_alias_cpybis_loop(tmp2, str, toq);
}

static void	ft_dollar_alias_cpy(char **tmp, char **tmp2, t_struct *st, int toq)
{
	t_varlist	*tmplst;

	tmplst = st->lst;
	while (tmplst && ft_strcmp(*tmp, tmplst->name))
		tmplst = tmplst->next;
	if (!tmplst)
	{
		*tmp2 = malloc(sizeof(char));
		(*tmp2)[0] = '\0';
	}
	else
		ft_dollar_alias_cpybis(tmp2, tmplst->content, toq);
}

static void	ft_dollar_alias(char **tmp, t_struct *st, int toq, int par)
{
	char	*tmp2;

	if (!toq && par)
		toq = -1;
	if ((*tmp)[0] == '\0')
	{
		tmp2 = malloc(sizeof(char) * 3);
		tmp2[0] = '\\';
		tmp2[1] = '$';
		tmp2[2] = '\0';
	}
	else
		ft_dollar_alias_cpy(tmp, &tmp2, st, toq);
	free(*tmp);
	*tmp = tmp2;
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

int	ft_dollar_d(char **s1, int *i, char **s2, t_struct *st)
{
	char	*tmp;
	int		j;
	int		len;
	int		par;

	if ((*s1)[++(*i)] == '?')
	{
		tmp = ft_itoa(st->ret);
		(*i)++;
	}
	else
	{
		j = *i;
		len = 0;
		while ((*s1)[j] && ft_isalnum((*s1)[j++]))
			len++;
		tmp = malloc(sizeof(char) * (len + 2));
		ft_dollar_d_cpy(s1, i, &tmp);
		par = 0;
		if (*i > 2 && (*s1)[*i - 3] != ' ')
			par = 1;
		ft_dollar_alias(&tmp, st, ft_tkorqt(*s1, *i), par);
	}
	ft_dollar_cat(s2, &tmp);
	return (0);
}
