#include "../headers/minishell.h"
#include "../libft/libft.h"

void       ft_chevron(t_struct *st)
{
    open(st->cmd[1], O_CREAT);
}