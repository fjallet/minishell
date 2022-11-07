/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:53:34 by abouleau          #+#    #+#             */
/*   Updated: 2022/10/06 14:53:34 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_part(t_env *src, t_env *dst)
{
	src->name = dst->name;
	src->value = dst->value;
	src->init = dst->init;
}

void	ft_print_new_export(t_mini *mini, int fd_out, t_env *new)
{
	int	i;

	i = 0;
	while (i < (mini->env_length - 1))
	{
		ft_putstr_fd("declare -x ", fd_out);
		if (new[i].init)
		{
			ft_putstr_fd(new[i].name, fd_out);
			ft_putstr_fd("=\"", fd_out);
			ft_putstr_fd(new[i].value, fd_out);
			ft_putstr_fd("\"\n", fd_out);
		}
		else
			ft_putstr_fd(new[i].name, fd_out);
		i++;
	}
	free(new);
}

void	ft_printexport(t_mini *mini, int fd_out)
{
	int		i;
	int		j;
	t_env	*new;
	t_env	temp;

	i = 0;
	new = ft_copy_env(mini);
	while (i < (mini->env_length - 1))
	{
		j = 0;
		while (j < (mini->env_length - 1))
		{
			if (new[j + 1].name && ft_strcmp(new[j].name, new[j + 1].name) > 0)
			{
				ft_copy_part(&temp, &new[j]);
				ft_copy_part(&new[j], &new[j + 1]);
				ft_copy_part(&new[j + 1], &temp);
			}
			j++;
		}
		i++;
	}
	ft_print_new_export(mini, fd_out, new);
}
