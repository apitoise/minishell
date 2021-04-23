/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:28:25 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/23 13:28:28 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void new_line(char *cmd, t_history **history)
{
    t_history   *current;
    t_history   *new;

    new = malloc(sizeof(t_history));
    new->cmd = cmd;
    new->next = NULL;
    if (*history == NULL)
        *history = new;
    else
    {
        current = *history;
        while (current->next)
            current = current->next;
        current->next = new;
    }
}

static int  is_same_command(char *cmd, t_history **history)
{
    t_history   *current;

    if (*history == NULL)
        return (0);
    current = *history;
    while(current->next)
        current = current->next;
    if (!ft_strcmp(current->cmd, cmd))
        return (1);
    else
        return (0);
}

void        get_history(char *cmd, t_history **history)
{
    if (!is_same_command(cmd, history))
        new_line(cmd, history);
    return ;
}