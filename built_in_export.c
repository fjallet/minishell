/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 09:45:38 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 17:54:20 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_clean_export(char *s, int *ret)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[0]))
	{
		*ret = 2;
		return (1);
	}
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			*ret = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

char	**first_split(char *s, char c)
{
	char	**sep;
	int		size_alpha;
	int		size_omega;

	sep = malloc(sizeof(char *) * 3);
	if (!sep)
		return (NULL);
	size_alpha = ft_strlen_c(s, c);
	size_omega = ft_strlen_c(s, '\0');
	sep[0] = ft_malloc(sizeof(char) * (size_alpha + 2));
	sep[1] = ft_malloc(sizeof(char) * (size_omega + 2));
	sep[2] = NULL;
	if (!sep[0] || !sep[1])
		return (free(sep[0]), free(sep[1]), free(sep), NULL);
	ft_strlcpy(sep[0], s, size_alpha + 1);
	sep[0][size_alpha + 1] = '\0';
	if (s[size_alpha] != c)
		return (free(sep[1]), sep[1] = NULL, sep);
	else
		ft_strlcpy(sep[1], &s[size_alpha + 1], size_omega + 1);
	return (sep);
}

void	msg_error_export(char **str)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(str[0], 2);
	if (str[1])
	{
		ft_putstr_fd("=", 2);
		ft_putstr_fd(str[1], 2);
	}
	ft_putstr("'not a valid identifier\n");
}

void	free_sep(char **sep)
{
	free(sep[0]);
	free(sep[1]);
	free(sep);
}

int	built_in_export(char **cmd, t_mini *mini, int fd_out)
{
	int		i;
	char	**sep;
	int		ret;

	i = 0;
	ret = EXIT_SUCCESS;
	while (cmd[++i])
	{
		sep = first_split(cmd[i], '=');
		if (!sep)
			return (EXIT_SUCCESS);
		if (ft_clean_export(sep[0], &ret))
			msg_error_export(sep);
		else
		{
			if (!sep[1])
				ft_setenv2(mini, sep[0], NULL, 0);
			else
				ft_setenv(mini, sep[0], sep[1], 1);
		}
		free_sep(sep);
	}
	if (i == 1)
		ft_printexport(mini, fd_out);
	return (ret);
}
