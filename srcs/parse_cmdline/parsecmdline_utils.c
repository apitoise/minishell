/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmdline_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:24:51 by cnotin            #+#    #+#             */
/*   Updated: 2021/04/20 13:17:42 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

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
			quoteup = !quoteup ? 2 : 0;
	}
	return (tickup + quoteup);
}
