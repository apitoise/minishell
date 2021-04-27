/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:53:02 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/27 13:53:03 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void get_cursor_line(t_struct *st)
{
    char    buff[51];
    int     i;

    if ((i = read(STDOUT_FILENO, buff, 50) <= 0))
        return ;
    buff[i] = 0;
    while (buff[i] && buff[i != '['])
        i++;
    while (buff[i] && !ft_isdigit(buff[i]))
        i++;
    st->current_line = ft_atoi(&buff[i]);
}

static void is_doublon(t_struct *st)
{
    if (st->hstline < 2)
        return ;
    if (!ft_strcmp(st->hst[st->hstline - 1], st->hst[st->hstline - 2]))
    {
        if (st->hst[st->hstline - 1])
        {
            st->hst[st->hstline - 1][0] = 0;
            free(st->hst[st->hstline - 1]);
        }
        st->hstline--;
    }
}

static char *get_new_line(t_struct *st, char *cmd)
{
    if (cmd)
        free(cmd);
    cmd = ft_strdup(st->hst[st->nav]);
    if (!st->hst[st->nav][0])
    {
        if (st->hst[st->hstline - 1])
            free (st->hst[st->hstline - 1]);
        st->hstline--;
        return (cmd);
    }
    else if (st->nav == st->hstline - 1)
    {
        is_doublon(st);
        return (cmd);
    }
    else
    {
        if (st->hst[st->hstline - 1])
            free(st->hst[st->hstline - 1]);
        st->hst[st->hstline - 1] = ft_strdup(st->hst[st->nav]);
        is_doublon(st);

    }
    return (cmd);
}

static char *get_command(t_struct *st)
{
    int     i;
    int     j;
    char    *cmd;

    if (!(cmd = (char *)malloc(sizeof(char)
    * (ft_strlen(st->hst[st->nav]) + ft_strlen(st->buff) + 1))))
        return (NULL);
    i = 0;
    while (st->hst[st->nav][i])
    {
        cmd[i] = st->hst[st->nav][i];
        i++;
    }
    j = 0;
    while (st->buff[j])
    {
        cmd[i] = st->buff[j];
        i++;
        j++;
    }
    cmd[i] = '\0';
    return (cmd);
}

static void is_line(t_struct *st)
{
    int new_line;

    new_line = (ft_strlen(st->hst[st->nav]) + ft_strlen("@minishell>")
    / st->term.column_term);
    if (new_line > st->term.line_term - st->current_line)
    {
        tputs(tgoto(st->term.cm, 0, 0), 1, ft_putchar);
        shell_init();
        tputs(st->term.sc, 1, ft_putchar);
        st->current_line = 0;
    }
}

static void ft_print_screen(t_struct *st)
{
    tputs(st->term.rc, 1, ft_putchar);
    is_line(st);
    tputs(st->term.cd, 1, ft_putchar);
    ft_putstr_fd(st->hst[st->nav], 1);
}

char        *get_input(t_struct *st)
{
    int     ret;
    char    *cmd;

    st->nav = st->hstline;
    st->hstline++;
    st->hst[st->nav] = malloc(sizeof(char));
    st->hst[st->nav][0] = '\0';
    tputs(st->term.sc, 1, ft_putchar);
    get_cursor_line(st);
    cmd = NULL;
    while ((ret = read(0, st->buff, 4)))
    {
        st->buff[ret] = '\0';
        if (st->buff[0] == 4)
            ft_exit(st->cmd);
        if (st->buff[0] == '\n')
        {
            cmd = get_new_line(st, cmd);
            ft_putchar_fd('\n', 1);
            return (cmd);
        }
        else if (st->buff[0] == 127 && ft_strlen(st->hst[st->nav]) > 0)
            st->hst[st->nav][ft_strlen(st->hst[st->nav]) - 1] = 0;
        // else if (st->buff[0] == 27 && st->buff[1] == '[')
        //     up_and_down(st);
        else
            cmd = get_command(st);
        ft_print_screen(st);
    }
    return (cmd);
}