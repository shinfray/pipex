/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:15:00 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/10 09:55:33 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void		ft_set_pipex(t_pipex *s_pipex, int argc, char **argv, char **envp);
static char	**ft_get_path(char **envp);
static void	*ft_set_backslash(char **path);

void	ft_set_pipex(t_pipex *s_pipex, int argc, char **argv, char **envp)
{
	s_pipex->argc = argc;
	s_pipex->argv = argv;
	s_pipex->envp = envp;
	s_pipex->path = ft_get_path(envp);
	s_pipex->infile = argv[1];
	s_pipex->outfile = argv[argc - 1];
	s_pipex->args = NULL;
	s_pipex->path_cmd = NULL;
	s_pipex->fd[0] = -1;
	s_pipex->fd[1] = -1;
	s_pipex->fd_in = open(s_pipex->infile, O_RDONLY);
	if (s_pipex->fd_in == -1)
		perror("pipex");
	s_pipex->fd_out = open(s_pipex->outfile, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (s_pipex->fd_out == -1)
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
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		path[i] = ft_strjoin(path[i], "/");
		if (path[i++] == NULL)
		{
			perror("ft_strjoin");
			path = ft_free_double_ptr(path);
		}
	}	
	return (path);
}
