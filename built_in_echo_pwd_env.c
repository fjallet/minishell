/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo_pwd_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 09:45:50 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 20:32:04 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_arg(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == 'n')
			n = 1;
		if (str[i] != 'n')
			return (0);
		i++;
	}
	if (n == 0)
		return (0);
	return (1);
}

int	built_in_echo(char **cmd, int fd_out)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd[i] && ft_check_arg(cmd[i]) == 1)
	{
		n = 1;
		i++;
		if (!cmd[i])
			return (EXIT_SUCCESS);
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd_out);
		i++;
		if (cmd[i] && ft_strlen(cmd[i - 1]) > 0)
			write(fd_out, " ", 1);
	}
	if (n == 0)
		write(fd_out, "\n", 1);
	return (EXIT_SUCCESS);
}

int	built_in_pwd(int fd_out)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, fd_out);
		ft_putstr_fd("\n", fd_out);
		return (EXIT_SUCCESS);
	}
	else
		perror("pwd\n");
	return (EXIT_FAILURE);
}

int	built_in_env(t_mini *mini, int fd_out)
{
	int	i;

	i = 0;
	while (i < (mini->env_length - 1))
	{
		if (mini->env[i].init)
		{
			ft_putstr_fd(mini->env[i].name, fd_out);
			ft_putstr_fd("=", fd_out);
			ft_putstr_fd(mini->env[i].value, fd_out);
			ft_putstr_fd("\n", fd_out);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
