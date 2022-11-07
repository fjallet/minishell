/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 00:18:45 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/30 00:18:45 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*remove_cmd(t_token *old_cmd, int size, int range)
{
	t_token	*new_cmd;
	int		i;
	int		j;

	new_cmd = ft_calloc(sizeof(t_token), size + 1);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (i != range)
			new_cmd[j++] = old_cmd[i];
		i++;
	}
	new_cmd[j].value = NULL;
	new_cmd[j].type = 0;
	if (old_cmd[range].value)
		free(old_cmd[range].value);
	free(old_cmd);
	return (new_cmd);
}

t_token	*insert_cmd(t_token *old_cmd, int size, int ins, t_token tmp)
{
	t_token	*new;
	int		i;
	int		j;

	new = ft_malloc(sizeof(t_token) * (size + 1));
	i = 0;
	j = 0;
	while (i < size)
	{
		if ((i) == ins)
			new[j++] = tmp;
		else if (i > ins)
			new[j++] = old_cmd[i - 1];
		else
			new[j++] = old_cmd[i];
		i++;
	}
	new[j].value = NULL;
	new[j].type = 0;
	free(old_cmd);
	return (new);
}

t_token	*cmd_update(t_token *cmd, t_mini *mini, int *size, int i)
{
	int		j;
	int		count;
	t_token	tmp;

	j = 0;
	count = 1;
	while (cmd[i].value[j])
	{
		tmp = get_arg(cmd[i].value, &j, mini, 1);
		tmp.type = cmd[i].type;
		tmp.dollar = 0;
		cmd = insert_cmd(cmd, ++(*size), i + count++, tmp);
		while (cmd[i].value[j] && cmd[i].value[j] == ' ')
			j++;
	}
	cmd = remove_cmd(cmd, (*size)--, i);
	cmd = check_dollar(cmd, mini, (*size));
	return (cmd);
}

void	get_cmd_files_count(t_token *token, t_pipe *pipe, int i, int *j)
{
	if (token[*j].type == TOKEN_ARGUMENT
		|| token[*j].type == TOKEN_COMMAND)
		pipe[i].cmd_count++;
	else if (token[*j].type >= TOKEN_REDIRECTION_INPUT
		&& token[*j].type <= TOKEN_REDIRECTION_DELIMTER)
	{
		if (token[*j].type != TOKEN_REDIRECTION_DELIMTER)
			(*j)++;
		pipe[i].files_count++;
	}
	if (token[*j].value)
		(*j)++;
}

void	get_cmd_files(t_token *token, int *i)
{
	int	cmd;

	cmd = 1;
	while (token[*i].value && token[*i].type != TOKEN_PIPE)
	{
		if (token[*i].value && token[*i].type >= 4 && token[*i].type <= 8
			&& token[*i].type != TOKEN_REDIRECTION_DELIMTER)
		{
			(*i)++;
			if (token[*i].value && token[*i].type == TOKEN_ARGUMENT)
				token[*i].type = TOKEN_FILE;
		}
		else if (cmd && token[*i].value && token[*i].type == TOKEN_ARGUMENT)
		{
			token[*i].type = TOKEN_COMMAND;
			cmd = 0;
		}
		if (token[*i].value)
			(*i)++;
	}
}
