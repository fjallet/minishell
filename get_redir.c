/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:25:46 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 13:56:57 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_redirection(char *s)
{
	if (ft_strcmp(s, ">") == 0)
		return (TOKEN_REDIRECTION_INPUT);
	else if (ft_strcmp(s, "<") == 0)
		return (TOKEN_REDIRECTION_OUTPUT);
	else if (ft_strcmp(s, ">>") == 0)
		return (TOKEN_REDIRECTION_APPEND);
	else if (ft_strcmp(s, "<<") == 0)
		return (TOKEN_REDIRECTION_DELIMTER);
	else if (ft_strcmp(s, "<>") == 0)
		return (TOKEN_ERROR);
	return (TOKEN_ERROR);
}

t_token	get_redir1(int *i, char *str, t_mini *mini)
{
	t_token	tmp;
	t_token	tmp2;

	tmp.dollar = 0;
	tmp.type = 0;
	tmp.fd = 0;
	tmp.value = ft_strndup(str + *i, 2);
	tmp.type = ft_get_redirection(tmp.value);
	(*i) += 2;
	if (tmp.type == TOKEN_REDIRECTION_DELIMTER)
	{
		while (str[(*i)] && ft_whitespace(str[*i]))
			(*i)++;
		tmp2 = get_arg(str, i, mini, 0);
		if (mini->signaldelimiters == 0)
			ft_delimiters(tmp2.value, &tmp, mini, ft_expand(str[*i - 1]));
		free(tmp2.value);
	}
	return (tmp);
}

t_token	get_redir2(int i, char *str, char c)
{
	t_token	tmp;
	t_token	tmp2;

	tmp.dollar = 0;
	tmp.type = 0;
	tmp.fd = 0;
	tmp.value = ft_malloc(sizeof(char) * 2);
	tmp.value[0] = c;
	tmp.value[1] = '\0';
	tmp.type = ft_get_redirection(tmp.value);
	return (tmp);
}

t_token	get_redir(char *str, char c, int *i, t_mini *mini)
{
	if (str[*i + 1] && (str[*i + 1] == '>' || str[*i + 1] == '<'))
		return (get_redir1(i, str, mini));
	else
		return (get_redir2((*i)++, str, c));
}

int	redirections(t_pipe pipe, int *fd_in, int *fd_out)
{
	int			i;
	int			outfile_count;

	i = -1;
	outfile_count = 0;
	while (++i < pipe.files_count && pipe.files[i].value)
	{
		if (pipe.files[i].type == TOKEN_REDIRECTION_OUTPUT
			|| pipe.files[i].type == TOKEN_REDIRECTION_DELIMTER)
			get_input(fd_in, &pipe.files[i]);
		else
		{
			outfile_count = 1;
			get_output(fd_out, &pipe.files[i]);
		}
		if (*fd_in == INVALID_FD || *fd_out == INVALID_FD)
		{
			input_error(pipe.files[i].value, NULL, -666);
			return (INVALID_FD);
		}
	}
	if (outfile_count > 0)
		return (1);
	return (0);
}
