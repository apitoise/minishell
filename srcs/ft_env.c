/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:23:26 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 21:26:30 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

char	**get_env(char **env)
{
	int		nb_vars;
	int		i;
	char	**our_env;

	nb_vars = 0;
	while (env[nb_vars])
		nb_vars++;
	if (!(our_env = (char **)malloc(sizeof(char *) * (nb_vars + 1))))
		return (NULL);
	i = 0;
	while (i < nb_vars)
	{
		our_env[i] = ft_strdup(env[i]);
		i++;
	}
	our_env[i] = NULL;
	return (our_env);
}

int		ft_env(char **env)
{
	print_tab(env);
	return (0);
}
