/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:55:25 by abouleau          #+#    #+#             */
/*   Updated: 2022/09/16 23:55:25 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdio.h>
# include <string.h>

size_t	ft_strlen1(char *str);
char	*ft_strjoin1(char *s1, char *s2);
char	*ft_strchr1(char *s, int c);
char	*get_next_line(int fd);
char	*get_read(int fd, char *save);
char	*get_line(char *save);
char	*get_save(char *save);

#endif