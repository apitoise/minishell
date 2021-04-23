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
# include <termios.h>
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
	int					pipe;
	char				*s;
	char				**cmd;
	char				**env;
	t_varlist			*lst;
	t_cmdlist			*cmdlst;
	int					ret;
	int					stdout_fd;
	int					stdin_fd;
	int					stdin_copy;
	int					stdout_copy;
	char				*result;
}						t_struct;

void					minishell(t_struct *st);
void					print_tab(char **map);
void					printlist_env(t_varlist **lst);
void					printlist_export(t_varlist **lst);
void					shell_init(void);
void					print_list(t_varlist **lst);
int						do_chevrons(char **cmd, t_struct *st);
void					shell_init();
char					**del_chevron(char **cmd);
void    				ft_edit_cmd(t_struct *st);
void					init_struct(t_struct *st, char **env);
void					ft_cd(char *path, t_struct *st);
int						ft_echo(char **cmd, t_struct *st);
void					ft_exit(char **cmd);
int						ft_pwd(char **cmd);
int						ft_unset(char **cmd, t_struct *st);
void					ft_export(char **cmd, t_struct *st, int i);
int						first_check(char **cmd);
void					ft_env(t_struct *st);
void					do_builtin(char **cmd, t_struct *st);
void					do_routine(t_struct *st);
void					do_pipe(t_struct *st);
char					**get_env(char **env);
char					**ft_split_cmd(const char *s, char c, t_struct *st);
char					**ft_split_cmdline(char const *s, char c);
int						ft_error(char *s);
int						ft_syntax_error(char *token);
void					ft_checkpath(char **cmd, t_struct *st);
void					not_cmd(char *str, t_struct *st);
void					init_lstenv(char **env, t_struct *st);

int						ft_parsecmdline(char **s, t_struct *st);
int						ft_checkvalid(char *s);
int						ft_dollar(char **s1, t_struct *st);
int						ft_dollar_d(char **s1, int *i, char **s2, t_struct *st);
int						ft_dollar_cat(char **s2, char **tmp);
int						ft_addbslash(char **s);
int						ft_rmbslash(char **s, int i, int j);
int						ft_tkorqt(char *str, int i);
int						ft_freestr(char *str);
int						ft_isspechar(char c);

#endif
