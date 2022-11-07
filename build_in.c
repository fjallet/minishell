/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:49:11 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 20:30:51 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replaceenv(t_mini *mini, char *name, char *value)
{
	int	i;

	i = 0;
	while (i < (mini->env_length - 1))
	{
		if (ft_strcmp(mini->env[i].name, name) == 0)
		{
			if (mini->env[i].value)
				free(mini->env[i].value);
			if (value)
			{
				mini->env[i].value = ft_strdup(value);
				mini->env[i].init = 1;
			}
			else
			{
				mini->env[i].value = NULL;
				mini->env[i].init = 0;
			}
			break ;
		}
		i++;
	}
	update_env(mini);
}

void	ft_setenv1(t_mini *mini, int *i, t_env *env, char *value)
{
	if (value)
		env[(*i)].value = ft_strdup(value);
	else
		env[(*i)].value = NULL;
	env[++(*i)].name = NULL;
	env[(*i)].init = 1;
	env[(*i)].value = NULL;
	free(mini->env);
	mini->env = env;
	mini->env_length++;
	update_env(mini);
}

int	is_built_in(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

int	exec_built_in(char **cmd, t_mini *mini, int fd_in, int fd_out)
{
	(void) fd_in;
	if (!cmd[0])
		return (1);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (built_in_pwd(fd_out));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (built_in_cd(cmd, mini));
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (built_in_echo(cmd, fd_out));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (built_in_export(cmd, mini, fd_out));
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (built_in_env(mini, fd_out));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (built_in_exit(cmd, mini));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (built_in_unset(cmd, mini));
	return (1);
}
