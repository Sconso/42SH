/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 23:03:12 by sconso            #+#    #+#             */
/*   Updated: 2014/03/27 18:54:07 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H

# include <string.h>
# define INVIT "\r\033[K\033[1;31mTest >\033[0m "

typedef struct		s_command
{
	char				*data;
	int					type;
	struct s_command	*next;
	struct s_command	*prev;
}					t_command;

typedef struct		s_list
{
	t_command		*first;
	t_command		*last;
	int				size;
}					t_list;

typedef struct		s_env
{
	char			**env;
	char			**path;
	int				in;
	int				out;
}					t_env;

typedef struct		s_index
{
	int				i;
	int				j;
	int				k;
}					t_index;

typedef struct		s_builtins
{
	char			*name;
	int				(*func)(char **cmd, char ***env);
}					t_builtins;

typedef enum		e_types
{
	CMD,
	SEMICOL,
	AND,
	OR,
	PIPE,
	SIN,
	SOUT,
	DIN,
	DOUT
}					t_types;

/*
** ft_42sh.c
*/
t_command	*ft_pipe(t_command *cmd);

/*
** ft_cd.c
*/
int			ft_cd(char **cmd, char ***env);

/*
** ft_cd_error.c
*/
int			ft_chdir(char *path);

/*
** ft_echo.c
*/
int			ft_echo(char **cmd, char ***env);

/*
** ft_env.c
*/
char		**ft_cpy_env(char **env);
char		**ft_get_path(char **env);
char		*ft_get_key(char **env, char *key);

/*
** ft_env_cmds.c
*/
int			ft_env(char **cmd, char ***env);
int			ft_setenv(char **cmd, char ***env);
int			ft_unsetenv(char **cmd, char ***env);

/*
** ft_errors.c
*/
int			ft_assert(int test);
int			ft_error(char *str);
void		ft_exit(char *str);
int			ft_line_error(char *str, char *line);
int			ft_file_error(char *file, char *error);

/*
** ft_execve.c
*/
int			ft_execve(char **cmd, t_env *env);

/*
** ft_fd.c
*/
void		ft_save_fd(t_env *env);
void		ft_reset_fd(t_env *env);

/*
** ft_io.c
*/
void		ft_test_redir(t_command *cmd);
int			ft_change_in(char *file, int app);
int			ft_change_out(char *file, int app);

/*
** ft_lexer.c
*/
void		ft_lexer(t_list *lst, t_env *env);

/*
** ft_list.c
*/
t_list		*ft_newlist(void);
t_command	*ft_pushfirst(t_list *list, char *data, int type);
t_command	*ft_pushlast(t_list *list, char *data, int type);
void		ft_free_list(t_list **list);
void		ft_printlist(t_list *list);

/*
** ft_mem.c
*/
void		*ft_malloc(long size);

/*
** ft_parsing.c
*/
int			ft_parsing(char **command, t_list *lst);

/*
** ft_pipe.c
*/
t_command	*ft_pipe(t_command *cmd);

/*
** ft_quotes.c
*/
char		ft_is_quote(char c);
char		**ft_ask_quote(char quote, char **command);
int			ft_quotes(int *i, char *command);

/*
** ft_signal.c
*/
void		handle_signal(int signo);
void		ft_signals(void);

/*
** ft_strsplitarg.c
*/
char		**ft_strsplitarg(char const *s);

/*
** ft_tokens.c
*/
char		ft_istoken(char c);
int			ft_test_token(char *tmp);
void		ft_add_token(char *command, int i, int j, t_list *lst);

/*
** ft_utilities.c
*/
void		ft_free_matrix(char ***matrix);
t_index		*ft_init_index(int i, int j, int k);
char		*ft_cstrtrim(char **str);
char		*ft_cstrsub(char **str, unsigned int start, size_t len);
int			ft_strccmp(const char *s1, const char *s2, char c);
#endif
