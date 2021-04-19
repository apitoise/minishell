/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_chevron.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:11:09 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/19 15:11:11 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int  get_len(char **cmd)
{
    int len;
    int i;

    len = 0;
    i = 0;
    while(cmd[i])
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

static char     **get_res(char **cmd, int len)
{
    int     i;
    int     j;
    char    **res;

    if (!(res = (char **)malloc(sizeof(char *) * (len + 1))))
        return (NULL);
    i = 0;
    j = 0;
    while(cmd[i])
    {
        if (!ft_strcmp(cmd[i], ">")
        || !ft_strcmp(cmd[i], ">>")
        || !ft_strcmp(cmd[i], "<"))
        {
            if (!cmd[i + 2])
                return (res);
            else
                i += 2;
        }
        else
        {
            res[j] = ft_strdup(cmd[i]);
            i++;
            j++;
        }
    }
    res[j] = NULL;
    return (res);
}

char    **del_chevron(char **cmd)
{
    int     len;
    char    **res;

    len = get_len(cmd);
    if (len == 0)
    {
        if (!(res = (char **)malloc(sizeof(char *) * 1)))
            return (NULL);
        res[0] = ft_strdup("");
        return (res);
    }
    else
        res = get_res(cmd, len);
    ft_free_tab(cmd);
    return (res);
}
