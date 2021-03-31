/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:49:26 by cnotin            #+#    #+#             */
/*   Updated: 2019/12/06 12:16:42 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *begin;
	t_list *current;

	if (lst)
	{
		if (!(begin = ft_lstnew(f(lst->content))))
			return (NULL);
		lst = lst->next;
		while (lst)
		{
			if (!(current = ft_lstnew(f(lst->content))))
			{
				ft_lstclear(&begin, del);
				return (NULL);
			}
			ft_lstadd_back(&begin, current);
			lst = lst->next;
		}
		return (begin);
	}
	return (NULL);
}
