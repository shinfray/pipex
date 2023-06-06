/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:59:53 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/06 17:28:45 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parse_args(t_pipex *s_pipex);
void	ft_open_files(t_pipex *s_pipex);
void	ft_set_path(t_pipex *s_pipex);
void	ft_check_path_cmd(t_pipex *s_pipex);
void	ft_exec(t_pipex *s_pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pipex;

	errno = 0;
	if (argc != 5)
		return (0);
	s_pipex.argv = argv;
	s_pipex.envp = envp;
	s_pipex.path = ft_get_path(envp);
	s_pipex.infile = argv[1];
	s_pipex.outfile = argv[argc - 1];
	s_pipex.args_1 = NULL;
	s_pipex.args_2 = NULL;
	s_pipex.path_cmd1 = NULL;
	s_pipex.path_cmd2 = NULL;
	ft_open_files(&s_pipex);
	ft_parse_args(&s_pipex);
	ft_set_path(&s_pipex);
	ft_check_path_cmd(&s_pipex);
	if (pipe(s_pipex.fd) == -1)
		ft_quit(&s_pipex);
	ft_exec(&s_pipex);


	return (0);
}

void	ft_open_files(t_pipex *s_pipex)
{
	if (access(s_pipex->infile, F_OK | R_OK) != 0)
		ft_quit(s_pipex);
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

void	ft_parse_args(t_pipex *s_pipex)
{
	s_pipex->args_1 = ft_split(s_pipex->argv[2], ' ');
	s_pipex->args_2 = ft_split(s_pipex->argv[3], ' ');
	if (s_pipex->args_1 == NULL || s_pipex->args_2 == NULL)
		ft_quit(s_pipex);
}

void	ft_set_path(t_pipex *s_pipex)
{
	int	i;

	i = 0;
	while (s_pipex->path[i] != NULL)
	{
		s_pipex->path[i] = ft_strjoin(s_pipex->path[i], "/");
		if (s_pipex->path[i] == NULL)
			ft_quit(s_pipex);
		++i;
	}	
}

void	ft_check_path_cmd(t_pipex *s_pipex)
{
	int	i;

	i = 0;
	s_pipex->path_cmd1 = ft_strjoin(s_pipex->path[i], s_pipex->args_1[0]);
	if (s_pipex->path_cmd1 == NULL)
		ft_quit(s_pipex);
	while (access(s_pipex->path_cmd1, F_OK | X_OK) != 0)
	{
		++i;
		free(s_pipex->path_cmd1);
		s_pipex->path_cmd1 = ft_strjoin(s_pipex->path[i], s_pipex->args_1[0]);
		if (s_pipex->path_cmd1 == NULL)
			ft_quit(s_pipex);
	}
	i = 0;
	s_pipex->path_cmd2 = ft_strjoin(s_pipex->path[i], s_pipex->args_2[0]);
	if (s_pipex->path_cmd2 == NULL)
		ft_quit(s_pipex);
	while (access(s_pipex->path_cmd2, F_OK | X_OK) != 0)
	{
		++i;
		free(s_pipex->path_cmd2);
		s_pipex->path_cmd2 = ft_strjoin(s_pipex->path[i], s_pipex->args_2[0]);
		if (s_pipex->path_cmd2 == NULL)
		ft_quit(s_pipex);
	}
}

void	ft_exec(t_pipex *s_pipex)
{
	s_pipex->pid1 = fork();
	if (s_pipex->pid1 < 0)
		ft_quit(s_pipex);
	if (s_pipex->pid1 == 0)
	{
		dup2(s_pipex->fd[1], 1);
		close(s_pipex->fd[0]);
		close(s_pipex->fd[1]);
		execve(s_pipex->path_cmd1, s_pipex->args_1, s_pipex->envp);
	}
	s_pipex->fd_out = open(s_pipex->outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (s_pipex->fd_out == -1)
		return ;
	s_pipex->pid2 = fork();
	if (s_pipex->pid2 < 0)
		return ;
	if (s_pipex->pid2 == 0)
	{
		dup2(s_pipex->fd[0], 0);
		dup2(s_pipex->fd_out, 1);
		close(s_pipex->fd[0]);
		close(s_pipex->fd[1]);
		close(s_pipex->fd_out);
		execve(s_pipex->path_cmd2, s_pipex->args_2, s_pipex->envp);
	}
	close(s_pipex->fd[0]);
	close(s_pipex->fd[1]);
	waitpid(s_pipex->pid1, NULL, 0);
	waitpid(s_pipex->pid2, NULL, 0);
}