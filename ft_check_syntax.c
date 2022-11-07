/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:17:15 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 20:34:42 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_syntax1(char *str, int *count, int *i, int *error)
{
	count[2]++;
	while (str[(*i)] && str[(*i)] != '\'')
		(*i)++;
	if (!str[(*i)])
		*error = 1;
	else
		count[2]++;
}

void	ft_syntax2(char *str, int *count, int *i, int *error)
{
	count[3]++;
	while (str[(*i)] && str[(*i)] != '\"')
		(*i)++;
	if (!str[(*i)] || str[(*i) - 1] == '\\')
		*error = 1;
	else
		count[3]++;
}

void	ft_syntax3(char *str, int *count, int *i, int *error)
{
	count[4]++;
	while (str[(*i)] && ft_whitespace(str[(*i)]))
		(*i)++;
	if (str[(*i)] && str[(*i)] == '|')
		*error = 1;
}

void	ft_syntax4(char *str, int *count, int *i, int *error)
{
	if (str[*i] && str[*i] == '\\')
		(*i)++;
	else if (str[*i] && str[*i] == '{')
		count[0]++;
	else if (str[*i] && str[*i] == '}')
		count[1]++;
	else if (str[*i] && str[*i] == '\'' && ++(*i))
		ft_syntax1(str, count, i, error);
	else if (str[*i] && str[*i] == '\"' && ++(*i))
		ft_syntax2(str, count, i, error);
	else if (str[*i] && str[*i] == '|' && ++(*i))
		ft_syntax3(str, count, i, error);
	if (str[*i])
		(*i)++;
}

int	ft_check_syntax(char *str)
{
	int	i;
	int	*count;
	int	error;

	i = 0;
	count = ft_calloc(sizeof(int), 255);
	error = 0;
	while (str[i])
		ft_syntax4(str, count, &i, &error);
	if (error)
		msg_error("Minishell : syntax error\n");
	free(count);
	return (error);
}
