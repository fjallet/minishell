/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:20:58 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/28 01:20:58 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_stdin(char *str, t_token *token)
{
	char	*line;
	char	*buffer;
	int		p[2];

	pipe(p);
	buffer = NULL;
	line = get_next_line(0);
	while (strncmp(str, line, (strlen(line) - 1)))
	{
		buffer = ft_strjoin1(buffer, line);
		line = get_next_line(0);
	}
	ft_putstr_fd(buffer, p[1]);
	close(p[1]);
	token->fd = p[0];
}

t_token	*check_dollar(t_token *cmd, t_mini *mini, int size)
{
	int	i;

	i = 0;
	while (cmd[i].value)
	{
		if (cmd[i].dollar)
		{
			cmd[i].value = ft_dollar(cmd[i].value, '"', mini);
			if (!cmd[i].value || ft_strlen(cmd[i].value) <= 0)
			{
				cmd = remove_cmd(cmd, size--, i);
				cmd = check_dollar(cmd, mini, size);
				break ;
			}
			cmd = cmd_update(cmd, mini, &size, i);
			break ;
		}
		i++;
	}
	return (cmd);
}

void	ft_reset_token2(t_token *token)
{
	token->type = TOKEN_NULL;
	token->value = NULL;
}

t_token	*get_cmd(char *str, t_mini *mini)
{
	t_token	*cmd;
	t_token	tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = (t_token *) malloc (sizeof(t_token) * 1);
	while (str[i] && ft_whitespace(str[i]))
		i++;
	while (str[i])
	{
		tmp = get_arg(str, &i, mini, 0);
		if (tmp.value)
		{
			cmd = add_token(cmd, tmp, j);
			j++;
		}
		while (str[i] && ft_whitespace(str[i]))
			i++;
	}
	ft_reset_token2(&cmd[j]);
	cmd = check_dollar(cmd, mini, j);
	ft_parse_token(cmd, mini);
	return (cmd);
}
