/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:28:25 by apitoise          #+#    #+#             */
/*   Updated: 2021/04/23 13:28:28 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void raw_mode(t_term *term)
{
    struct termios  termios;

    tcgetattr(STDIN_FILENO, &term->terms);
    termios = term->terms;
    termios.c_lflag &= ~(ECHO | ICANON);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios) == -1)
        return ;
}

void        init_termcap(t_term *term)
{
    int     i;
    char    *term_type;

    if ((term_type = getenv("TERM")) == NULL)
        return ;
    i = tgetent(NULL, term_type);
    if (i == -1 || i == 0)
        return ;
    term->column_term = tgetnum("co");
    term->line_term = tgetnum("li");
    term->me = tgetstr("me", NULL);
    term->cm = tgetstr("cm", NULL);
    term->sc = tgetstr("sc", NULL);
    term->sf = tgetstr("sf", NULL);
    term->rc = tgetstr("rc", NULL);
    term->cd = tgetstr("cd", NULL);
    term->cl = tgetstr("cl", NULL);
    term->up = tgetstr("up", NULL);
    term->dw = tgetstr("dw", NULL);
    raw_mode(term);
}