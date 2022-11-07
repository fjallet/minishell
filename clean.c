/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:20:41 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 12:27:42 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(t_mini *mini)
{
	if (mini->exit_char)
	{
		free(mini->exit_char);
		mini->exit_char = NULL;
	}
}

void	free_pipe(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->pipe_length)
	{
		free(mini->pipe[i].cmd);
		free (mini->pipe[i].files);
		free(mini->pipe[i].parse_cmd);
		i++;
	}
	free(mini->pipe);
}

void	free_cmd(t_token *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i].value)
		free(cmd[i].value);
	free(cmd[i].value);
	free(cmd);
}

void	free_env(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < (mini->env_length - 1))
	{
		free(mini->env[i].value);
		free(mini->env[i].name);
		i++;
	}
	free(mini->env);
}

void	free_all(t_mini *mini)
{
	rl_clear_history();
	free_env(mini);
	free_full_env(mini);
	free_exit(mini);
}
