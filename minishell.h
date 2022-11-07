/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:24:34 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 20:05:27 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/wait.h>
# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"

# define TOKEN_NULL 0
# define TOKEN_COMMAND 1
# define TOKEN_ARGUMENT 2
# define TOKEN_PIPE 3
# define TOKEN_REDIRECTION_INPUT 4 // >
# define TOKEN_REDIRECTION_OUTPUT 5 // <
# define TOKEN_REDIRECTION_APPEND 6 // >>
# define TOKEN_REDIRECTION_DELIMTER 7 // <<
# define TOKEN_REDIRECTION_OTHER 8 // <>
# define TOKEN_FILE 9
# define TOKEN_ERROR 10 //

# define VALID_CMD 1 //
# define INVALID_CMD 3 //
# define EXCUTE_NOT 4 //
# define INVALID_FD -1 //

// typedef struct t_mini s_mini;

typedef struct s_pstat
{
	pid_t	pid;
	int		status;
}	t_pstat;

typedef struct s_token
{
	int		type;
	char	*value;
	int		fd;
	int		dollar;
}	t_token;

typedef struct s_pipe
{
	t_token			*cmd;
	char			**parse_cmd;
	int				cmd_count;
	t_token			*files;
	int				files_count;
	char			**args;
	int				pipe_fd[2];
	int				redir;
	struct s_mini	*mini;
}	t_pipe;

typedef struct s_env
{
	char	*name;
	char	*value;
	int		init;
}	t_env;

typedef struct s_mini
{
	void	(*signal_save)(int);
	void	(*signal_c)(int);
	void	(*signal_c2)(int);
	void	(*signal_c4)(int);
	int		signaldelimiters;
	char	*exit_char;
	int		dup_fd;
	t_env	*env;
	int		env_length;
	char	**full_env;
	int		exit_status;
	int		print_exit;
	int		end;
	int		pipe_length;
	t_pipe	*pipe;
}				t_mini;

typedef struct s_helper
{
	char	*line;
	char	*save;
	int		change;
	char	*ret;
	char	*temp;
	int		start;
	char	*tmp;
	char	*tmp2;
	char	*str;
	char	*copy;
	t_mini	*mini;
	t_pipe	*pipe;
}	t_helper;

typedef struct s_ep
{
	t_pipe	*pipe;
	t_mini	*m;
}	t_ep;

void	minishell(char **line, t_mini *mini, t_token *cmd);
void	free_all(t_mini *mini);
void	free_cmd(t_token *cmd);
void	free_pipe(t_mini *mini);
void	get_input(int *input_fd, t_token *file);
void	get_output(int *output_fd, t_token *file);
void	dup_env(char **env, t_mini *mini);
int		ft_check_syntax(char *str);
void	*ft_malloc(size_t nb);
int		fork_store(pid_t *pid_res);
int		run_pipes(t_pipe *pipes, int cmd_nbr, t_mini *mini);
int		get_fd(t_pipe pipe, int *input_fd, int *output_fd);
int		get_fds(t_pipe pipe, int *input_fd, int *output_fd, t_pstat *pstat);
int		exec_built_in(char **cmd, t_mini *mini, int fd_in, int fd_out);
t_pstat	*create_pipes_status(t_pstat **pipe_status,
			t_mini *mini, int pipe_size);
int		wait_all_pid(t_pstat *pipe_status, int size);
int		print_stdout(int fd);
int		default_pipe(int *input_fd, int *pipe_fd);
char	**get_args(t_pipe *pipe_a, t_mini *mini, int *redir, t_pstat *pstat);
int		input_error(char *error_type, char	*precision, int type);
char	**args_cpy(char **cmd, int size);
int		ft_tern(int condition, int a, int b);
void	*free_split(char **splited);
void	update_env(t_mini *mini);
char	*ft_strdup2(const char *s);
int		is_built_in(char *cmd);
int		is_path(char *cmd);
void	close_pipe(int *pipe);
int		run_solo_builtin(t_pipe pipe, t_mini *mini);
int		run_cmd(t_pipe *pipe, t_mini *mini, int cmd_nbr, char **env);
void	msg_error(char *str);
void	get_i_incr(char *str, int *i);
void	get_type_value(t_token *tmp, t_helper *save);
void	copy_env(t_mini *mini);
char	**error_args_path(t_pstat *pstat, char **paths, int *redir, int choice);
int		last_details(t_pstat *pipe_status,
			int cmd_nbr, t_pipe *pipes, int *input_fd);
void	free_args(char **args);
int		check_redir(int	*redir, int last_pipe, int *pipe_fd, int *input_fd);
int		free_invalid_cmd(t_pstat *pipe_status, char **args, int *status);
int		write_fd(char *s, int fd);
int		ft_strlen_c(char *s, char c);
int		ft_clean_export(char *s, int *ret);
void	ft_printexport(t_mini *mini, int fd_out);
t_env	*ft_copy_env(t_mini *mini);
int		cmd_built_in(char **command);
int		ft_expand(char c);
int		free_pipe2(t_pstat *pipe_status);
int		free_args2(t_pstat *pstat, char **args, int choice);
int		redirections(t_pipe pipe, int *fd_in, int *fd_out);
int		set_pipe(t_pstat *pstat, int *fd_in, int *pipe_fd);
int		run_process_command(int fd_in, char **pipe_cmd,
			t_mini *mini, int *new_pipe_fd);
int		run_command(int fd_in, int	*pipe_fd, char **parsed_cmd, t_mini *mini);

void	ft_setenv(t_mini *mini, char *name, char *value, int init);
void	ft_setenv1(t_mini *mini, int *i, t_env *env, char *value);
void	ft_setenv2(t_mini *mini, char *name, char *value, int init);
void	ft_replaceenv(t_mini *mini, char *name, char *value);
void	free_full_env(t_mini *mini);

int		built_in_cd(char **cmd, t_mini *mini);
int		built_in_echo(char **cmd, int fd_out);
int		built_in_pwd(int fd_out);
int		built_in_env(t_mini *mini, int fd_out);
int		built_in_export(char **cmd, t_mini *mini, int fd_out);
int		built_in_unset(char **cmd, t_mini *mini);
int		built_in_exit(char **cmd, t_mini *mini);
int		ft_hasenv(t_mini *mini, char *name);
int		ft_check_arg(char *str);

char	*ft_dollar(char *str, char c, t_mini *mini);
t_token	*get_cmd(char *str, t_mini *mini);
t_token	*check_dollar(t_token *cmd, t_mini *mini, int size);
t_token	get_arg(char *str, int *i, t_mini *mini, int choice);
int		ft_whitespace(char c);
t_token	*add_token(t_token *old_cmd, t_token tmp, int size);
void	ft_parse_token(t_token *token, t_mini *mini);
t_token	*remove_cmd(t_token *old_cmd, int size, int range);
t_token	*cmd_update(t_token *cmd, t_mini *mini, int *size, int i);
void	read_stdin(char *str, t_token *token);
void	get_cmd_files(t_token *token, int *i);
void	get_cmd_files_count(t_token *token, t_pipe *pipe, int i, int *j);
t_pipe	*ft_create_pipe(t_token *token, int count);
void	get_in_pipe(t_pipe *pipe, t_mini *mini, int count);
t_token	ft_copy_token(t_token token);
char	*ft_getenv(t_mini *mini, char *name);
t_token	get_redir(char *str, char c, int *i, t_mini *mini);
void	ft_set_base(t_token *token, t_helper *save, t_mini *mini);

void	signal_c(int sig);
void	signal_c3(int sig);
void	signal_c2(int sig);
void	signal_c4(int sig);
void	signal_delimiters(t_mini *mini, int i);
void	ft_delimiters(char *s, t_token *token, t_mini *mini, int expand);
void	ft_delimiters1(char *ret, char *s, int *pipes, t_token *token);
void	ft_delimiters2(t_helper *save, char *s, int expand);

#endif
