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

void	ft_set_pipex(t_pipex *s_pipex, int argc, char **argv, char **envp)
{
	s_pipex->exit_status = EXIT_FAILURE;
	s_pipex->argv = argv;
	s_pipex->envp = envp;
	s_pipex->path = ft_get_path(s_pipex->envp);
	s_pipex->infile = argv[1];
	s_pipex->outfile = argv[argc - 1];
	s_pipex->args_1 = NULL;
	s_pipex->args_2 = NULL;
	s_pipex->path_cmd1 = NULL;
	s_pipex->path_cmd2 = NULL;
	s_pipex->fd[0] = -1;
	s_pipex->fd[1] = -1;
	s_pipex->fd_out = -1;
	s_pipex->fd_in = -1;
}

void	ft_open_files(t_pipex *s_pipex)
{
	if (access(s_pipex->infile, F_OK | R_OK) != 0)
	{
		perror("pipex");
	}
	else
		s_pipex->fd_in = open(s_pipex->infile, O_RDONLY);
	if (s_pipex->fd_in == -1)
		ft_quit(s_pipex);
	if (dup2(s_pipex->fd_in, 0) != -1)
	{
		close(s_pipex->fd_in);
		return ;
	}
	close(s_pipex->fd_in);
	ft_quit(s_pipex);
}

static char	**ft_get_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	if (envp == NULL)
	{
		ft_putendl_fd("PATH unavailable", 2);
		exit(EXIT_FAILURE);
	}
	path = NULL;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
	{
		ft_putendl_fd("PATH unavailable", 2);
		exit(EXIT_FAILURE);
	}
	path = ft_split(envp[i] + 5, ':');
	if (path == NULL)
	{
		perror("split");
		exit(EXIT_FAILURE);
	}
	return (path);
}
