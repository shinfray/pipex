/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:15:00 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/29 01:54:24 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void		ft_set_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
static char	**ft_get_path(char **envp);
static void	*ft_set_backslash(char **path);

void	ft_set_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->path = ft_get_path(envp);
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->args = NULL;
	pipex->path_cmd = NULL;
	pipex->fds = NULL;
	pipex->pipe_index = -1;
	pipex->total_pipes = pipex->argc - 4;
	pipex->total_cmds = pipex->total_pipes + 1;
	pipex->pid_last = -1;
	pipex->fd_in = open(pipex->infile, O_RDONLY);
	if (pipex->fd_in == -1)
		perror("pipex");
	pipex->fd_out = open(pipex->outfile, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
		perror("pipex");
}

static char	**ft_get_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	if (envp == NULL)
	{
		ft_putendl_fd("PATH unavailable", 2);
		return (NULL);
	}
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		++i;
	if (envp[i] == NULL)
	{
		ft_putendl_fd("PATH unavailable", 2);
		return (NULL);
	}
	path = ft_split(envp[i] + 5, ':');
	if (path == NULL)
	{
		perror("split");
		return (NULL);
	}
	path = ft_set_backslash(path);
	return (path);
}

static void	*ft_set_backslash(char **path)
{
	char	*temp;
	int		i;

	i = 0;
	while (path[i] != NULL)
	{
		temp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		if (path[i++] == NULL)
		{
			perror("ft_strjoin");
			path = ft_free_double_ptr(path);
		}
		free(temp);
	}
	return (path);
}
