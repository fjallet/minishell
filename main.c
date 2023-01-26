/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:01:57 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/26 13:49:13 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signal(t_mini *mini)
{
	mini->signal_save = signal(SIGINT, signal_c);
	mini->signal_c = signal_c;
	mini->signal_c2 = signal_c2;
	mini->signal_c4 = signal_c4;
	signal(SIGQUIT, signal_c2);
	signal_delimiters(mini, 0);
}

void	ft_init_mini(t_mini *mini, char **envp)
{
	mini->end = -1;
	mini->print_exit = 0;
	mini->exit_status = 0;
	mini->exit_char = ft_malloc(sizeof(char) * 4);
	dup_env(envp, mini);
}

int	main(int ac, char **av, char **envp)
{
	t_mini				mini;
	char				*line;
	t_token				*cmd;

	if (ac == 0 || !av[0])
		return (0);
	ft_init_mini(&mini, envp);
	setup_signal(&mini);
	line = NULL;
	cmd = NULL;
	if (isatty(0))
		line = readline("\e[0;35mMini\e[0;33mshell $>\e[0;37m ");
	while (line && mini.end == -1 && isatty(0))
		minishell(&line, &mini, cmd);
	check_exit_status(&mini, line);
	free_all(&mini);
	return (mini.exit_status);
}
