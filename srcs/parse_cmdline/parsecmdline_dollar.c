/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmdline_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:24:51 by lgimenez          #+#    #+#             */
/*   Updated: 2021/04/19 17:36:21 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_dollar_cat(char **s2, char **tmp)
{
	char	*s3;
	int		i;
	int		j;

	i = -1;
	while ((*s2)[++i])
		;
	j = -1;
	while ((*tmp)[++j])
		;
	s3 = malloc(sizeof(char) * (i + j + 1));
	i = -1;
	j = 0;
	while ((*s2)[++i])
		s3[j++] = (*s2)[i];
	i = -1;
	while ((*tmp)[++i])
		s3[j++] = (*tmp)[i];
	s3[j] = '\0';
	free(*s2);
	free(*tmp);
	*s2 = s3;
	return (0);
}

static void	ft_dollar_notd_cpy(char **s1, int *i, char **tmp)
{
	int	j;

	j = 0;
	while ((*s1)[*i] && (*s1)[*i] != '$')
	{
		if (((*s1)[*i] == '\\' && ft_tkorqt(*s1, *i) != 1)
			|| ((*s1)[*i + 1] == '$' && ft_tkorqt(*s1, *i + 1) == 1))
		{
			(*tmp)[j] = ((*s1)[*i]);
			(*tmp)[j + 1] = ((*s1)[*i + 1]);
			j += 2;
			*i += 2;
		}
		else
		{
			(*tmp)[j] = ((*s1)[*i]);
			j++;
			(*i)++;
		}
	}
	(*tmp)[j] = '\0';
}

static int	ft_dollar_notd(char **s1, int *i, char **s2)
{
	char	*tmp;
	int		j;
	int		len;

	j = *i;
	len = 0;
	while ((*s1)[j] && (*s1)[j] != '$')
	{
		if (((*s1)[j] == '\\' && ft_tkorqt(*s1, j) != 1)
			|| ((*s1)[j + 1] == '$' && ft_tkorqt(*s1, j + 1) == 1))
		{
			len++;
			j++;
		}
		len++;
		j++;
	}
	tmp = malloc(sizeof(char) * (len + 1));
	ft_dollar_notd_cpy(s1, i, &tmp);
	if (ft_dollar_cat(s2, &tmp))
		return (ft_freestr(tmp));
	return (0);
}

int	ft_dollar(char **s1, t_struct *st)
{
	char	*s2;
	int		i;

	s2 = malloc(sizeof(char));
	s2[0] = '\0';
	i = 0;
	while ((*s1)[i])
	{
		if (((*s1)[i] != '$' || ft_tkorqt(*s1, i) == 1))
		{
			if (ft_dollar_notd(s1, &i, &s2))
				return (ft_freestr(s2));
		}
		else if (ft_dollar_d(s1, &i, &s2, st))
			return (ft_freestr(s2));
	}
	free(*s1);
	*s1 = s2;
	return (0);
}
