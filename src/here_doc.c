/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:01:31 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/03 00:57:15 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int			ft_here_doc(char **argv);
static void	ft_fill_in_here_doc_file(int fd_hd, char *limiter);
static char	*ft_here_doc_get_next_line(char *line);

int	ft_here_doc(char **argv)
{
	const char	*path = ".here_doc_temp_file";
	int			fd_hd_origin;
	int			fd_hd;

	fd_hd_origin = open(path, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd_hd_origin == -1)
		return (-1);
	fd_hd = dup(fd_hd_origin);
	if (fd_hd != -1)
	{
		ft_fill_in_here_doc_file(fd_hd, argv[2]);
		close(fd_hd);
		fd_hd = open(path, O_RDONLY);
	}
	close(fd_hd_origin);
	unlink(path);
	return (fd_hd);
}

static void	ft_fill_in_here_doc_file(int fd_hd, char *limiter)
{
	char	*line;

	while (1)
	{
		line = NULL;
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = ft_here_doc_get_next_line(line);
		if (ft_strncmp(line, limiter, ft_strlen(line)) == ('\n' - '\0'))
			break ;
		ft_putstr_fd(line, fd_hd);
		free(line);
	}
	free(line);
}

static char	*ft_here_doc_get_next_line(char *line)
{
	char	*buff;
	char	*temp;

	while (line == NULL || line[ft_strlen(line) - 1] != '\n')
	{
		buff = NULL;
		while (buff == NULL)
			buff = get_next_line(STDIN_FILENO);
		if (line == NULL)
			line = ft_strdup(buff);
		else
		{
			temp = line;
			line = ft_strjoin(line, buff);
			free(temp);
		}
		free(buff);
	}
	return (line);
}
