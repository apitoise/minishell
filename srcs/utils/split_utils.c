/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:58:41 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/12 15:07:48 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	get_i(char c)
{
	if (c == '\\')
		return (2);
	else
		return (1);
}

void	pipe_or_chevron(char c, t_struct *st)
{
	if (c == '|')
		st->pipe++;
	else
		st->chevrons++;
}
