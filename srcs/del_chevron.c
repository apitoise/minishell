#include "../headers/minishell.h"
#include "../libft/libft.h"

static int  get_len(t_struct *st)
{
    int len;
    int i;

    len = 0;
    i = 0;
    while(st->cmd[i])
    {
        if (!ft_strcmp(st->cmd[i], ">")
        || !ft_strcmp(st->cmd[i], ">>")
        || !ft_strcmp(st->cmd[i], "<"))
        {
            if (!st->cmd[i + 2])
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

static char     **get_res(t_struct *st, int len)
{
    int     i;
    int     j;
    char    **res;

    if (!(res = (char **)malloc(sizeof(char *) * (len + 1))))
        return (NULL);
    i = 0;
    j = 0;
    while(st->cmd[i])
    {
        if (!ft_strcmp(st->cmd[i], ">")
        || !ft_strcmp(st->cmd[i], ">>")
        || !ft_strcmp(st->cmd[i], "<"))
        {
            if (!st->cmd[i + 2])
                return (res);
            else
                i += 2;
        }
        else
        {
            res[j] = ft_strdup(st->cmd[i]);
            i++;
            j++;
        }
    }
    res[j] = NULL;
    return (res);
}

char    **del_chevron(t_struct *st)
{
    int     len;
    char    **res;

    len = get_len(st);
    if (len == 0)
    {
        if (!(res = (char **)malloc(sizeof(char *) * 1)))
            return (NULL);
        res[0] = ft_strdup("");
        return (res);
    }
    else
        res = get_res(st, len);
    ft_free_tab(st->cmd);
    return (res);
}