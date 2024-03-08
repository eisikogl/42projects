/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:47:43 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include "../libs/readline/readline.h"
# include "../libs/readline/history.h"
# include "../libs/libft/libft.h"

typedef struct t_envp
{
	char			*key;
	char			*value;
	char			*fullstr;
	struct t_envp	*next;
}	t_envp;

typedef struct s_token
{
	char			*token_value;
	int				token_type;
	struct s_token	*next;
}	t_token;

typedef struct s_parser
{
	char		*input;
	t_token		*tokens;
}	t_parser;

typedef struct s_cmd
{
	int				id;
	t_token			*commands;
	t_token			*redirections;
	int				endpoint;
	int				is_piped;
	char			**exec;
	char			*exec_path;
	char			**envp;
	int				fd_out;
	int				fd_in;
	int				fd_pipe[2];
	int				error_number;
	char			*filename;
	int				s_quotes;
	int				d_quotes;
	int				argc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	t_envp		*envp;
	t_parser	*parser;
	t_cmd		*command;
	int			exit_code;
}	t_minishell;

enum e_token_type
{
	T_WORD,
	T_REDIR_IN,
	T_HEREDOC,
	T_REDIR_OUT,
	T_APPEND,
	T_PIPE,
};

enum e_file_descriptor
{
	IN,
	OUT,
	IN_OUT
};

extern t_minishell	g_minishell;

//builtins
int			is_builtin_command(t_cmd *cmd);
int			strcmp_eq(char *s1, char *s2);
void		put_msg(char *title, char *msg, int fd);
void		send_to_execution_in_parent(t_cmd *command);
void		send_to_execution_in_child(t_cmd *command);
int			cd_builtin(t_cmd *command);
int			echo_builtin(char **exec);
int			env_builtin(t_cmd *command);
int			exit_builtin(void);
int			export_builtin(t_cmd *command);
int			pwd_builtin(void);
int			unset_builtin(t_cmd *command);

//envp
char		**create_execution_envp(void);
char		*get_env_value(char *envp, char *key);
int			env_lst_add_back(t_envp **env_list, char *name,
				char *value, char *fullstr);
void		set_envp(char **envp);
int			validate_var_name(char *var_name);
char		*search_env_value(char *var);
int			get_envp_size(t_envp *envp_lst);
int			save_env_var(char *variable, int validate);

//executer
t_cmd		*init_command(int id);
void		command_add_back(t_cmd *command);
void		execution_phase(void);
void		wait_pids(int pid[1024], int id);
int			is_forked_command(t_cmd *command);
char		*get_command_path(t_cmd *command);
int			define_redirection_fds(void);
void		close_single_fd(t_cmd *command, int fd_type);
void		close_all_fds(void);
int			heredoc(char *filename);
void		open_redirection_files(int redir_type, char *filename, t_cmd *cmd);
void		open_needed_pipes(void);

//expand
int			handle_quotes(t_cmd *cmd, char *arg, int i);
void		handle_dollar_sign(t_cmd *cmd, char *tmp, int i);
void		handle_home(t_cmd *cmd, char *tmp, int i);
void		handle_dollar_sign(t_cmd *cmd, char *tmp, int i);
void		handle_home(t_cmd *cmd, char *tmp, int i);
void		count_quotes(t_cmd *cmd, char *str);
void		expand_args(t_cmd *cmd);

//free
void		del_node(t_envp **env_list, char *word);
void		del_first_node(t_envp **env_list);
void		ft_matrix_free(char ***matrix);
void		free_env_lst(t_envp **env_list);
void		free_tokens(t_token **tokens);
void		free_parser(void);
void		free_command(void);
void		free_path(char **path);
void		free_minishell(void);

//lexer and parser
void		set_commands(void);
t_parser	*init_parser(void);
int			define_token_type(char *token);
int			is_redirection(int prev, int token_type);
int			is_valid_token(const char *input, size_t index, size_t prev);
int			is_valid_command(void);
t_token		*token_dup(t_token *src);
void		token_add_back(t_token **token, t_token *new_token);
int			tokenize_everything(void);

//signals
void		execution_parent_signals(void);
void		execution_child_signals(void);
void		heredoc_parent_signal(void);
void		heredoc_child_signal(void);
void		shell_loop_signal(void);

#endif