/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:09:41 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/28 01:09:41 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_full_env(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->full_env[i])
	{
		free(mini->full_env[i]);
		i++;
	}
	free(mini->full_env);
}

void	update_env(t_mini *mini)
{
	static int	first = 1;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (mini->env[i].name)
	{
		if (mini->env[i].init)
			j++;
		i++;
	}
	if (first == 0)
		free_full_env(mini);
	first = 0;
	mini->full_env = ft_malloc(sizeof(char *) * (j + 1));
	copy_env(mini);
}

void	dup_env(char **env, t_mini *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i])
		i++;
	mini->env = ft_malloc(sizeof(t_env) * (i + 1));
	mini->env_length = (i + 1);
	i = -1;
	while (env[++i])
	{
		temp = ft_strchr(env[i], '=');
		mini->env[i].name = ft_strndup(env[i], temp - env[i]);
		mini->env[i].value = ft_strdup(temp + 1);
		mini->env[i].init = 1;
	}
	mini->env[i].name = NULL;
	mini->env[i].value = NULL;
	mini->env[i].init = 0;
	mini->full_env = env;
	update_env(mini);
}

int	ft_hasenv(t_mini *mini, char *name)
{
	int	i;

	i = 0;
	while (i < (mini->env_length - 1))
	{
		if (ft_strcmp(mini->env[i].name, name) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_setenv(t_mini *mini, char *name, char *value, int init)
{
	int		i;
	t_env	*env;

	if (ft_hasenv(mini, name))
	{
		ft_replaceenv(mini, name, value);
		return ;
	}
	env = ft_malloc(sizeof(t_env) * (mini->env_length + 1));
	i = 0;
	while (i < (mini->env_length - 1))
	{
		env[i].name = mini->env[i].name;
		env[i].value = mini->env[i].value;
		env[i].init = mini->env[i].init;
		i++;
	}
	env[i].name = ft_strdup(name);
	env[i].init = init;
	ft_setenv1(mini, &i, env, value);
}
