/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:59:53 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/07 10:26:31 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec_cmd1(t_pipex *s_pipex);
static void	ft_exec_cmd2(t_pipex *s_pipex);
static void	ft_wait(t_pipex *s_pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pipex;

	errno = 0;
	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		return (0);
	}
	ft_set_pipex(&s_pipex, argc, argv, envp);
	ft_open_files(&s_pipex);
	ft_set_path(&s_pipex);
	if (pipe(s_pipex.fd) == -1)
		perror("pipe creation");
	ft_exec_cmd1(&s_pipex);
	ft_exec_cmd2(&s_pipex);
	if (s_pipex.fd_in != -1)
		close(s_pipex.fd_in);
	if (s_pipex.fd_out != -1)
		close(s_pipex.fd_out);
	if (s_pipex.fd[0] != -1)
		close(s_pipex.fd[0]);
	if (s_pipex.fd[1] != -1)
		close(s_pipex.fd[1]);
	ft_wait(&s_pipex);
	ft_quit(&s_pipex);
}

static void	ft_exec_cmd1(t_pipex *s_pipex)
{
	int	res[2];

	s_pipex->pid1 = fork();
	if (s_pipex->pid1 < 0)
	{
		perror("fork error");
		return ;
	}
	if (s_pipex->pid1 != 0)
		return ;
	close(s_pipex->fd[0]);
	close(s_pipex->fd_out);
	res[0] = dup2(s_pipex->fd_in, 0);
	res[1] = dup2(s_pipex->fd[1], 1);
	close(s_pipex->fd_in);
	close(s_pipex->fd[1]);
	if (res[0] == -1 || res[1] == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	ft_parse_args(s_pipex, s_pipex->argv[2]);
	ft_check_path_cmd(s_pipex);
	execve(s_pipex->path_cmd, s_pipex->args, s_pipex->envp);
	ft_putstr_fd("pipex: command not found: ", 2);
	if (s_pipex->args[0] != NULL)
		ft_putendl_fd(s_pipex->args[0], 2);
	exit(EXIT_FAILURE);
}

static void	ft_exec_cmd2(t_pipex *s_pipex)
{
	int	res[2];

	s_pipex->pid1 = fork();
	if (s_pipex->pid1 < 0)
	{
		perror("fork error");
		return ;
	}
	if (s_pipex->pid1 != 0)
		return ;
	close(s_pipex->fd[1]);
	close(s_pipex->fd_in);
	res[0] = dup2(s_pipex->fd[0], 0);
	res[1] = dup2(s_pipex->fd_out, 1);
	close(s_pipex->fd_out);
	close(s_pipex->fd[0]);
	if (res[0] == -1 || res[1] == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	ft_parse_args(s_pipex, s_pipex->argv[3]);
	ft_check_path_cmd(s_pipex);
	execve(s_pipex->path_cmd, s_pipex->args, s_pipex->envp);
	ft_putstr_fd("pipex: command not found: ", 2);
	if (s_pipex->args[0] != NULL)
		ft_putendl_fd(s_pipex->args[0], 2);
	exit(EXIT_FAILURE);
}

static void	ft_wait(t_pipex *s_pipex)
{
	int		wstatus;

	waitpid(s_pipex->pid1, &wstatus, 0);
	if (WIFEXITED(wstatus))
		s_pipex->exit_status = WEXITSTATUS(wstatus);
	waitpid(s_pipex->pid2, &wstatus, 0);
	if (WIFEXITED(wstatus))
		s_pipex->exit_status = WEXITSTATUS(wstatus);
	else
		s_pipex->exit_status = EXIT_FAILURE;
}
