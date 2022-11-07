/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:10:11 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 12:27:31 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_built_in(char **command)
{
	*command = ft_strdup2(*command);
	return (VALID_CMD);
}

int	default_pipe(int *input_fd, int *pipe_fd)
{
	int	other_pipe[2];

	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (pipe(other_pipe) == -1)
		return (-1);
	close(other_pipe[1]);
	*input_fd = other_pipe[0];
	return (0);
}

void	get_i_incr(char *str, int *i)
{
	if (str[*i])
		(*i)++;
}

void	get_type_value(t_token *tmp, t_helper *save)
{
	tmp->type = TOKEN_ARGUMENT;
	tmp->value = ft_strjoin1(tmp->value, save->tmp);
}

int	last_details(t_pstat *pipe_status, int cmd_nbr,
	t_pipe *pipes, int *input_fd)
{
	t_mini	*mini;

	mini = pipes->mini;
	if (pipes[cmd_nbr - 1].parse_cmd[0] == NULL && cmd_nbr > 1)
		mini->exit_status = 0;
	if (*input_fd > 0)
		close(*input_fd);
	free(pipe_status);
	return (1);
}
