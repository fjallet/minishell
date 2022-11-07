/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 09:45:25 by abouleau          #+#    #+#             */
/*   Updated: 2022/10/01 09:45:25 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_argv(char *argv)
{
	int	j;

	if (!argv)
		return (1);
	if ((ft_strlen(argv) >= 20 && ft_strcmp(argv, "-9223372036854775808") > 0)
		|| (ft_strlen(argv) >= 19
			&& ft_strcmp(argv, "9223372036854775807") > 0))
		return (1);
	j = 0;
	while (argv[j])
	{
		if ((j == 0) && ((argv[j] > '9' || argv[j] < '0') && argv[j] != '-'))
			return (1);
		else if (j != 0 && (argv[j] > '9' || argv[j] < '0'))
			return (1);
		j++;
	}
	return (0);
}

long long	long_atoi(const char *nptr)
{
	long long	i;
	long long	total;
	long long	neg;

	i = 0;
	total = 0;
	neg = 1;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		total = total * 10 + (nptr[i] - '0');
		i++;
	}
	return (total * neg);
}

void	incr_i(char **cmd, int *i)
{
	while (cmd[*i])
		(*i)++;
}

int	built_in_exit(char **cmd, t_mini *mini)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	incr_i(cmd, &i);
	if (i > 2 && ++err)
	{
		msg_error("exit: too many arguments\n");
		if (check_argv(cmd[1]) == 0)
			return (1);
	}
	mini->print_exit = 1;
	mini->end = EXIT_SUCCESS;
	if (!cmd[1])
		return (0);
	if (check_argv(cmd[1]) == 0)
		return (long_atoi(cmd[1]));
	else
	{
		if (err == 0)
			msg_error("exit: numeric argument required\n");
		mini->end = EXIT_FAILURE;
		return (2);
	}
}
