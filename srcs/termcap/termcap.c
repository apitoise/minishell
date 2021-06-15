/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:20:53 by lgimenez          #+#    #+#             */
/*   Updated: 2021/06/15 15:38:23 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static char	*closetermcap(t_history *new, struct termios *restore, t_struct *st)
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

static void	ctrld(t_history *new, struct termios *restore, t_struct *st)
{
	if (!new->cmdline || new->cmdline[0] == '\0')
	{
		ft_freehs(new);
		tcsetattr(STDIN_FILENO, TCSANOW, restore);
		ft_exit(NULL, 0, st);
	}
}

static int	readloop(t_history *new, struct termios *restore, t_struct *st)
{
	char	buff[11];
	int		ret;

	ft_bzero(buff, 11);
	while (buff[0] != '\n')
	{
		if (ft_winszdiff(new, st) == -1)
			return (1);
		ret = read(STDIN_FILENO, buff, 10);
		if (ret == -1)
			return (1);
		buff[ret] = '\0';
		if (!ft_strcmp(buff, "\t"))
			buff[0] = ' ';
		if (buff[0] == 4)
			ctrld(new, restore, st);
		else if (buff[0] == 27 && buff[1] == '[')
		{
			if (tc_browsehs(buff[2], new, st))
				return (1);
		}
		else if (ret == 1 && tc_editcmdl(buff, new, st))
			return (1);
	}
	return (0);
}

static int	getcmdline(t_history **new, struct termios *restore, t_struct *st)
{
	int	ret;

	st->hsindex = 0;
	if (ft_getposition(st))
		return (1);
	st->startposx = st->posx;
	if (readloop(*new, restore, st))
		return (1);
	ret = ft_winszdiff(*new, st);
	if (ret == -1)
		return (1);
	else if (ret == 1)
		ft_putchar_fd('\n', 1);
	if ((*new)->cmdline && ft_isblank((*new)->cmdline))
		(*new)->cmdline[0] = '\0';
	if ((*new)->cmdline && (*new)->cmdline[0] && tc_ediths(new, st))
		return (1);
	return (0);
}

char	*ft_termcap(t_struct *st)
{
	struct termios	restore;
	struct termios	term;
	t_history		*new;

	if (ft_getwinsz(st))
		return (NULL);
	tcgetattr(STDIN_FILENO, &restore);
	term = restore;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	new = malloc(sizeof(t_history));
	ft_bzero(new, sizeof(t_history));
	g_sig.cmdl = &new;
	if (getcmdline(&new, &restore, st))
		return (closetermcap(new, &restore, st));
	if (!new->cmdline || !new->cmdline[0])
	{
		ft_freehs(new);
		return (NULL);
	}
	g_sig.cmdl = NULL;
	tcsetattr(STDIN_FILENO, TCSANOW, &restore);
	return (ft_strdup(new->cmdline));
}
