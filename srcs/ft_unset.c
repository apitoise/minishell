/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:03 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/25 21:23:05 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

int	ft_unset(t_struct *st)
{
	st = NULL;
	printf("%s \n", st->s);
	printf("unset\n");
	return (0);
}
