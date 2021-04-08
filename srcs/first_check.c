#include "../headers/minishell.h"
#include "../libft/libft.h"

int		first_check(t_struct *st)
{
	int	i;

	i = 0;
	while(st->cmd[i])
	{
		if ((st->cmd[i][0] == '<' || st->cmd[i][0] == '|')
		&& (ft_strlen(st->cmd[i]) > 1))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(st->cmd[i], 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		else if ((!ft_strcmp(st->cmd[i], ">") || !ft_strcmp(st->cmd[i], ">>")
		|| !ft_strcmp(st->cmd[i], "<") || !ft_strcmp(st->cmd[i], "|"))
		&& !st->cmd[i + 1])
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
		else if (st->cmd[i][0] == '>' && ft_strlen(st->cmd[i]) > 2)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
			return (1);
		}
		else if ((st->cmd[i][0] == '>' || st->cmd[i][0] == '<')
		&& (st->cmd[i + 1][0] == '>' || st->cmd[i][0] == '<'
		|| st->cmd[i][0] == '|'))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(st->cmd[i], 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}