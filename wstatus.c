/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstatus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:47:07 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/27 17:09:44 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen1(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = (char *) malloc ((ft_strlen1(s1)
				+ ft_strlen1(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen1(s1) + ft_strlen1(s2)] = '\0';
	free(s1);
	return (str);
}

int	create_pipes_status(t_pstat **pipe_status, t_mini *mini, int pipe_size)
{
	int			i;

	*pipe_status = malloc(sizeof(t_pstat) * pipe_size);
	if (!*pipe_status)
	{
		mini->exit_status = 1;
		return (0);
	}
	i = -1;
	while (++i < pipe_size)
	{
		(*pipe_status)[i].pid = 0;
		(*pipe_status)[i].status = 0;
	}
	return (1);
}

int	wait_all_pid(t_pstat *pipe_status, int size)
{
	int	i;
	int	status;

	i = 0;
	if (!pipe_status)
		return (1);
	while (i < size)
	{
		if (&pipe_status[i] != NULL && pipe_status[i].pid > 0)
		{
			waitpid(pipe_status[i].pid, &status, 0);
			if (WIFEXITED(status))
				pipe_status[i].status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				pipe_status[i].status = 128 + WTERMSIG(status);
			else if (WIFSTOPPED(status))
				pipe_status[i].status = 128 + WSTOPSIG(status);
			else if (WIFCONTINUED(status))
				pipe_status[i].status = 128 + WIFCONTINUED(status);
		}
		++i;
	}
	return (1);
}

void	check_exit_status(t_mini *mini, char *line)
{
	if (line == NULL || mini->print_exit == 1)
		printf("exit\n");
	else if (mini->check_mini == 1)
		mini->check_mini = 0;
	else if (mini->exit_status == 131)
		printf("Quit (core dumped)\n");
	else if (mini->exit_status == 130)
		printf("\n");
}
