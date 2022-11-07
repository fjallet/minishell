/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:01:57 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 17:54:56 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv2(t_mini *mini, char *name, char *value, int init)
{
	int		i;
	t_env	*env;

	if (ft_hasenv(mini, name))
		return ;
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
	free_all(&mini);
	if (mini.print_exit == 1)
		printf("exit\n");
	return (mini.exit_status);
}
