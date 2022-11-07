/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:20:38 by abouleau          #+#    #+#             */
/*   Updated: 2022/11/07 13:40:01 by abouleau         ###   ########.fr       */
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
		pstat->status = 1;
		return (-4);
	}
	else if (choice == 2)
	{
		free(args[0]);
		free(args);
		return (0);
	}
}
