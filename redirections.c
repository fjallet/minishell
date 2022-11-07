/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:48:21 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/29 23:48:21 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_output(char *outfile, int append)
{
	int		fd_outfile;
	int		readed;
	char	buffer[1023];

	if (!outfile)
		return (input_error("parse error near '\\n'", NULL, 0));
	fd_outfile = open(outfile, O_RDWR | O_CREAT, S_IRWXU);
	if (fd_outfile == INVALID_FD)
		return (INVALID_FD);
	if (append == 0)
	{
		close(fd_outfile);
		unlink(outfile);
		fd_outfile = open(outfile, O_RDWR | O_CREAT, S_IRWXU);
		if (fd_outfile == INVALID_FD)
			return (INVALID_FD);
	}
	else
	{
		readed = 1023;
		while (readed == 1023)
			readed = read(fd_outfile, buffer, 1023);
	}
	return (fd_outfile);
}

void	get_input(int *input_fd, t_token *file)
{
	if (*input_fd > 2)
		close(*input_fd);
	if (file->type == TOKEN_REDIRECTION_OUTPUT)
		*input_fd = open(file->value, O_RDONLY);
	else if (file->type == TOKEN_REDIRECTION_DELIMTER)
	{
		*input_fd = file->fd;
	}
}

void	get_output(int *output_fd, t_token *file)
{
	if (*output_fd != 1)
		close(*output_fd);
	*output_fd = open_output(file->value,
			ft_tern(file->type == TOKEN_REDIRECTION_INPUT, 0, 1));
}

int	get_fds(t_pipe pipe, int *input_fd, int *output_fd, t_pstat *pstat)
{
	int			i;
	int			outfile_count;

	i = -1;
	outfile_count = 0;
	while (++i < pipe.files_count && pipe.files[i].value)
	{
		if (pipe.files[i].type == TOKEN_REDIRECTION_OUTPUT
			|| pipe.files[i].type == TOKEN_REDIRECTION_DELIMTER)
			get_input(input_fd, &pipe.files[i]);
		else
		{
			outfile_count = 1;
			get_output(output_fd, &pipe.files[i]);
		}
		if (*input_fd == INVALID_FD || *output_fd == INVALID_FD)
		{
			input_error(pipe.files[i].value, NULL, -666);
			pstat->status = 1;
			return (INVALID_FD);
		}
	}
	if (outfile_count > 0)
		return (1);
	return (0);
}

int	get_fd(t_pipe pipe, int *input_fd, int *output_fd)
{
	int	i;
	int	outfile_count;

	i = -1;
	outfile_count = 0;
	while (++i < pipe.files_count && pipe.files[i].value)
	{
		if (pipe.files[i].type == TOKEN_REDIRECTION_OUTPUT
			|| pipe.files[i].type == TOKEN_REDIRECTION_DELIMTER)
			get_input(input_fd, &pipe.files[i]);
		else
		{
			outfile_count = 1;
			get_output(output_fd, &pipe.files[i]);
		}
		if (*input_fd == INVALID_FD || *output_fd == INVALID_FD)
		{
			input_error(pipe.files[i].value, NULL, -666);
			return (INVALID_FD);
		}
	}
	if (outfile_count > 0)
		return (1);
	return (0);
}
