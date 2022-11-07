/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 00:16:39 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/30 00:16:39 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_token(t_token *old_cmd, t_token tmp, int size)
{
	int		i;
	t_token	*new_cmd;

	i = 0;
	new_cmd = (t_token *) malloc (sizeof(t_token) * (size + 2));
	while (i < size)
	{
		new_cmd[i] = old_cmd[i];
		i++;
	}
	new_cmd[i++] = tmp;
	new_cmd[i].type = TOKEN_NULL;
	new_cmd[i].value = NULL;
	free(old_cmd);
	return (new_cmd);
}

int	ft_check_token_syntax(t_token *token, int i)
{
	if (i > 0 && token[i - 1].type == TOKEN_PIPE)
		return (1);
	i = 0;
	while (token[i].value)
	{
		if (token[i].type && token[i].type == TOKEN_ERROR)
			return (1);
		if (token[i].type >= 4 && token[i].type <= 8
			&& token[i].type != TOKEN_REDIRECTION_DELIMTER)
		{
			if (!token[i + 1].value || token[i + 1].type != TOKEN_FILE)
				return (1);
		}
		i++;
	}
	return (0);
}

t_token	ft_copy_token(t_token token)
{
	t_token	copy;

	copy.value = token.value;
	copy.type = token.type;
	copy.fd = token.fd;
	copy.dollar = token.dollar;
	return (copy);
}

/*void	print_pipe(t_pipe *pipe, t_mini *mini)
{
	int	i = 0;
	int	j = 0;
	while(i < mini->pipe_length)
	{
		j = 0;
		while(pipe[i].parse_cmd[j])
		{
			printf("pipe[%d].parse_cmd[%d] == %s\n", i, j, pipe[i].parse_cmd[j]);
			if(pipe[i].files[j].value)
				printf("pipe[%d].files[%d] == %s\n", i, j, pipe[i].files[j].value);
			if(pipe[i].files[j].type)
				printf("pipe[%d].files[%d].type == %d\n", i, j, pipe[i].files[j].type);
			j++;
		}
		i++;
	}
}*/

void	ft_parse_token(t_token *token, t_mini *mini)
{
	int		i;
	int		count;
	t_pipe	*pipe;

	i = 0;
	count = 0;
	while (token[i].value)
	{
		get_cmd_files(token, &i);
		count++;
		if (token[i].value && token[i].type == TOKEN_PIPE)
			i++;
	}
	pipe = ft_create_pipe(token, count);
	get_in_pipe(pipe, mini, count);
	if (ft_check_token_syntax(token, i))
	{
		msg_error("Minishell : syntax error\n");
		mini->exit_status = 1;
		return ;
	}
	if (mini->signaldelimiters != 0 || count <= 0)
		return ;
	run_cmd(pipe, mini, count, mini->full_env);
}
