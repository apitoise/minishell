/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsecmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:24:51 by lgimenez          #+#    #+#             */
/*   Updated: 2019/12/06 12:03:31 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_parsecmdline(char **s, t_struct *st)
{
	if (!*s || ft_checknewline(*s) || ft_dollar(s, st) || ft_addbslash(s)
		|| ft_rmbslash(s, -1, 0))
	{
		if (*s)
			free(*s);
		return (1);
	}
	printf("s: %s\n", *s);
	return (0);
}
