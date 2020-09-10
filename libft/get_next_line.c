/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:07:18 by cnotin            #+#    #+#             */
/*   Updated: 2020/06/18 17:21:39 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

static int	get_return(char **line)
{
	if ((**line))
		return (1);
	else
	{
		ft_strdel(line);
		return (0);
	}
}

int			get_next_line(int fd, char **line)
{
	static char	fdstock[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*tmp;
	int			ret;

	tmp = fdstock[fd];
	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (-1);
	if (!((*line) = ft_strnew(0)))
		return (-1);
	while (1)
	{
		if (ft_strchr(tmp, '\n'))
		{
			(*line) = ft_strnjoinf((*line), tmp, 1,
				(ft_strchr(tmp, '\n') - tmp));
			ft_strncpy(tmp, &tmp[ft_strchr(tmp, '\n') - tmp + 1],
				BUFFER_SIZE - (ft_strchr(tmp, '\n') - tmp));
			return (1);
		}
		(*line) = ft_strnjoinf((*line), tmp, 1, BUFFER_SIZE);
		ret = read(fd, fdstock[fd], BUFFER_SIZE);
		tmp[ret] = '\0';
		if (ret == 0)
			return (get_return(line) == 1 ? 1 : 0);
	}
}
