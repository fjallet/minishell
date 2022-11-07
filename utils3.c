/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:09:47 by abouleau          #+#    #+#             */
/*   Updated: 2022/10/06 16:09:47 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_error(char *error_type, char	*precision, int type)
{
	write_fd("\033[1;36m", 2);
	write_fd(error_type, 2);
	write_fd(": \033[1;31m", 2);
	if (type == -666)
	{
		perror("");
		write_fd("\033[0m", 2);
	}
	else
	{
		write_fd(precision, 2);
		write_fd("\033[0m\n", 2);
	}
	return (-1);
}

void	msg_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	close_pipe(int *pipe)
{
	close(pipe[1]);
	close(pipe[0]);
}

int	ft_strlen_c(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		++i;
	return (i);
}

char	**error_args_path(t_pstat *pstat, char **paths, int *redir, int choice)
{
	if (choice == 1)
	{
		input_error("Environement", "cant find PATH", 3);
		pstat->status = 127;
		*redir = INVALID_CMD;
		return (NULL);
	}
	else
	{
		*redir = INVALID_CMD;
		pstat->status = 127;
		free_split(paths);
		return (NULL);
	}
}
