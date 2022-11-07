/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:02:27 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 14:03:08 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delimiters2(t_helper *save, char *s, int expand)
{
	save->temp = NULL;
	free(save->line);
	save->line = readline("\e[0;35m>\e[0;37m ");
	if (save->line && ft_strcmp(save->line, s) != 0)
	{
		if (!expand)
			save->line = ft_dollar(save->line, '"', save->mini);
		save->temp = save->ret;
		save->ret = ft_strjoin(save->ret, save->line);
		free(save->temp);
		save->temp = save->ret;
		save->ret = ft_strjoin(save->ret, "\n");
		free(save->temp);
	}
}

void	ft_delimiters1(char *ret, char *s, int *pipes, t_token *token)
{
	write(pipes[1], ret, ft_strlen(ret));
	close(pipes[1]);
	token->fd = pipes[0];
	free(token->value);
	token->value = ft_strdup(s);
	free(ret);
}

void	ft_delimiters(char *s, t_token *token, t_mini *mini, int expand)
{
	t_helper	save;
	int			pipes[2];

	if (pipe(pipes) == -1)
	{
		perror("pipe");
		return ;
	}
	save.ret = ft_calloc(sizeof(char), 1);
	save.line = ft_calloc(sizeof(char), 1);
	save.mini = mini;
	signal(SIGINT, signal_c3);
	mini->dup_fd = dup(0);
	save.start = 1;
	while (save.start || (save.line && ft_strcmp(save.line, s) != 0
			&& mini->signaldelimiters == 0))
	{
		save.start = 0;
		ft_delimiters2(&save, s, expand);
	}
	if (mini->signaldelimiters)
		return ;
	if (save.line)
		free(save.line);
	ft_delimiters1(save.ret, s, pipes, token);
}
