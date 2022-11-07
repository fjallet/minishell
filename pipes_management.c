/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 00:18:02 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/30 00:18:02 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_in_pipe(t_pipe *pipe, t_mini *mini, int count)
{
	int	i;
	int	j;

	i = 0;
	pipe[i].parse_cmd = NULL;
	while (i < count)
	{
		pipe[i].parse_cmd = ft_malloc(sizeof(char *) * (pipe[i].cmd_count + 1));
		j = 0;
		while (j < pipe[i].cmd_count)
		{
			pipe[i].parse_cmd[j] = pipe[i].cmd[j].value;
			j++;
		}
		pipe[i].parse_cmd[j] = NULL;
		i++;
	}
	mini->pipe = pipe;
	mini->pipe_length = count;
}

void	ft_add_pipe(t_token *token, t_pipe *pipe, int i, int j)
{
	pipe[i].cmd = ft_malloc(sizeof(t_token) * (pipe[i].cmd_count + 2));
	pipe[i].files = ft_malloc(sizeof(t_token) * (pipe[i].files_count + 2));
	pipe[i].cmd_count = 0;
	pipe[i].files_count = 0;
	while (token[j].type && token[j].type != TOKEN_PIPE)
	{
		if (token[j].type == TOKEN_ARGUMENT || token[j].type == TOKEN_COMMAND)
		{
			pipe[i].cmd[pipe[i].cmd_count++] = ft_copy_token(token[j]);
		}
		else if (token[j].type >= TOKEN_REDIRECTION_INPUT
			&& token[j].type <= TOKEN_REDIRECTION_DELIMTER)
		{
			if (token[j].type != TOKEN_REDIRECTION_DELIMTER)
			{
				pipe[i].files[pipe[i].files_count] = ft_copy_token(token[++j]);
				pipe[i].files[pipe[i].files_count].type = token[j - 1].type;
			}
			else
				pipe[i].files[pipe[i].files_count] = ft_copy_token(token[j]);
			pipe[i].files_count++;
		}
		if (token[j].type)
			j++;
	}
}

t_pipe	*ft_create_pipe(t_token *token, int count)
{
	t_pipe	*pipe;
	int		i;
	int		j;
	int		n;

	pipe = ft_malloc(sizeof(t_pipe) * (count + 1));
	i = 0;
	j = 0;
	while (i < count)
	{
		pipe[i].cmd_count = 0;
		pipe[i].files_count = 0;
		n = j;
		while (token[j].value && token[j].type != TOKEN_PIPE)
			get_cmd_files_count(token, pipe, i, &j);
		ft_add_pipe(token, pipe, i, n);
		if (token[j].type == TOKEN_PIPE)
			j++;
		i++;
	}
	return (pipe);
}
