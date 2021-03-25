#include "../headers/minishell.h"
#include "../libft/libft.h"

static int	check_str(char **cmd, int i, int j, char c)
{
	while(cmd[i])
	{
		while (cmd[i][j])
		{
			if (cmd[i][j] == c)
				return (1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

void		check_cmd(char **cmd, int i)
{
	int	j;
	int	ok;

	ok = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j] && !ok)
		{
			if (cmd[i][j] == '\'' || cmd[i][j] == '\"')
			{
				ok = check_str(cmd, i, j + 1, cmd[i][j]);
				printf("%d\n", ok);
			}
			j++;
		}
		i++;
	}
}