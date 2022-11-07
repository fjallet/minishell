/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 00:14:28 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/30 00:14:28 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	get_pipe(char *str, char c, int *i)
{
	t_token	token;

	token.dollar = 0;
	token.type = 0;
	if (str[*i + 1] && (c == str[*i + 1]))
	{
		token.value = ft_strndup(str + *i, 2);
		token.type = TOKEN_ERROR;
		*i = *i + 2;
	}
	else
	{
		token.value = ft_malloc(sizeof(char) * 2);
		token.value[0] = c;
		token.value[1] = '\0';
		token.type = TOKEN_PIPE;
		(*i)++;
	}
	return (token);
}

void	get_quote(char *str, int *i, t_token *token, t_helper h)
{
	char	*tmp;
	char	*tmp2;
	char	c;

	c = str[*i];
	(*i)++;
	token->type = TOKEN_ARGUMENT;
	tmp = ft_calloc(sizeof(char), 1);
	tmp2 = ft_calloc(sizeof(char), 2);
	while (str[*i] && str[*i] != c)
	{
		if (str[*i] == '\\' && str[(*i + 1)] != c)
			(*i)++;
		tmp2[0] = str[*i];
		tmp = ft_strjoin1(tmp, tmp2);
		(*i)++;
	}
	free(tmp2);
	tmp = ft_dollar(tmp, c, h.mini);
	token->value = ft_strjoin1(token->value, tmp);
	free(tmp);
	return ;
}

t_token	get_redirec_arg(int *i, char *str, t_helper save, t_token token)
{
	t_token	tmp;

	if (ft_strlen(token.value) < 1)
	{
		tmp = get_redir(str, str[*i], i, save.mini);
		free(token.value);
		free(save.tmp);
		return (tmp);
	}
	free(save.tmp);
	return (token);
}

t_token	get_pipe_arg(int *i, char *str, t_helper save, t_token token)
{
	t_token	tmp;

	if (ft_strlen(token.value) < 1)
	{
		tmp = get_pipe(str, str[*i], i);
		free(token.value);
		free(save.tmp);
		return (tmp);
	}
	free(save.tmp);
	return (token);
}

t_token	get_arg(char *str, int *i, t_mini *mini, int choice)
{
	t_token		tmp;
	t_helper	save;

	ft_set_base(&tmp, &save, mini);
	while (str[*i] && !ft_whitespace(str[*i]))
	{
		if ((str[*i] == '\'' || str[*i] == '\"') && !choice)
			get_quote(str, i, &tmp, save);
		else
		{
			if (str[*i] == '\\')
				(*i)++;
			else if (str[*i] == '<' || str[*i] == '>')
				return (get_redirec_arg(i, str, save, tmp));
			else if (str[*i] == '|')
				return (get_pipe_arg(i, str, save, tmp));
			else if (str[*i] == '$')
				tmp.dollar = 1;
			save.tmp[0] = str[*i];
			get_type_value(&tmp, &save);
		}
		get_i_incr(str, i);
	}
	free(save.tmp);
	return (tmp);
}
