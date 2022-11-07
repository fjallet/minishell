/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:58:38 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/29 23:58:38 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_split(char **splited)
{
	int	i;

	if (!splited)
		return (NULL);
	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		++i;
	}
	free(splited);
	return (NULL);
}

int	ft_tern(int condition, int a, int b)
{
	if (condition == 1)
		return (a);
	return (b);
}

int	fork_store(pid_t *pid_res)
{
	pid_t	pid;

	pid = fork();
	*pid_res = pid;
	if (pid == -1)
		return (-1);
	return (0);
}

int	print_stdout(int fd)
{
	if (fd > 2)
		close(fd);
	if (dup2(1, fd) == -1)
		return (-3);
	return (0);
}

int	write_fd(char *s, int fd)
{
	int	size;

	if (!s)
		return (-1);
	size = ft_strlen(s);
	write(fd, s, size);
	return (0);
}
