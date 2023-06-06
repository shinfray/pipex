/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:59:53 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/06 19:39:00 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec_cmd1(t_pipex *s_pipex);
static void	ft_exec_cmd2(t_pipex *s_pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pipex;

	errno = 0;
	if (argc != 5)
		return (0);
	ft_set_pipex(&s_pipex, argc, argv, envp);
	ft_open_files(&s_pipex);
	ft_parse_args(&s_pipex);
	ft_set_path(&s_pipex);
	ft_check_path_cmd2(&s_pipex);
	ft_check_path_cmd2(&s_pipex);
	if (pipe(s_pipex.fd) == -1)
		ft_quit(&s_pipex);
	ft_exec_cmd1(&s_pipex);
	ft_exec_cmd2(&s_pipex);
	waitpid(s_pipex.pid1, NULL, 0);
	waitpid(s_pipex.pid2, NULL, 0);
	s_pipex.exit_status = EXIT_SUCCESS;
	ft_quit(&s_pipex);
	return (0);
}

static void	ft_exec_cmd1(t_pipex *s_pipex)
{
	if (dup2(s_pipex->fd[1], 1) == -1)
		ft_quit(s_pipex);
	close(s_pipex->fd[1]);
	s_pipex->pid1 = fork();
	if (s_pipex->pid1 < 0)
		ft_quit(s_pipex);
	if (s_pipex->pid1 == 0)
	{
		close(s_pipex->fd[0]);
		execve(s_pipex->path_cmd1, s_pipex->args_1, s_pipex->envp);
		exit(EXIT_FAILURE);
	}
}

static void	ft_exec_cmd2(t_pipex *s_pipex)
{
	s_pipex->fd_out = open(s_pipex->outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (s_pipex->fd_out == -1)
		ft_quit(s_pipex);
	if (dup2(s_pipex->fd[0], 0) == -1)
		ft_quit(s_pipex);
	if (dup2(s_pipex->fd_out, 1) == -1)
		ft_quit(s_pipex);
	close(s_pipex->fd[0]);
	close(s_pipex->fd_out);
	s_pipex->pid2 = fork();
	if (s_pipex->pid2 < 0)
		ft_quit(s_pipex);
	if (s_pipex->pid2 == 0)
	{
		execve(s_pipex->path_cmd2, s_pipex->args_2, s_pipex->envp);
		exit(EXIT_FAILURE);
	}
}
