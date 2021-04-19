/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:25:37 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/19 15:25:38 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int			first_check(char **cmd)
{
	int	i;

	i = 0;
	while(cmd[i])
	{
		if ((cmd[i][0] == '<' || cmd[i][0] == '|')
		&& (ft_strlen(cmd[i]) > 1))
			return (syntax_error(cmd[i]));
		else if ((!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>")
		|| !ft_strcmp(cmd[i], "<") || !ft_strcmp(cmd[i], "|"))
		&& !cmd[i + 1])
			return (syntax_error("newline"));
		else if (cmd[i][0] == '>' && ft_strlen(cmd[i]) > 2)
			return (syntax_error(">"));
		else if ((cmd[i][0] == '>' || cmd[i][0] == '<')
		&& (cmd[i + 1][0] == '>' || cmd[i + 1][0] == '<'
		|| cmd[i + 1][0] == '|'))
			return (syntax_error(cmd[i]));
		i++;
	}
	return (0);
}
