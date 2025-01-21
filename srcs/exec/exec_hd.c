/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:43:26 by phautena          #+#    #+#             */
/*   Updated: 2025/01/21 17:27:22 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_write(t_token *tp, int fd_in, t_data **data)
{
	char	*line;

	ft_signals(3);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(0);
		if (!line || g_exit_status == 130)
		{
			free(line);
			break ;
		}
		if (tp->next->was_quote == false)
		{
			line = handle_exit_status(line, data);
			line = handle_dollar(line, data);
		}
		if (!ft_strncmp(line, tp->next->value, ft_strlen(tp->next->value)))
			return (free(line));
		ft_putstr_fd(line, fd_in);
		free(line);
	}
	ft_signals(1);
}

int	init_here_doc(t_token *tp, t_data **data)
{
	int	infile;

	infile = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0)
		return (-1);
	here_doc_write(tp, infile, data);
	if (infile > 0)
		close(infile);
	if (g_exit_status == 130)
	{
		unlink("temp.txt");
		return (-1);
	}
	infile = open("temp.txt", O_RDONLY);
	return (infile);
}
