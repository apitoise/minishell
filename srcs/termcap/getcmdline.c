/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmdline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:20:53 by lgimenez          #+#    #+#             */
/*   Updated: 2021/05/20 16:06:48 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"
#include <curses.h>
#include <term.h>

void		ft_freehs(t_history *new)
{
	if (new)
	{
		if (new->cmdline)
			free(new->cmdline);
		free(new);
		new = NULL;
	}
}

static int	getposition_atoi(char *buff, int i, t_struct *st)
{
	int	pow;

	st->posx = 0;
	st->posy = 0;
	--i;
	pow = 1;
	while (buff[i] != ';')
	{
		st->posx = st->posx + (buff[i] - '0') * pow;
		pow *= 10;
		--i;
		if (i < 0)
			return (1);
	}
	--i;
	pow = 1;
	while (buff[i] != '[')
	{
		st->posy = st->posy + (buff[i] - '0') * pow;
		pow *= 10;
		--i;
		if (i < 0)
			return (1);
	}
	return (0);
}

static int	ft_getposition(t_struct *st)
{
	char	buff[30];
	char	c;
	int		i;

	if (write(1, "\033[6n", 4) == -1)
		return (1);
	i = -1;
	c = 0;
	while (c != 'R')
	{
		if (read(0, &c, 1) < 1)
			return (1);
		buff[++i] = c;
	}
	if (i < 2)
		return (1);
	if (getposition_atoi(buff, i, st))
		return (1);
	return (0);
}

static int	ft_nextline(t_history *new, t_struct *st)
{
	size_t	len;

	if (ft_getposition(st))
		return (1);
	len = 0;
	if (new)
		len = new->len;
	if ((st->startposx - 1 + len) % (unsigned int)st->ttywidth == 0)
	{
		if (st->posy == st->ttyheight)
		{
			tputs(tgoto(tgetstr("cm", NULL), 0, st->posy - 1), 1, &ft_putc);
			tputs(tgetstr("sf", NULL), st->ttyheight, &ft_putc);
		}
		else
			tputs(tgoto(tgetstr("cm", NULL), 0, st->posy), 1, &ft_putc);
	}
	return (0);
}

int			ft_tputsstr(char *str, t_history *new, t_struct *st)
{
	tputs(str, 1, &ft_putc);
	if (ft_nextline(new, st))
		return (1);
	return (0);
}

static void	delcmdline(t_history *new, t_struct *st)
{
	int	startposx;
	int	nbrlines;
	int	i;

	startposx = st->startposx - 1;
	nbrlines = (startposx + new->len) / st->ttywidth;
	if (new->cmdline)
	{
		free(new->cmdline);
		new->cmdline = NULL;
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, st->posy - 1), 1, &ft_putc);
	i = 1;
	while (nbrlines-- && ++i)
	{
		tputs(tgetstr("ce", NULL), 1, &ft_putc);
		tputs(tgoto(tgetstr("cm", NULL), 0, st->posy - i), 1, &ft_putc);
	}
	while (startposx--)
		tputs(tgetstr("nd", NULL), 1, &ft_putc);
	tputs(tgetstr("ce", NULL), 1, &ft_putc);
}

static int	replaceline(t_history *new, t_struct *st)
{
	if (ft_getposition(st))
		return (1);
	delcmdline(new, st);
	if (!st->hsindex)
		ft_bzero(new, sizeof(t_history));
	else if (st->hsindex > 0)
	{
		if (!(new->cmdline =
					ft_strdup(st->hstab[st->hslen - st->hsindex]->cmdline)))
			return (1);
		new->len = st->hstab[st->hslen - st->hsindex]->len;
		new->capacity = st->hstab[st->hslen - st->hsindex]->capacity;
		if (ft_tputsstr(new->cmdline, new, st))
			return (1);
	}
	return (0);
}

static int	browsehistory(char c, t_history *new, t_struct *st)
{
	if (c == 'A' && st->hsindex < st->hslen)
		st->hsindex++;
	else if (c == 'B' && st->hsindex > 0)
		st->hsindex--;
	else
		return (0);
	return (replaceline(new, st));
}

static void	ft_hstabcpy(t_history **tmp, t_struct *st)
{
	size_t	i;

	i = 0;
	while (i < st->hslen)
	{
		tmp[i] = st->hstab[i];
		++i;
	}
}

static int	ediths(t_history **new, t_struct *st)
{
	t_history	**tmp;

	if (!st->hstab)
	{
		if (!(st->hstab = malloc(sizeof(t_history*))))
			return (1);
		st->hstab[0] = *new;
		st->hslen = 1;
		st->hscapacity = 1;
	}
	else if (ft_strcmp(st->hstab[st->hslen - 1]->cmdline, (*new)->cmdline))
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
		st->hstab[st->hslen] = *new;
		st->hslen++;
	}
	else
	{
		ft_freehs(*new);
		*new = st->hstab[st->hslen - 1];
	}
	return (0);
}

static int	isempty(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
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
		if (ft_getposition(st))
			return (1);
		if (st->posx == 1 && st->posy != 1)
		{
			tputs(tgoto(tgetstr("cm", NULL), st->ttywidth, st->posy - 2),
				1, &ft_putc);
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

static int	vector(t_history *new, char *buff)
{
	char	*tmp;

	if (new->cmdline == NULL)
	{
		if (!(new->cmdline = malloc(sizeof(char) + 1)))
			return (1);
		new->capacity = 1;
		ft_strcpy(new->cmdline, buff);
		new->len = 1;
	}
	else
	{
		if (new->len + 1 > new->capacity)
		{
			if (!(tmp = malloc(sizeof(char) * (new->capacity * 2 + 1))))
				return (1);
			ft_strcpy(tmp, new->cmdline);
			free(new->cmdline);
			new->cmdline = tmp;
			new->capacity *= 2;
		}
		ft_strcat(new->cmdline, buff);
		new->len++;
	}
	return (0);
}

int			winszdiff(t_history *new, t_struct *st)
{
	int	oldwidth;
	int	oldheight;

	oldwidth = st->ttywidth;
	oldheight = st->ttyheight;
	if (ft_getwinsz(st))
		return (-1);
	if (oldwidth != st->ttywidth || oldheight != st->ttyheight)
	{
		tputs(tgetstr("cl", NULL), st->ttyheight, &ft_putc);
		if (ft_tputsstr("@minishell> ", NULL, st))
			return (-1);
		if (new->cmdline && ft_tputsstr(new->cmdline, new, st))
				return (-1);
		return (1);
	}
	return (0);
}

char		*closetermcap(t_history *new, struct termios *restore, t_struct *st)
{
	if (new)
	{
		if (new->cmdline)
			free(new->cmdline);
		free(new);
	}
	tputs(tgetstr("cl", NULL), st->ttyheight, &ft_putc);
	tcsetattr(STDIN_FILENO, TCSANOW, restore);
	ft_putstr_fd("Malfunction with termcap\n", 2);
	return (NULL);
}

static int	editcmdline(char *buff, t_history *new, t_struct *st)
{
	if (buff[0] == 127)
	{
		if (delone(new, st))
			return (1);
	}
	else if ((buff[0] != '\n' && vector(new, buff))
			|| (ft_tputsstr(buff, new, st)))
		return (1);
	return (0);
}

static void	ctrld(t_history *new, struct termios *restore, t_struct *st)
{
	if (!new->cmdline || new->cmdline[0] == '\0')
	{
		ft_freehs(new);
		tcsetattr(STDIN_FILENO, TCSANOW, restore);
		ft_putstr_fd("exit\n", 1);
		ft_exit(NULL, st);
	}
}

static int	readloop(t_history *new, struct termios *restore, t_struct *st)
{
	char	buff[11];
	int		ret;

	ft_bzero(buff, 11);
	while (buff[0] != '\n')
	{
		if ((winszdiff(new, st) == -1)
			|| ((ret = read(STDIN_FILENO, buff, 10)) == -1))
			return (1);
		buff[ret] = '\0';
		if (buff[0] == 4)
			ctrld(new, restore, st);
		else if (buff[0] == 27 && buff[1] == '[')
		{
			if (browsehistory(buff[2], new, st))
				return (1);
		}
		else if (ret == 1 && editcmdline(buff, new, st))
			return (1);
	}
	return (0);
}

char		*getcmdline(t_struct *st)
{
	struct termios	restore;
	struct termios	term;
	t_history		*new;
	int				ret;

	if (ft_getwinsz(st))
		return (NULL);
	tcgetattr(STDIN_FILENO, &restore);
	term = restore;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	new = NULL;
	if (!(new = malloc(sizeof(t_history))))
		return (closetermcap(NULL, &restore, st));
	ft_bzero(new, sizeof(t_history));
	st->hsindex = 0;
	if (ft_getposition(st))
		return (closetermcap(new, &restore, st));
	st->startposx = st->posx;
	if (readloop(new, &restore, st) || (ret = winszdiff(new, st)) == -1)
		return (closetermcap(new, &restore, st));
	else if (ret == 1)
		ft_putchar_fd('\n', 1);
	if (new->cmdline && isempty(new->cmdline))
		new->cmdline[0] = '\0';
	if (new->cmdline && new->cmdline[0] && ediths(&new, st))
		return (closetermcap(new, &restore, st));
	tcsetattr(STDIN_FILENO, TCSANOW, &restore);
	if (!new->cmdline || !new->cmdline[0])
	{
		ft_freehs(new);
		return (NULL);
	}
	return (ft_strdup(new->cmdline));
}
