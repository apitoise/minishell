/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:32 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 18:41:19 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

static void	print_var(const char *res, t_varlist **lst)
{
	int			i;
	t_varlist	*current;

	i = 0;
	if (!res[i])
		ft_putchar_fd('$', 1);
	if (*lst == NULL)
		return ;
	while (current->next)
	{
		if (!ft_strcmp(res, current->name))
			ft_putstr_fd(current->content, 1);
		else
			current = current->next;
	}
	if (!ft_strcmp(res, current->name))
		ft_putstr_fd(current->content, 1);
	return ;
}

int	ft_echo(char **cmd, t_varlist **lst)
{
	int	i;
	int n;
	char *res;

	i = 1;
	n = 0;
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
		n = 1;
	i += n;
	while (cmd[i])
	{
		res = ft_trim(cmd[i]);
		if (res[0] == '$')
			print_var(res + 1, lst);
		else
			ft_putstr_fd(res, 2);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		free(res);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (0);
}
