/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:06:20 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/11 18:22:10 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <string.h>
# include <limits.h>
# include <termios.h>
# include <curses.h>
# include <ncurses.h>
# include <term.h>
# include <errno.h>
# define MAX_FD 3000

typedef struct			s_sig
{
	pid_t	pid;
	int		sig_ret;
}						t_sig;

typedef struct			s_varlist
{
	char				*name;
	char				*content;
	int					visible;
	void				*next;
}						t_varlist;

typedef	struct			s_history
{
	char				*cmdline;
	size_t				len;
	size_t				capacity;
}						t_history;

typedef struct			s_struct
{
	int					exit;
	int					pipe;
	char				*s;
	char				**input;
	char				**cmd;
	char				**env;
	pid_t				pid;
	t_varlist			*lst;
	int					ret;
	int					stdout_fd;
	int					stdin_fd;
	int					stdin_copy;
	int					stdout_copy;
	char				*result;
	int					ttywidth;
	int					ttyheight;
	int					startposx;
	int					posx;
	int					posy;
	t_history			**hstab;
	size_t				hslen;
	size_t				hscapacity;
	unsigned int		hsindex;
}						t_struct;

extern t_sig			g_sig;

void					minishell(t_struct *st);
void					print_tab(char **map);
void					printlist_env(t_varlist **lst);
void					printlist_export(t_varlist **lst);
void					shell_init(void);
void					print_list(t_varlist **lst);
int						do_chevrons(char **cmd, t_struct *st);
void					shell_init();
char					**del_chevron(char **cmd);
void					ft_edit_cmd(t_struct *st);
void					init_struct(t_struct *st, char **env);
void					init_sig_struct(void);
void					ft_cd(char *path, t_struct *st);
int						ft_echo(char **cmd, t_struct *st);
void					ft_exit(char **cmd, t_struct *st);
void					ft_clean_exit(char *str, t_struct *st);
int						ft_pwd(char **cmd);
int						ft_unset(char **cmd, t_struct *st);
void					ft_export(char **cmd, t_struct *st, int i);
void					ft_varlstclear(t_varlist **lst);
int						first_check(char **cmd, t_struct *st);
void					ft_env(t_struct *st);
void					do_builtin(char **cmd, t_struct *st);
void					do_routine(t_struct *st);
void					do_pipe(t_struct *st);
char					**get_env(char **env);
void					ft_split_cmd(const char *s, char c,
t_struct *st, int i);
char					**ft_split_cmdline(char const *s, char c);
int						ft_error(char *s);
int						ft_syntax_error(char *token, t_struct *st);
void					ft_checkpath(char **cmd, t_struct *st);
void					not_cmd(char *str, t_struct *st);
void					init_lstenv(char **env, t_struct *st);
void					get_signals(t_struct *st);
void					ctrl_c(int useless);
void					ctrl_backslash(int useless);
void					ft_exec(char **cmd, char *filepath, t_struct *st);
int						ft_parsecmdline(char **s, t_struct *st);
int						ft_checkvalid(char *s, t_struct *st);
int						ft_dollar(char **s1, t_struct *st);
int						ft_dollar_d(char **s1, int *i, char **s2, t_struct *st);
int						ft_dollar_cat(char **s2, char **tmp);
int						ft_addbslash(char **s);
int						ft_rmbslash(char **s, int i, int j);
int						ft_tkorqt(char *str, int i);
int						ft_freestr(char *str);
int						ft_isspechar(char c);
int						init_termcap(t_struct *st);
int						ft_getwinsz(t_struct *st);
char					*getcmdline(t_struct *st);
int						ft_putc(int c);

#endif
