/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmdline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:20:53 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/07 15:44:31 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"
#include <curses.h>
#include <term.h>

static int	getposition(t_struct *st)
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
	st->posx = 0;
	st->posy = 0;
	--i;
	pow = 1;
	while (buff[i] != ';')
	{
		st->posx = st->posx + (buff[i] - '0') * pow;
		--i;
		pow *= 10;
	}
	--i;
	pow = 1;
	while (buff[i] != '[')
	{
		st->posy = st->posy + (buff[i] - '0') * pow;
		--i;
		pow *= 10;
	}
	return (0);
}

static void	nextline(t_history *new, t_struct *st)
{
	size_t	len;

	getposition(st);
	len = 0;
	if (new)
		len = new->len;
	if ((len + 12) % (unsigned int)st->ttywidth == 0)
	{
		if (st->posy == st->ttyheight)
		{
			tputs(tgoto(tgetstr("cm", NULL), 0, st->posy - 1), 1, &ft_putc);
			tputs(tgetstr("sf", NULL), st->ttyheight, &ft_putc);
		}
		else
			tputs(tgoto(tgetstr("cm", NULL), 0, st->posy), 1, &ft_putc);
	}
}

static void	replaceline(t_history *new, t_struct *st)
{
	int	nbrlines;
	int	i;

	getposition(st);
	nbrlines = (new->len + 12) / st->ttywidth;
	free(new->cmdline);
	tputs(tgoto(tgetstr("cm", NULL), 0, st->posy - 1), 1, &ft_putc);
	i = 2;
	while (nbrlines--)
	{
		tputs(tgetstr("ce", NULL), 1, &ft_putc);
		tputs(tgoto(tgetstr("cm", NULL), 0, st->posy - i), 1, &ft_putc);
		++i;
	}
	tputs(tgetstr("ce", NULL), 1, &ft_putc);
	shell_init();
	nextline(NULL, st);
	new->cmdline = ft_strdup(st->hstab[st->hslen - st->hsindex]->cmdline);
	new->len = st->hstab[st->hslen - st->hsindex]->len;
	new->reallen = st->hstab[st->hslen - st->hsindex]->reallen;
	new->capacity = st->hstab[st->hslen - st->hsindex]->capacity;
	tputs(new->cmdline, 1, &ft_putc);
	nextline(new, st);
}

static int	browsehistory(char c, t_history *new, t_struct *st)
{
	if (c == 'A' && st->hsindex < st->hslen)
	{
		st->hsindex++;
		replaceline(new, st);
	}
	else if (c == 'B' && st->hsindex > 1)
	{
		st->hsindex--;
		replaceline(new, st);
	}
	return (0);	
}

static void	ft_hstabcpy(t_history **tmp, t_struct *st)
{
	size_t	i;

	i = 0;
	while(i < st->hslen)
	{
		tmp[i] = st->hstab[i];
		++i;
	}
}

static int	ediths(t_history *new, t_struct *st)
{
	t_history	**tmp;

	if (!st->hstab)
	{
		if (!(st->hstab = malloc(sizeof(t_history*))))
			return (1);
		st->hstab[0] = new;
		st->hslen = 1;
		st->hscapacity = 1;
	}
	else if (ft_strcmp(st->hstab[st->hslen - 1]->cmdline, new->cmdline))
	{
		if (st->hslen + 1 > st->hscapacity)
		{
			if (!(tmp = malloc(sizeof(t_history*) * (st->hscapacity * 2))))
				return (1);
			ft_hstabcpy(tmp, st);
			free(st->hstab);
			st->hstab = tmp;
			st->hscapacity *= 2;
		}
		st->hstab[st->hslen] = new;
		st->hslen++;
	}
	return (0);
}

static int	delone(t_history *new, t_struct *st)
{
	int	i;

	if (new->cmdline && new->cmdline[0])
	{
		i = -1;
		while (new->cmdline[++i])
			;
		new->cmdline[--i] = '\0';
		new->len--;
		if (getposition(st))
			return (1);
		if (st->posx == 1 && st->posy != 1)
		{
			tputs(tgoto(tgetstr("cm", NULL), st->ttywidth, st->posy - 2), 1, &ft_putc);
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

static int	vector(t_history *new, char *buff, int bufflen)
{
	char	*tmp;

	if (new->cmdline == NULL)
	{
		if (!(new->cmdline = malloc(sizeof(char) * 10 + 1)))
			return (1);
		new->capacity = 10;
		ft_strcpy(new->cmdline, buff);
		new->len = 1;
		new->reallen = bufflen;
	}
	else
	{
		if (new->reallen + bufflen > new->capacity)
		{
			if (!(tmp = malloc(sizeof(char) * (new->capacity * 2 + 1))))
				return (ft_freestr(new->cmdline));
			ft_strcpy(tmp, new->cmdline);
			free(new->cmdline);
			new->cmdline = tmp;
			new->capacity *= 2;
		}
		ft_strcat(new->cmdline, buff);
		new->len++;
		new->reallen += bufflen;
	}
	return (0);
}

int			winszdiff(t_history *new, struct termios *restore, t_struct *st)
{
	int	oldwidth;
	int	oldheight;

	oldwidth = st->ttywidth;
	oldheight = st->ttyheight;
	if (ft_getwinsz(st))
	{
		if (new->cmdline)
			free(new->cmdline);
		free(new);
		tcsetattr(STDIN_FILENO, TCSANOW, restore);
		ft_exit(NULL);
	}
	if (oldwidth != st->ttywidth || oldheight != st->ttyheight)
	{
		tputs(tgetstr("cl", NULL), st->ttyheight, &ft_putc);
		shell_init();
		nextline(NULL, st);
		if (new->cmdline)
		{
			tputs(new->cmdline, 1, &ft_putc);
			nextline(new, st);
		}
		return (1);
	}
	return (0);
}

char		*getcmdline(t_struct *st)
{
	struct termios	restore;
	struct termios	term;
	t_history		*new;
	char			buff[11];
	int				ret;

	tcgetattr(STDIN_FILENO, &restore);
	term = restore;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	if (!(new = malloc(sizeof(t_history))))
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &restore);
		return (NULL);
	}
	new->cmdline = NULL;
	new->len = 0;
	new->reallen = 0;
	new->capacity = 0;
	st->hsindex = 0;
	while (buff[0] != '\n')
	{
		winszdiff(new, &restore, st);
		ret = read(STDIN_FILENO, buff, 10);
		buff[ret] = '\0';
		if (buff[0] == 4)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &restore);
			ft_exit(NULL);
		}
		if (buff[0] == 27 && buff[1] == '[')
		{
			browsehistory(buff[2], new, st);
		}
		else if (buff[0] == 127)
			delone(new, st);
		else
		{
			if (buff[0] != '\n')
				vector(new, buff, ret);
			tputs(buff, 1, &ft_putc);
			nextline(new, st);
		}
	}
	if (winszdiff(new, &restore, st))
		ft_putchar_fd('\n', 1);
	if (new->cmdline)
		ediths(new, st);
	tcsetattr(STDIN_FILENO, TCSANOW, &restore);
	return (ft_strdup(new->cmdline));
}
