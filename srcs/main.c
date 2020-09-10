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

int		isok(t_struct *st, char *str)
{
	int		i;
	int		len;

	len = ft_strlen(str);
	i = ft_strlen(st->s) - 1;
	if (i == len)
		return (0);
	if (i > len && (st->s[len + 1] != '\n' || st->s[len + 1] != ' ' || st->s[len + 1] != '\0'))
		return (1);
	else
		return (0);
}

/*
int		ft_dispatcher(t_struct *st)
{
	static char commande[7][7] = {{"cd"}, {"echo"}, {"pwd"}, {"export"}, {"unset"}, {"env"}, {"exit"}};
	static int (*fct[7])(t_struct *st) = {ft_cd, ft_echo, ft_pwd, ft_export, ft_unset, ft_env, ft_exit}; // fonction a cree par la suite
	int i;

	i = 0;
	while (i < 7)
	{
		if (!(ft_strcmp(st->s, commande[i])))
		{
			if (!(isok(st, commande[i])))
				return ((fct[i])(st));
			else
				return (ft_error(st->s));
		}
		else
			i++;
	}
	return (ft_error(st->s));
}*/

void	if_builtin(t_struct *st)
{
	if (!ft_strcmp(st->cmd[0], "pwd"))
		ft_pwd(st->cmd);
	else if (!ft_strcmp(st->cmd[0], "echo"))
		ft_echo(st->cmd);
	else if (!ft_strcmp(st->cmd[0], "exit"))
		ft_exit(st->cmd);
	else if (!ft_strcmp(st->cmd[0], "env"))
		ft_env(st->env);
	else if (!ft_strcmp(st->cmd[0], "unset"))
		ft_unset(st);
	else if (!ft_strcmp(st->cmd[0], "cd"))
		ft_cd(st->cmd[1]);
	else if (ft_strchr(st->cmd[0], '='))
		ft_export(st->cmd, &st->lst, 1);
	else if (!ft_strcmp(st->cmd[0], "export"))
		ft_export(st->cmd, &st->lst, 2);
	else
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(st->cmd[0], 1);
		ft_putstr_fd(" command not found\n", 1);
	}
}

void print_tab(char **map)
{
    int i;

    i = 0;
    if (!map)
        return ;
    while (map && map[i])
    {
        ft_putendl_fd(map[i++], 1);
    }
}


int		main(int ac, char **av, char **env)
{
	t_struct	st;
	int			ret;
	char		*tmp;

	(void)ac;
	(void)av;
	tmp = NULL;
	init_struct(&st, env);
	shell_init();
	while (!(st.exit))
	{
		while ((ret = get_next_line(1, &tmp)) > 0 && !(st.exit))
		{
			st.cmd = ft_split(tmp, ' ');
			if_builtin(&st);
			//if (st.cmd[0] == NULL)
			//	ft_error("");
			//print_map(st.cmd);
			//ft_dispatcher(&st);
			//free(st.s);
			shell_init();
		}
	}
	ft_free_tab(st.env);
	return (0);
}


