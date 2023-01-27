/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjallet <fjallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:20:38 by abouleau          #+#    #+#             */
/*   Updated: 2023/01/27 18:14:25 by fjallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_pipe2(t_pstat *pipe_status)
{
	free(pipe_status);
	return (-1);
}

int	free_args2(t_pstat *pstat, char **args, int choice)
{
	if (choice == 1)
	{
		free(args[0]);
		free(args);
		input_error("?", "!", 0);
		pstat->status = 12;
		return (-4);
	}
	else if (choice == 2)
	{
		free(args[0]);
		free(args);
		return (0);
	}
	return (0);
}
