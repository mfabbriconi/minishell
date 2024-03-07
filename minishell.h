/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:41:18 by pcalabre &        #+#    #+#             */
/*   Updated: 2024/02/28 19:26:31 by pcalabre &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SHELL_NAME "Minishell$ "

// TYPES
# define COMMAND 0
# define OPERATOR 1
# define REDIRECTION 2

// REDIR
# define OUTPUT_REDIR '>'
# define OUTPUT_REDIR_A ">>"
# define INPUT_REDIR '<'
# define INPUT_REDIR_A "<<"

// ADDS
# define PIPE '|'
# define QUESTION '?'
# define SPACE ' '
# define DOLLAR '$'
# define QUOTE_S '\''
# define QUOTE_D '"'
# define EXIT "exit"

// CODES
# define NONE 0
# define WAITING_OP 1
# define SKIP 2
# define END 3
# define EMPTY 4
# define DEFAULT -500

// ERRORS
# define OK 0
# define MALLOC_ERROR -1
# define ERROR_INVALID_REDIR -2
# define ERROR_CANT_OPENDIR -5
# define ERROR_PARSE -7
# define ERROR_FILE_NOT_FOUND -8
# define ERROR_EXEC -9
# define ERROR_PIPE -10
# define ERROR_HEREDOC_CLOSED -11
# define ERROR_NO_REDIR_ARG -12
# define ERROR_INVALID_OP -13
# define ERROR_UNCLOSED_QUOTES -14

// MODES
# define PROMPT 1
# define FORK 2
# define HEREDOC 3
# define SILENT 4

// HEREDOC
# define HEREDOC_MAX 1000
# define HEREDOC_TMP_FILE ".tmp_heredoc_"

typedef struct s_arg
{
	char				*value;
	struct s_arg		*next;
}						t_arg;

typedef struct s_expression
{
	pid_t				pid;
	int					type;
	char				*value;
	t_arg				*args;
	int					fd_in;
	int					fd_out;
	int					status;
	struct s_expression	*prev;
	struct s_expression	*next;
}						t_expression;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_all
{
	t_expression		*tree;
	t_env				*envs;
	int					g_status;
}						t_all;

extern int				g_signal;

void					ft_set_signals(int mode);
int						executor(t_all *all);
t_expression			*get_last_exp(t_expression *exps);
void					logic_handle_signals(t_expression *exp);

/* PARSER */
int						stop_parse_cmd(char *s);
int						take_str(char *input, int *i, char **str);
int						add_value(t_expression **exp, t_all *all, char *str,
							int *c);
int						is_operator(char *s);
int						is_redirection(char *s);
int						skip_space(char *input, int *i);
int						skip_quote(char *input, int *i);
int						add_arg(t_arg **args, char *str);
void					add_next(t_expression **exps, t_expression *new);
int						add_pipe(t_expression **exps, int i[2]);
int						add_redir(t_all *all, char *input, int i[2]);
int						add_command(t_all *all, char *input, int *i,
							t_expression **last_cmd);
void					solve_quote(t_all *all, char *value, int i[2],
							char *dst);
int						stop_parse_dollar(char *s);
char					*solve_dollar(t_all *all, char *str);
void					expand_dollar(t_all *all, char *str, int i[2],
							char *dst);
char					*solve_value_body(t_all *all, char *value, int hd);

t_env					*parse_envp(char *envp[]);
int						parse_exps(char *input, t_all *all);
void					free_exps(t_expression *exps);
void					print_exps(t_expression *exps);
int						sanitizer(t_all *all);
void					free_envs(t_env *envs);
char					*get_env(t_env *env, char *key);
void					print_env(t_env *env);

/* EXEC */
int						ft_cd(t_expression *cmd, t_env **env);
int						ft_pwd(t_expression *cmd);
int						ft_echo(t_expression *cmd);
char					**ft_env_list_to_matrix(t_env **env);
int						ft_env(t_env **env, t_expression *cmd);
int						ft_export(t_expression *cmd, t_env **env);
int						ft_unset(t_expression *cmd, t_env **env);
int						ft_exit(t_arg *arg);
int						ft_execve(t_expression *exp, t_env **envs);
int						open_heredoc(t_all *all, char *delim, int ghost);
void					delete_heredocs(void);
char					**get_mtx_args(t_arg *args, char *path);
int						check_pipe(t_expression *exp);
char					*get_path(char *arg, t_env *env);
void					set_next_pipe(t_expression *exp, int fd);
void					print_mtx(char **mtx);
int						setup_exec(t_expression *exp, t_env **envs);
int						not_found_or_no_such(char *str, int fd[2], int has_pipe,
							char *path);

/* UTILS */
void					free_mtx(char **mtx);
void					ft_putstr_fd(char *str, int fd);
int						ft_lstsize(t_env **e, t_arg *arg, int a);
int						parse_error_near(char *str);
int						parser_checks(t_expression *tmp, t_expression **exps);
int						get_perms(t_expression *valid_o);
int						delete_and_pop(t_expression **exps, t_expression *cmd,
							t_expression **valid_io, int io[2]);
int						clear_redir(t_all *all, t_expression *valid_redir,
							char redir);
void					ft_add_last(t_env *env, t_env *next);

#endif
