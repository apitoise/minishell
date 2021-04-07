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
			printf("minishell: syntax error near unexpected token `%c'\n", st->cmd[i][0]);
			return (1);
		}
		else if (st->cmd[i][0] == '>' && ft_strlen(st->cmd[i]) > 2)
		{
			printf("minishell: syntax error near unexpected token `>'\n");
			return (1);
		}
		else if ((st->cmd[i][0] == '>' || st->cmd[i][0] == '<')
		&& (st->cmd[i + 1][0] == '>' || st->cmd[i][0] == '<'
		|| st->cmd[i][0] == '|'))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", st->cmd[i + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}