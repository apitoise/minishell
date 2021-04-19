/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 22:30:02 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 18:41:00 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

char			*ft_trim(char const *s1)
{
	size_t		end;
	size_t		len;
    size_t      start;
	char		*res;
    char        c;

    start = 0;
    c = 34;
	if (!s1)
		return (NULL);
	if (s1[start] == '\0')
		return (ft_strdup(""));
    while (s1[start] == c)
	    start++;
	end = ft_strlen((char *)s1) - 1;
	while (s1[end] == c)
		end--;
	len = end - start + 1;
	res = ft_substr(s1, start, len);
	return (res);
}

void print_tab(char **map)
{
    int i;

    i = 0;
    if (!map)
        return ;
    while (map && map[i])
    {
        ft_putendl_fd(map[i++], 1);
    }
}

void 			printlist_env(t_varlist **lst)
{
	t_varlist	*current;

    if (*lst == NULL)
        return ;
    current = *lst;
    while (current != NULL)
    {
	if (current->visible == 1)
	{
    		if (current->content != NULL)
		{
   	 		ft_putstr_fd(current->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current->content, 1);
			ft_putchar_fd('\n', 1);
	    	}
	}
        current = current->next;
    }
}

void 			printlist_export(t_varlist **lst)
{
	t_varlist	*current;
	t_varlist	tmp;
	char		*lastwrit;
	int		i;

	if (*lst == NULL)
		return ;
	current = *lst;
	lastwrit = "";
	tmp.name = "";
	while (current != NULL)
	{
		i = 0;
		while (lastwrit[i] == current->name[i] && lastwrit[i] && current->name[i])
			i++;
		if (current->name[i] > lastwrit[i])
		{
			if (!tmp.name[0] || tmp.name == lastwrit)
				tmp = *current;
			else
			{
				i = 0;
				while (tmp.name[i] == current->name[i] && tmp.name[i] && current->name[i])
					i++;
				if (current->name[i] < tmp.name[i])
					tmp = *current;
			}
		}
		if (current->next == NULL && tmp.name != lastwrit && tmp.visible == 1)
		{
		 	ft_putstr_fd("declare -x ", 1);
		 	ft_putstr_fd(tmp.name, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp.content, 1);
			ft_putstr_fd("\"\n", 1);
			lastwrit = tmp.name;
			current = *lst;
		}
		else
			current = current->next;
	}
}

