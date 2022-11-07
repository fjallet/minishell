/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 09:45:55 by abouleau          #+#    #+#             */
/*   Updated: 2022/10/01 09:45:55 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_mini *mini, char *ph)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_setenv(mini, "OLDPWD", ft_getenv(mini, "PWD"), 1);
		ft_setenv(mini, "PWD", ph, 1);
	}
}

void	free_pwd(char *str, int full)
{
	if (full)
		free(str);
}

int	error_cd(char *ph, int full, int choice)
{
	if (choice == 1)
	{
		free_pwd(ph, full);
		write(1, "cd : too many arguments\n", 24);
		return (2);
	}
	else
	{
		msg_error("cd : Environement unvailable\n");
		return (2);
	}
}

int	built_in_cd(char **cmd, t_mini *mini)
{
	char	*base;
	char	*ph;
	int		full;

	full = 0;
	base = ft_getenv(mini, "HOME");
	ph = cmd[1];
	if (!ph || ft_strlen(ph) == 0)
		ph = base;
	else if (ft_strncmp(ph, "~", 1) == 0 && base && ++full)
		ph = ft_strdup(base);
	if (cmd[1] && cmd[2])
		return (error_cd(ph, full, 1));
	if (!ph || ft_strlen(ph) == 0 || !ft_getenv(mini, "PWD"))
		return (error_cd(ph, full, 0));
	else if (chdir(ph) == -1)
	{
		perror("cd");
		return (2);
	}
	else
		update_pwd(mini, ph);
	free_pwd(ph, full);
	return (EXIT_SUCCESS);
}
