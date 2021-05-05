/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmdline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:20:53 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/05 13:12:05 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"
#include <curses.h>
#include <term.h>

static int	getposition(int	*x, int *y)
{
	char	buff[30];
	char	c;
	int		i;
	int		pow;

	write(1, "\033[6n", 4);
	i = -1;
	c = 0;
	while (c != 'R')
	{
		if (!read(0, &c, 1))
			return (1);
		buff[++i] = c;
	}
	if (i < 2)
		return (1);
	*x = 0;
	*y = 0;
	--i;
	pow = 1;
	while (buff[i] != ';')
	{
		*x = *x + (buff[i] - '0') * pow;
		--i;
		pow *= 10;
	}
	--i;
	pow = 1;
	while (buff[i] != '[')
	{
		*y = *y + (buff[i] - '0') * pow;
		--i;
		pow *= 10;
	}
	return (0);
}

static int	delone(char *cmdline)
{
	int	i;
	int	x;
	int	y;

	if (cmdline && cmdline[0])
	{
		i = -1;
		while (cmdline[++i])
			;
		cmdline[--i] = '\0';
		if (getposition(&x, &y))
			return (1);
		if (x == 1 && y != 1)
		{
			tputs(tgoto(tgetstr("cm", NULL), tgetnum("co"), y - 2), 1, &ft_putc);
			tputs(tgetstr("dc", NULL), 1, &ft_putc);
		}
		else
		{
			tputs(tgetstr("le", NULL), 1, &ft_putc);
			tputs(tgetstr("dc", NULL), 1, &ft_putc);
		}
	}
	return (0);
}

static void	addchar(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	str[i] = c;
	str[++i] = '\0';
}

static int	vector(char **cmdline, char *buff, t_struct *st)
{
	char	*tmp;

	if (*cmdline == NULL)
	{
		if (!(*cmdline = malloc(sizeof(char) + 1)))
			return (1);
		st->capacmdline = 1;
		(*cmdline)[0] = buff[0];
		(*cmdline)[1] = '\0';
	}
	else if (ft_strlen(*cmdline) + 1 > st->capacmdline)
	{
		if (!(tmp = malloc(sizeof(char) * (st->capacmdline * 2 + 1))))
			return (ft_freestr(*cmdline));
		st->capacmdline = st->capacmdline * 2;
		ft_strcpy(tmp, *cmdline);
		addchar(tmp, buff[0]);
		free(*cmdline);
		*cmdline = tmp;
	}
	else
		addchar(*cmdline, buff[0]);
	return (0);
}

char		*getcmdline(t_struct *st)
{
	struct termios	restore;
	struct termios	term;
	char			*cmdline;
	char			buff[11];
	int				ret;

	tcgetattr(STDIN_FILENO, &restore);
	term = restore;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	cmdline = NULL;
	while (buff[0] != '\n')
	{
		ret = read(STDIN_FILENO, buff, 10);
		buff[ret] = '\0';
		if (buff[0] == 4)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &restore);
			ft_exit(NULL);
		}
		if (buff[0] == 27 && buff[1] == '[')
			;
		else if (buff[0] == 127)
			delone(cmdline);
		else
		{
			tputs(buff, 1, &ft_putc);
			if (buff[0] != '\n')
				vector(&cmdline, buff, st);
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &restore);
	return (cmdline);
}
