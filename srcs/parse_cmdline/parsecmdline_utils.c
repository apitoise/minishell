/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmdline_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:24:51 by cnotin            #+#    #+#             */
/*   Updated: 2021/06/14 15:21:02 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	ft_dollar_alias_cpybis_loop2(char **tmp2, char *str, int i, int *j)
{
	if (ft_isspechar(str[i]))
	{
		(*tmp2)[*j] = '\\';
		(*j)++;
	}
	(*tmp2)[*j] = str[i];
	(*j)++;
}

void	ft_dollar_alias_cpybis_loop(char **tmp2, char *str, int toq)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ' ' && toq < 1)
		{
			k = i;
			while (str[k] == ' ')
				k++;
			if ((str[k] && i) || (!i && toq < 0))
			{
				(*tmp2)[j] = ' ';
				j++;
			}
			while (str[i + 1] == ' ')
				i++;
		}
		else
			ft_dollar_alias_cpybis_loop2(tmp2, str, i, &j);
	}
	(*tmp2)[j] = '\0';
}

int	ft_isspechar(char c)
{
	if (c == '\'' || c == '"' || c == '\\' || c == '$' || c == ';' || c == ' '
		|| c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	ft_freestr(char *str)
{
	if (str)
		free(str);
	return (1);
}

int	ft_tkorqt(char *str, int i)
{
	int	tickup;
	int	quoteup;
	int	j;

	tickup = 0;
	quoteup = 0;
	j = -1;
	while (++j < i)
	{
		if (str[j] == '\\' && !tickup)
			j++;
		else if (str[j] == '\'' && !quoteup)
			tickup = !tickup;
		else if (str[j] == '"' && !tickup)
		{
			if (!quoteup)
				quoteup = 2;
			else
				quoteup = 0;
		}
	}
	return (tickup + quoteup);
}
