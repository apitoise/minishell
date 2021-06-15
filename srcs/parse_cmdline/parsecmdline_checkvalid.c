/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmdline_checkvalid.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:16:26 by lgimenez          #+#    #+#             */
/*   Updated: 2021/06/15 20:12:04 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	semicolon(char *s, t_struct *st)
{
	int	i;
	int	j;

	if (s[0] == ';')
		return (ft_syntax_error(";", st));
	i = -1;
	while (s[++i])
	{
		if (s[i] == ';' && s[i - 1] != '\\' && !ft_tkorqt(s, i))
		{
			j = i - 1;
			while (j >= 0 && s[j] == ' ')
				--j;
			if (j < 0 || s[j] == ';' || s[j] == '>' || s[j] == '<'
				|| s[j] == '|')
				return (ft_syntax_error(";", st));
		}
	}
	return (0);
}

static int	new_line(char *s, t_struct *st)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	if (i)
		--i;
	if (((s[i] == '\\') && (!i || s[i - 1] != '\\')) || ft_tkorqt(s, i + 1))
		return (ft_syntax_error("newline", st));
	if (((s[i] == '>' || s[i] == '<' || s[i] == '|')
			&& (!i || s[i - 1] != '\\')) || ft_tkorqt(s, i + 1))
		return (ft_syntax_error(s + i, st));
	return (0);
}

int	ft_checkvalid(char *s, t_struct *st)
{
	if (semicolon(s, st) || new_line(s, st))
		return (1);
	return (0);
}
