#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
//# define BUFFER_SIZE 42

int						EXIT_CODE;

typedef struct			s_varlist
{
	char				*name;
	char				*content;
	void				*next;
}						t_varlist;

typedef struct			s_struct
{
	int					exit;
	char				*s;
	char				**cmd;
	char				**env;
	t_varlist			*lst;
}						t_struct;

void					print_tab(char **map);

void					shell_init(void);
void					init_struct(t_struct *st, char **env);
void					ft_cd(char *path);
int						ft_echo(char **cmd, t_varlist **lst);
void					ft_exit(char **cmd);
int						ft_pwd(char **cmd);
int						ft_unset(t_struct *st);
void					ft_export(char **cmd, t_varlist **lst, int i);

int						ft_env(char **env);
char					**get_env(char **env);

int						ft_error(char *s);

char					*ft_trim(char const *s1);

#endif
