/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:11:50 by phautena          #+#    #+#             */
/*   Updated: 2024/08/01 12:39:08 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*get_line_fd(int fd, char *line);
char	*gnl_strchr(const char *s, int c);
size_t	gnl_strlen(const char *s);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strdup(const char *s);
char	*clean_line(char *line);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*get_remainder(char *line);
char	*clean_line(char *line);
char	*read_until_n(int fd, char *line, char *buffer, int bytes_red);

#endif
