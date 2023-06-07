/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:15:00 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/06 19:30:42 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void		ft_set_pipex(t_pipex *s_pipex, int argc, char **argv, char **envp);
void		ft_open_files(t_pipex *s_pipex);
static char	**ft_get_path(char **envp);
void	ft_set_path(t_pipex *s_pipex);

void	ft_set_pipex(t_pipex *s_pipex, int argc, char **argv, char **envp)
{
	s_pipex->exit_status = EXIT_FAILURE;
	s_pipex->argv = argv;
	s_pipex->envp = envp;
	s_pipex->path = ft_get_path(s_pipex->envp);
	s_pipex->infile = argv[1];
	s_pipex->outfile = argv[argc - 1];
	s_pipex->args = NULL;
	s_pipex->path_cmd = NULL;
	s_pipex->fd[0] = -1;
	s_pipex->fd[1] = -1;
}

void	ft_open_files(t_pipex *s_pipex)
{
	s_pipex->fd_in = open(s_pipex->infile, O_RDONLY);
	if (s_pipex->fd_in == -1)
		perror("pipex");
	s_pipex->fd_out = open(s_pipex->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (s_pipex->fd_out == -1)
		perror("pipex");
}

static char	**ft_get_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	if (envp == NULL)
		ft_putendl_fd("PATH unavailable", 2);
	path = NULL;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		++i;
	if (envp[i] == NULL)
		ft_putendl_fd("PATH unavailable", 2);
	path = ft_split(envp[i] + 5, ':');
	if (path == NULL)
		perror("split");
	return (path);
}

void	ft_set_path(t_pipex *s_pipex)
{
	int	i;

	if (s_pipex->path == NULL)
		return ;
	i = 0;
	while (s_pipex->path[i] != NULL)
	{
		s_pipex->path[i] = ft_strjoin(s_pipex->path[i], "/");
		if (s_pipex->path[i++] == NULL)
		{
			perror("ft_strjoin");
			s_pipex->path = ft_free_double_ptr(s_pipex->path);
			return ;
		}
	}	
}
