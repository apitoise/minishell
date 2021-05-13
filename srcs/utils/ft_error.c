/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:29 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/11 18:22:55 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int		ft_error(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (errno);
}

void	ft_clean_exit(char *cmd, t_struct *st)
{
	free(cmd);
	free(st->input);
	if (st->env)
		ft_free_tab(st->env);
	ft_varlstclear(&st->lst);
	exit(EXIT_SUCCESS);
}

void	not_cmd(char *str, t_struct *st)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : command not found\n", 2);
	st->ret = 127;
	ft_clean_exit(str, st);
}
