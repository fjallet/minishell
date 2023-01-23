/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:21:53 by fjallet           #+#    #+#             */
/*   Updated: 2023/01/23 16:52:48 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_delimiters(t_mini *mini, int i)
{
	static t_mini	*m;

	if (!m)
		m = mini;
	if (i >= 2)
	{
		m->exit_status = 128 + i;
		m->signal_save(i);
	}
	else if (i == -100)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		m->exit_status = 130;
	}
	else
	{
		m->exit_status = 130;
		m->signaldelimiters = i;
	}
}

void	signal_c(int sig)
{
	if (sig == SIGINT)
	{
		signal_delimiters(NULL, -100);
	}
}

void	signal_c2(int sig)
{
	(void) sig;
}

void	signal_c3(int sig)
{
	if (sig == SIGINT)
	{
		signal_delimiters(NULL, 1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		close(0);
	}
}

void	signal_c4(int sig)
{
	(void) sig;
	write(1, "\n", 1);
}
