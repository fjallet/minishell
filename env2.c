/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:57:26 by abouleau          #+#    #+#             */
/*   Updated: 2022/10/06 14:57:26 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(t_mini *mini)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (mini->env[i].name)
	{
		if (mini->env[i].init)
		{
			temp = ft_strjoin(mini->env[i].name, "=");
			mini->full_env[j++] = ft_strjoin(temp, mini->env[i].value);
			free(temp);
		}
		i++;
	}
	mini->full_env[j++] = NULL;
}

t_env	*ft_copy_env(t_mini *mini)
{
	t_env	*new;
	int		i;

	new = ft_malloc(sizeof(t_env) * (mini->env_length));
	i = 0;
	while (i < (mini->env_length - 1))
	{
		new[i].name = mini->env[i].name;
		new[i].value = mini->env[i].value;
		new[i].init = mini->env[i].init;
		i++;
	}
	new[i].name = NULL;
	new[i].value = NULL;
	new[i].init = 0;
	return (new);
}

char	*ft_exit_satus(int n, t_mini *mini)
{
	int		nb;
	int		i;

	nb = n;
	i = 0;
	while (n >= 10)
	{
		i++;
		n = n / 10;
	}
	i++;
	ft_bzero(mini->exit_char, 4);
	mini->exit_char[i] = '\0';
	n = nb;
	while (n >= 10)
	{
		mini->exit_char[--i] = ((n % 10) + '0');
		n = n / 10;
	}
	mini->exit_char[--i] = ((n % 10) + '0');
	return (mini->exit_char);
}

char	*ft_getenv(t_mini *mini, char *name)
{
	int	i;

	i = 0;
	if (ft_strcmp("?", name) == 0)
		return (ft_exit_satus(mini->exit_status, mini));
	while (i < (mini->env_length - 1))
	{
		if (ft_strcmp(mini->env[i].name, name) == 0)
			return (mini->env[i].value);
		i++;
	}
	return (NULL);
}
