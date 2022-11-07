/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:23:19 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 13:42:53 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_command(int fd_in, int	*pipe_fd, char **parsed_cmd, t_mini *mini)
{
	if (dup2(fd_in, 0) == -1 || dup2(pipe_fd[1], 1) == -1)
		return (-1);
	close_pipe(pipe_fd);
	if (fd_in != 0)
		close(fd_in);
	if (!parsed_cmd)
		perror("split error");
	if (is_built_in(parsed_cmd[0]))
		exit(exec_built_in(parsed_cmd, mini, 0, 1));
	if (execve(parsed_cmd[0], &parsed_cmd[0], mini->full_env) == -1)
		input_error("Command execution", parsed_cmd[0], 0);
	return (-1);
}

int	run_process_command(int fd_in, char **pipe_cmd,
t_mini *mini, int *new_pipe_fd)
{
	pid_t	pid;

	if (fork_store(&pid) == -1)
		return (-1);
	if (pid == 0)
		return (run_command(fd_in, new_pipe_fd, pipe_cmd, mini));
	if (dup2(new_pipe_fd[0], fd_in) == -1)
		return (-1);
	close_pipe(new_pipe_fd);
	return (pid);
}

int	set_pipe(t_pstat *pstat, int *fd_in, int *pipe_fd)
{
	pstat->status = 1;
	return (default_pipe(fd_in, pipe_fd));
}

int	run_solo_builtin(t_pipe pipe, t_mini *mini)
{
	int		fd_in;
	int		fd_out;
	int		test;

	fd_in = 0;
	fd_out = 1;
	test = get_fd(pipe, &fd_in, &fd_out);
	if (test == INVALID_FD)
	{
		mini->exit_status = 1;
		return (0);
	}
	mini->exit_status = exec_built_in(pipe.parse_cmd, mini, 0, fd_out);
	return (0);
}

void	minishell(char **line, t_mini *mini, t_token *cmd)
{
	add_history(*line);
	if (*line[0])
	{
		if (!ft_check_syntax(*line))
		{
			cmd = get_cmd(*line, mini);
			free_cmd(cmd);
			free_pipe(mini);
		}
		else
			mini->exit_status = 1;
	}
	if (mini->signaldelimiters == 1)
	{
		dup2(mini->dup_fd, 0);
		mini->signaldelimiters = 0;
		signal(SIGINT, signal_c);
	}
	free(*line);
	if (mini->end == -1 && isatty(0))
		*line = readline("\e[0;35mMini\e[0;33mshell $>\e[0;37m ");
}
