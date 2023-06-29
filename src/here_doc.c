/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:01:31 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/29 15:10:13 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int			ft_here_doc(char **argv);
static int	ft_here_doc_loop(char *line, int fd_hd, char *limiter);

int	ft_here_doc(char **argv)
{
	const char	*path = ".here_doc_temp_file";
	int			fd_hd_origin;
	int			fd_hd;
	int			loop_error_status;
	char		*line;

	fd_hd_origin = open(path, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd_hd_origin == -1)
		return (-1);
	fd_hd = dup(fd_hd_origin);
	line = NULL;
	if (fd_hd != -1)
	{
		loop_error_status = ft_here_doc_loop(line, fd_hd, argv[2]);
		close(fd_hd);
		if (loop_error_status == 0)
			fd_hd = open(path, O_RDONLY);
		else
			fd_hd = -1;
	}
	close(fd_hd_origin);
	unlink(path);
	return (fd_hd);
}

static int	ft_here_doc_loop(char *line, int fd_hd, char *limiter)
{
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (-1);
		if (ft_strncmp(line, limiter, ft_strlen(line)) == 10)
			break ;
		ft_putstr_fd(line, fd_hd);
		free(line);
	}
	if (line != NULL)
		free(line);
	return (0);
}
