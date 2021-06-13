/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:37 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/07 13:42:42 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	first_check(char **cmd, t_struct *st)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i][0] == '<' || cmd[i][0] == '|')
				&& (ft_strlen(cmd[i]) > 1))
			return (ft_syntax_error(cmd[i], st));
		else if (cmd[0][0] == '|')
			return (ft_syntax_error("|", st));
		else if ((!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>")
				|| !ft_strcmp(cmd[i], "<") || !ft_strcmp(cmd[i], "|"))
			&& !cmd[i + 1])
			return (ft_syntax_error("newline", st));
		else if (cmd[i][0] == '>' && ft_strlen(cmd[i]) > 2)
			return (ft_syntax_error(">", st));
		else if ((cmd[i][0] == '>' || cmd[i][0] == '<') && (cmd[i + 1][0] == '>'
			|| cmd[i + 1][0] == '<' || cmd[i + 1][0] == '|'))
			return (ft_syntax_error(cmd[i + 1], st));
		else if (!ft_strcmp(cmd[i], "|") && !ft_strcmp(cmd[i + 1], "|"))
			return (ft_syntax_error("|", st));
		i++;
	}
	return (0);
}
