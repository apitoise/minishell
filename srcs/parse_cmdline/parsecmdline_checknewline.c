/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmdline_checknewline.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:24:51 by lgimenez          #+#    #+#             */
/*   Updated: 2019/12/06 12:03:31 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_checknewline(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	if ((i && (s[i - 1] == '\\' || s[i - 1] == '>'
		|| s[i - 1] == '<' || s[i - 1] == '|')) || ft_tkorqt(s, i))
	{
		ft_putstr_fd("minishell : syntax error", 2);
		ft_putstr_fd(" near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}
