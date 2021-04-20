#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void cmd_analysis(char **commands, t_struct *st)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		st->cmd = ft_split_cmd(commands[i], ' ', st);
		if (first_check(st->cmd))
			return ;
		do_routine(st);
		i++;
	}
}

void        minishell(t_struct *st)
{
    char    **commands;
    char    *tmp;
    int     ret;

    commands = NULL;
    tmp = NULL;
    shell_init();
	while (!(st->exit))
	{
		while ((ret = get_next_line(1, &tmp)) > 0 && !(st->exit))
		{
			if (!ft_parsecmdline(&tmp, st))
			{
				commands = ft_split_cmdline(tmp, ';');
				cmd_analysis(commands, st);
			}
			shell_init();
		}
	}
    ft_free_tab(st->env);
}
