/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:32 by cnotin            #+#    #+#             */
/*   Updated: 2021/04/08 13:09:37 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

static void	print_ret(t_struct *st)
{
	ft_putnbr_fd(st->ret, 1);
	st->ret = 0;
	return ;
}

static void	print_var(const char *res, t_varlist **lst, t_struct *st)
{
	t_varlist	*current;

	if (res[0] == '?')
		return (print_ret(st));
	if (!res[0])
		ft_putchar_fd('$', 1);
	if (*lst == NULL)
		return ;
	current = *lst;
	while (current->next)
	{
		if (!ft_strcmp(res, current->name))
			ft_putstr_fd(current->content, 1);
		current = current->next;
	}
	if (!ft_strcmp(res, current->name))
		ft_putstr_fd(current->content, 1);
	return ;
}

int	ft_echo(char **cmd, t_varlist **lst, t_struct *st)
{
	int			i;
	int 		n;
	char 		*res;

	i = 1;
	n = 0;
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
		n = 1;
	i += n;
	check_cmd(cmd, i);
	while (cmd[i])
	{
		res = ft_trim(cmd[i]);
		if (res[0] == '$')
			print_var(res + 1, lst, st);
		else
			ft_putstr_fd(res, 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		free(res);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	st->ret = 0;
	return (0);
}
