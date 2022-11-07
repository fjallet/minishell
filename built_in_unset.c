/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 09:45:29 by abouleau          #+#    #+#             */
/*   Updated: 2022/10/01 09:45:29 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_env1(t_mini *mini, int *j, t_env *env, int temp)
{
	free(mini->env[temp].name);
	free(mini->env[temp].value);
	env[(*j)].name = NULL;
	env[(*j)].init = 1;
	env[(*j)++].value = NULL;
	free(mini->env);
	mini->env = env;
	mini->env_length--;
	update_env(mini);
}

void	ft_delete_env(t_mini *mini, char *name)
{
	int		i;
	int		j;
	t_env	*env;
	int		temp;

	if (!ft_hasenv(mini, name))
		return ;
	env = ft_malloc(sizeof(t_env) * (mini->env_length));
	i = 0;
	j = 0;
	while (i < (mini->env_length - 1))
	{
		if (ft_strcmp(mini->env[i].name, name) != 0)
		{
			env[j].name = mini->env[i].name;
			env[j].value = mini->env[i].value;
			env[j].init = mini->env[i].init;
			j++;
		}
		else
			temp = i;
		i++;
	}
	ft_delete_env1(mini, &j, env, temp);
}

int	built_in_unset(char **cmd, t_mini *mini)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_delete_env(mini, cmd[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
