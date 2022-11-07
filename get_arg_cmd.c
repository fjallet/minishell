/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:44:04 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/29 23:44:04 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_path(char **command)
{
	DIR	*dir;

	if (access(*command, F_OK) == 0)
	{
		if (access(*command, F_OK | X_OK) == 0)
		{
			dir = opendir(*command);
			if (dir)
			{
				closedir(dir);
				input_error("Is a directory", *command, 2);
				return (EXCUTE_NOT);
			}
			*command = ft_strdup2(*command);
			return (VALID_CMD);
		}
		else
		{
			input_error("Permission denied", *command, 2);
			return (EXCUTE_NOT);
		}
	}
	input_error("Invalid path", *command, 2);
	return (INVALID_CMD);
}

char	*create_path(char *path, char *filename)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, filename);
	free(tmp);
	return (full_path);
}

int	parse_cmd(char **command, char **paths)
{
	int		i;
	char	*full_path;

	if (!*command)
		return (-1);
	if (is_path(*command))
		return (process_path(command));
	if (is_built_in(*command) == 1)
		return (cmd_built_in(command));
	i = -1;
	while (paths[++i] != NULL)
	{
		full_path = create_path(paths[i], *command);
		if (!full_path)
			return (-2);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			*command = full_path;
			return (VALID_CMD);
		}
		free(full_path);
	}
	input_error("Invalid command", *command, 2);
	return (INVALID_CMD);
}

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			paths = ft_split(env[i] + 5, ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
	}
	return (NULL);
}

char	**get_args(t_pipe *pipe_a, t_mini *mini, int *redir, t_pstat *pstat)
{
	char		**paths;
	char		**args;

	args = NULL;
	paths = get_paths(mini->full_env);
	if (!paths)
		return (error_args_path(pstat, paths, redir, 1));
	args = args_cpy(pipe_a->parse_cmd, pipe_a->cmd_count);
	if (!args)
		return (error_args_path(pstat, paths, redir, 2));
	*redir = parse_cmd(&args[0], paths);
	if (*redir == INVALID_CMD || *redir == EXCUTE_NOT)
	{
		pstat->status = ft_tern(*redir == INVALID_CMD, 127, 126);
		free(args);
		free_split(paths);
		return (NULL);
	}
	free_split(paths);
	return (args);
}
