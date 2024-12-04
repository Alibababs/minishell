/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:11:24 by phautena          #+#    #+#             */
/*   Updated: 2024/08/01 12:39:59 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
	{
		if (line != NULL)
		{
			free(line);
			line = NULL;
		}
		return (NULL);
	}
	line = get_line_fd(fd, line);
	if (gnl_strlen(line) == 0)
	{
		free(line);
		line = NULL;
		return (line);
	}
	return_line = clean_line(line);
	line = get_remainder(line);
	return (return_line);
}

char	*get_line_fd(int fd, char *line)
{
	char	*buffer;
	int		bytes_red;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	buffer[0] = '\0';
	bytes_red = 1;
	line = read_until_n(fd, line, buffer, bytes_red);
	return (line);
}

char	*read_until_n(int fd, char *line, char *buffer, int bytes_red)
{
	char	*temp;

	while (gnl_strchr(buffer, '\n') == NULL)
	{
		bytes_red = read(fd, buffer, BUFFER_SIZE);
		if (bytes_red == 0)
		{
			free(buffer);
			return (line);
		}
		buffer[bytes_red] = '\0';
		if (line == NULL)
			line = gnl_strdup("");
		temp = line;
		if (temp != NULL && buffer != NULL)
			line = gnl_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	return (line);
}

char	*clean_line(char *line)
{
	int		i;
	char	*cleaned_line;

	i = 0;
	if (line != NULL)
	{
		while (line[i] != '\n' && line[i] != '\0')
			i++;
		cleaned_line = gnl_substr(line, 0, i + 1);
		return (cleaned_line);
	}
	else
		return (NULL);
}

char	*get_remainder(char *line)
{
	int		i;
	char	*remainder_line;

	i = 0;
	if (line != NULL)
	{
		while (line[i] != '\n' && line[i] != '\0')
			i++;
		remainder_line = gnl_substr(line, i + 1, gnl_strlen(line));
		free(line);
		line = NULL;
		return (remainder_line);
	}
	else
		return (NULL);
}
