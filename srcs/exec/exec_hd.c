/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:43:26 by phautena          #+#    #+#             */
/*   Updated: 2025/01/22 03:54:39 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_write(t_token *tp, int fd_in, t_data **data)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(0);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `",
				2);
			ft_putstr_fd(tp->next->value, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (tp->next->was_quote == false)
		{
			line = handle_exit_status(line, data);
			line = handle_dollar(line, data);
		}
		if (!ft_strncmp(line, tp->next->value, ft_strlen(tp->next->value)))
			break ;
		ft_putstr_fd(line, fd_in);
	}
	free(line);
}

int	init_here_doc(t_token *tp, t_data **data)
{
	int	infile;

	infile = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0)
		return (-1);
	ft_signals(1);
	here_doc_write(tp, infile, data);
	ft_signals(2);
	if (infile > 0)
		close(infile);
	infile = open("temp.txt", O_RDONLY);
	return (infile);
}
