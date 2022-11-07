/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstatus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:47:07 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/29 23:47:07 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pstat	*create_pipes_status(t_pstat **pipe_status, t_mini *mini, int pipe_size)
{
	int			i;

	*pipe_status = malloc(sizeof(t_pstat) * pipe_size);
	if (!*pipe_status)
	{
		mini->exit_status = 1;
		return (NULL);
	}
	i = -1;
	while (++i < pipe_size)
	{
		(*pipe_status)[i].pid = 0;
		(*pipe_status)[i].status = 0;
	}
}

int	wait_all_pid(t_pstat *pipe_status, int size)
{
	int	i;
	int	status;

	i = 0;
	if (!pipe_status)
		return (1);
	while (i < size)
	{
		if (&pipe_status[i] != NULL && pipe_status[i].pid > 0)
		{
			waitpid(pipe_status[i].pid, &status, 0);
			if (WIFEXITED(status))
				pipe_status[i].status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				pipe_status[i].status = 128 + WTERMSIG(status);
			else if (WIFSTOPPED(status))
				pipe_status[i].status = 128 + WSTOPSIG(status);
			else if (WIFCONTINUED(status))
				pipe_status[i].status = 128 + WIFCONTINUED(status);
		}
		++i;
	}
	return (1);
}
