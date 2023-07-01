/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:01:31 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/01 19:42:38 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int			ft_here_doc(char **argv);
static void	ft_here_doc_loop(char *line, int fd_hd, char *limiter);

int	ft_here_doc(char **argv)
{
	const char	*path = ".here_doc_temp_file";
	int			fd_hd_origin;
	int			fd_hd;
	char		*line;

	fd_hd_origin = open(path, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd_hd_origin == -1)
		return (-1);
	fd_hd = dup(fd_hd_origin);
	line = NULL;
	if (fd_hd != -1)
	{
		ft_here_doc_loop(line, fd_hd, argv[2]);
		close(fd_hd);
		fd_hd = open(path, O_RDONLY);
	}
	close(fd_hd_origin);
	unlink(path);
	return (fd_hd);
}

static void	ft_here_doc_loop(char *line, int fd_hd, char *limiter)
{
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	while (1)
	{
		if (line != NULL)
			free(line);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			continue ;
		if (ft_strncmp(line, limiter, ft_strlen(line)) == ('\n' - '\0'))
			break ;
		ft_putstr_fd(line, fd_hd);
		if (line[ft_strlen(line) - 1] == '\n')
			ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	}
	free(line);
}
