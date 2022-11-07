/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:52:46 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/29 23:52:46 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup2(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**args_cpy(char **cmd, int size)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = cmd[i];
		++i;
	}
	res[i] = NULL;
	return (res);
}

void	*ft_malloc(size_t nb)
{
	void	*ret;

	ret = malloc(nb);
	if (ret)
		return (ret);
	else
	{
		msg_error("Malloc error\n");
		exit(EXIT_FAILURE);
	}
	return (NULL);
}

int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\r' || c == '\t'
		|| c == '\f' || c == '\n' || c == '\v')
		return (1);
	return (0);
}

int	is_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		++i;
	}
	return (0);
}
