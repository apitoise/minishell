#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
//# define BUFFER_SIZE 42

typedef struct			s_varlist
{
	char				*name;
	char				*content;
	int				visible;
	void				*next;
}						t_varlist;

typedef	struct			s_cmdlist
{
	char				*cmd;
	char				*arg;
	void				*next;
}						t_cmdlist;

typedef struct			s_struct
{
	int					exit;
	char				*s;
	char				**cmd;
	char				**env;
	t_varlist			*lst;
	t_cmdlist			*cmdlst;
	int					ret;
	int					fd;
	int					stdout_copy;
	char				*result;
}						t_struct;

void					print_tab(char **map);
void					printlist_env(t_varlist **lst);
void					printlist_export(t_varlist **lst);
void					shell_init(void);
void					print_list(t_varlist **lst);
void					do_chevrons(t_struct *st);
void					shell_init();
void					init_struct(t_struct *st, char **env);
void					ft_cd(char *path, t_struct *st);
int						ft_echo(char **cmd, t_varlist **lst, t_struct *st);
void					ft_exit(char **cmd);
int						ft_pwd(char **cmd);
void					check_cmd(char **cmd, int i);
int						ft_unset(t_struct *st);
void					ft_export(t_struct *st, int i);
int						first_check(t_struct *st);
void					ft_env(t_struct *st);
void					do_builtin(t_struct *st);
char					**get_env(char **env);
char					**ft_split_cmd(const char *s, char c);
int						ft_error(char *s);
void					ft_checkpath(t_struct *st);
void					not_cmd(char *str, t_struct *st);
char					*ft_trim(char const *s1);
void					init_lstenv(char **env, t_struct *st);

#endif
