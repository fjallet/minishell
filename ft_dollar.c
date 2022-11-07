/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 02:54:19 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 20:15:44 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_str(t_helper arg, char c, int i, char *str)
{
	if (ft_getenv(arg.mini, arg.tmp))
		arg.copy = ft_strjoin(arg.tmp2, ft_getenv(arg.mini, arg.tmp));
	else
	{
		arg.change = 0;
		arg.copy = ft_strdup(arg.tmp2);
	}
	free(arg.tmp);
	free(arg.tmp2);
	arg.tmp = arg.copy;
	if (arg.str[i] == '}')
		arg.copy = ft_strjoin(arg.copy, arg.str + i + 1);
	else
		arg.copy = ft_strjoin(arg.copy, arg.str + i);
	free(arg.str);
	free(arg.tmp);
	arg.str = arg.copy;
	arg.str = ft_dollar(arg.str, c, arg.mini);
	return (arg.str);
}

void	is_brace(t_helper *arg, int j, int i)
{
	if (arg->str[i] == '}' && arg->str[j - 1] == '{')
	{
		arg->tmp = ft_strndup(arg->tmp, i - j);
		arg->tmp2 = ft_strndup(arg->str, j - 2);
	}
	else
	{
		arg->tmp = ft_strndup(arg->tmp, i - j);
		arg->tmp2 = ft_strndup(arg->str, j - 1);
	}
}

int	is_sentence(char *str, int i, int j)
{
	if (str[i] && !ft_whitespace(str[i]) && str[i] != '$'
		&& str[i] != '}' && !ft_isdigit(str[j])
		&& (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
		return (1);
	return (0);
}

char	*ft_dollar(char *str, char c, t_mini *mini)
{
	int			i;
	int			j;
	t_helper	arg;

	i = -1;
	arg.mini = mini;
	while (str[++i] && c != '\'')
	{
		if (str[i] == '$')
		{
			j = (i++) + 1;
			if (str[i] == '{')
				j = (++i);
			if (ft_isdigit(str[j]))
				i++;
			while (is_sentence(str, i, j))
				i++;
			arg.tmp = str + j;
			arg.str = str;
			is_brace(&arg, j, i);
			str = get_new_str(arg, c, i, str);
			break ;
		}
	}
	return (str);
}
