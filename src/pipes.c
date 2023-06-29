/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 01:21:45 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/29 11:05:42 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_create_pipes(t_pipex *pipex);
void	ft_close_pipes(t_pipex *pipex);

void	ft_create_pipes(t_pipex *pipex)
{
	int	i;

	pipex->fds = ft_calloc(pipex->total_pipes * 2, sizeof(*pipex->fds));
	if (pipex->fds == NULL)
	{
		perror("Error pipe creation");
		ft_close(2, pipex->fd_in, pipex->fd_out);
		ft_quit(pipex);
	}
	i = 0;
	while (i < pipex->total_pipes * 2)
		pipex->fds[i++] = -1;
	i = -1;
	while (++i < pipex->total_pipes)
		if (pipe(pipex->fds + (i * 2)) == -1)
			perror("Error pipe creation");
}

void	ft_close_pipes(t_pipex *pipex)
{
	const int	fds = pipex->total_pipes * 2;
	int			i;

	i = 0;
	while (i < fds)
		close(pipex->fds[i++]);
	ft_close(2, pipex->fd_in, pipex->fd_out);
}
