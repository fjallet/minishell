/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:52:08 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 13:42:04 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init(int *fd_in, t_pstat *pstat, t_helper *save, int last_pipe)
{
	char		**args;
	int			redir;
	int			pipe_fd[2];

	if (pipe(pipe_fd) == INVALID_FD)
		return (INVALID_FD);
	redir = redirections(*(save->pipe), fd_in, &pipe_fd[1]);
	if (redir == 0 && last_pipe && print_stdout(pipe_fd[1]) < 0)
		return (-2);
	else if (redir == INVALID_FD)
		return (set_pipe(pstat, fd_in, pipe_fd));
	else if (!save->pipe->parse_cmd[0])
		return (0);
	args = get_args(save->pipe, save->mini, &redir, pstat);
	if (redir == INVALID_CMD || redir == EXCUTE_NOT)
		return (0);
	else if (redir == VALID_CMD)
	{
		pstat->pid = run_process_command(*fd_in, args, save->mini, pipe_fd);
		if (pstat->pid == INVALID_FD)
			return (free_args2(pstat, args, 1));
	}
	return (free_args2(pstat, args, 2));
}

int	run_pipes(t_pipe *pipes, int cmd_nbr, t_mini *mini)
{
	t_pstat		*pipe_status;
	int			i;
	int			fd_in;
	t_helper	save;

	fd_in = 0;
	if (!create_pipes_status(&pipe_status, mini, cmd_nbr))
		return (-1);
	i = 0;
	while (i < cmd_nbr)
	{
		save.mini = mini;
		save.pipe = &pipes[i];
		if (ft_init(&fd_in, &pipe_status[i], &save, i + 1 == cmd_nbr) < 0)
			return (free_pipe2(pipe_status));
		++i;
	}
	wait_all_pid(pipe_status, cmd_nbr);
	mini->exit_status = pipe_status[cmd_nbr - 1].status;
	if (pipes[cmd_nbr - 1].parse_cmd[0] == NULL && cmd_nbr > 1)
		mini->exit_status = 0;
	if (fd_in > 0)
		close(fd_in);
	free(pipe_status);
	return (1);
}

int	run_cmd2(t_pipe *pipe, t_mini *mini, int cmd_nbr)
{
	mini->end = 1;
	signal(SIGINT, mini->signal_c4);
	if (run_pipes(pipe, cmd_nbr, mini) == -1)
	{
		mini->exit_status = 1;
		return (0);
	}
	mini->end = 0;
	close(0);
	return (1);
}

int	run_cmd(t_pipe *pipe, t_mini *mini, int cmd_nbr, char **env)
{
	pid_t	pid;
	int		status;

	(void)env;
	mini->exit_status = 0;
	if (cmd_nbr == 1 && is_built_in(pipe[0].parse_cmd[0]))
		return (run_solo_builtin(pipe[0], mini));
	if (fork_store(&pid) == -1)
	{
		mini->exit_status = 1;
		return (-1);
	}
	if (pid == 0)
		return (run_cmd2(pipe, mini, cmd_nbr));
	else
	{
		signal(SIGINT, mini->signal_c2);
		waitpid(pid, &status, 0);
		mini->exit_status = WEXITSTATUS(status);
		signal(SIGINT, mini->signal_c);
	}
	return (0);
}
