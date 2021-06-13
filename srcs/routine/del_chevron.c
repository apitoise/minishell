/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_chevron.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:26:17 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/13 19:10:16 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	get_len(char **cmd)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], ">")
			|| !ft_strcmp(cmd[i], ">>")
			|| !ft_strcmp(cmd[i], "<"))
		{
			if (!cmd[i + 2])
				return (len);
			else
				i += 2;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static char	**get_res(char **cmd, int len)
{
	int		i;
	int		j;
	char	**res;

	res = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>")
			|| !ft_strcmp(cmd[i], "<"))
		{
			if (!cmd[i + 2])
			{
				res[j] = NULL;
				return (res);
			}
			i += 2;
		}
		else
			res[j++] = ft_strdup(cmd[i++]);
	}
	res[j] = NULL;
	return (res);
}

char	**del_chevron(char **cmd)
{
	int		len;
	char	**res;

	len = get_len(cmd);
	res = NULL;
	if (len == 0)
	{
		res = (char **)malloc(sizeof(char *) * 2);
		res[0] = ft_strdup("");
		res[1] = NULL;
		ft_free_tab(cmd);
		return (res);
	}
	else
		res = get_res(cmd, len);
	ft_free_tab(cmd);
	return (res);
}
