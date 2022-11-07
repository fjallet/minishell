/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:05:26 by abouleau          #+#    #+#             */
/*   Updated: 2022/10/06 18:05:26 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_invalid_cmd(t_pstat *pipe_status, char **args, int *status)
{
	free_args(args);
	input_error("?", "!", 0);
	*status = 1;
	free(pipe_status);
	return (-1);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	check_redir(int	*redir, int last_pipe, int *pipe_fd, int *input_fd)
{
	if (*redir == 0 && last_pipe && print_stdout(pipe_fd[1]) < 0)
	{
		*redir = -2;
		return (1);
	}
	else if (*redir == INVALID_FD)
	{
		*redir = default_pipe(input_fd, pipe_fd);
		return (1);
	}
	return (0);
}

void	ft_set_base(t_token *token, t_helper *save, t_mini *mini)
{
	token->value = ft_calloc(sizeof(char), 1);
	token->dollar = 0;
	token->fd = 0;
	save->tmp = ft_calloc(sizeof(char), 2);
	save->mini = mini;
}

int	ft_expand(char c)
{
	return ((c == '"' || c == '\''));
}
