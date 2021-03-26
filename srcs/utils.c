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

#include "../headers/minishell.h"
#include "../libft/libft.h"

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
	t_varlist	*tmp;
	char		*prevname;

    if (*lst == NULL)
        return ;
    current = *lst;
    while (true)
    {
	    prevname = "";
	    tmp = current;
	    while (current != NULL)
	    {
		i = 0;
		while (prevname[i] == current->name[i] && prevname[i])
			i++;
		if (prevname[i] < current->name[i])
		{
			i = 0;
			while (tmp->name[i] == current->name[i] && tmp->name[i])
				i++;
			if (tmp->name[i] > current->name[i])
				tmp = current;
		}
		current = current->next;
	    }
		if (tmp->visible == 1 && tmp->content)
		{
	   	 	ft_putstr_fd(current->name, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(tmp->content, 1);
			ft_putchar_fd('\n', 1);
		}
 	       current = current->next;
 	   }
    }
}

