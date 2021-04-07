/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:22:41 by cnotin            #+#    #+#             */
/*   Updated: 2020/08/26 19:31:00 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"

static void	cmd_analysis(char **commands, t_struct *st)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		st->cmd = ft_split_cmd(commands[i], ' ');
		if (first_check(st))
			return ;
		do_chevrons(st);						
		do_builtin(st);
		i++;
	}
}

int			main(int ac, char **av, char **env)
{
	t_struct	st;
	int			ret;
	char		*tmp;
	char		**commands;

	(void)ac;
	(void)av;
	tmp = NULL;
	commands = NULL;
	init_struct(&st, env);
	shell_init();
	while (!(st.exit))
	{
		while ((ret = get_next_line(1, &tmp)) > 0 && !(st.exit))
		{
			commands = ft_split(tmp, ';');
			cmd_analysis(commands, &st);
			if (st.result)
			{
				if (st.ret != 127)
					ft_putstr_fd(st.result, st.fd);
				free(st.result);
				st.result = NULL;
			}
			shell_init();
		}
	}
	ft_free_tab(st.env);
	return (0);
}
