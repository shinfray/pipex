/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:04:14 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/10 13:18:07 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec_first_cmd(t_pipex *s_pipex);
static void	ft_exec_last_cmd(t_pipex *s_pipex);
static void	ft_wait(t_pipex *s_pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pipex;

	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		return (EXIT_FAILURE);
	}
	ft_set_pipex(&s_pipex, argc, argv, envp);
	if (pipe(s_pipex.fd) == -1)
		perror("pipe creation");
	ft_exec_first_cmd(&s_pipex);
	ft_exec_last_cmd(&s_pipex);
	ft_close(4, s_pipex.fd_in, s_pipex.fd_out, s_pipex.fd[0], s_pipex.fd[1]);
	ft_wait(&s_pipex);
	ft_quit(&s_pipex);
}

static void	ft_exec_first_cmd(t_pipex *s_pipex)
{
	int	res[2];

	s_pipex->pid_first = fork();
	if (s_pipex->pid_first < 0)
	{
		s_pipex->exit_status = EXIT_FAILURE;
		return (perror("fork error"));
	}
	if (s_pipex->pid_first != 0)
		return ;
	res[0] = dup2(s_pipex->fd_in, STDIN_FILENO);
	res[1] = dup2(s_pipex->fd[1], STDOUT_FILENO);
	ft_close(4, s_pipex->fd_in, s_pipex->fd_out, \
		s_pipex->fd[0], s_pipex->fd[1]);
	if (res[0] == -1 || res[1] == -1)
	{
		s_pipex->exit_status = EXIT_FAILURE;
		ft_quit(s_pipex);
	}
	ft_parse_args(s_pipex, s_pipex->argv[2]);
	execve(s_pipex->path_cmd, s_pipex->args, s_pipex->envp);
	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
	ft_putendl_fd(s_pipex->args[0], STDERR_FILENO);
	s_pipex->exit_status = COMMAND_NOT_FOUND;
	ft_quit(s_pipex);
}

static void	ft_exec_last_cmd(t_pipex *s_pipex)
{
	int	res[2];

	s_pipex->pid_last = fork();
	if (s_pipex->pid_last < 0)
	{
		s_pipex->exit_status = EXIT_FAILURE;
		return (perror("fork error"));
	}
	if (s_pipex->pid_last != 0)
		return ;
	res[0] = dup2(s_pipex->fd[0], STDIN_FILENO);
	res[1] = dup2(s_pipex->fd_out, STDOUT_FILENO);
	ft_close(4, s_pipex->fd_in, s_pipex->fd_out, \
		s_pipex->fd[0], s_pipex->fd[1]);
	if (res[0] == -1 || res[1] == -1)
	{
		s_pipex->exit_status = EXIT_FAILURE;
		ft_quit(s_pipex);
	}
	ft_parse_args(s_pipex, s_pipex->argv[s_pipex->argc - 2]);
	execve(s_pipex->path_cmd, s_pipex->args, s_pipex->envp);
	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
	ft_putendl_fd(s_pipex->args[0], STDERR_FILENO);
	s_pipex->exit_status = COMMAND_NOT_FOUND;
	ft_quit(s_pipex);
}

static void	ft_wait(t_pipex *s_pipex)
{
	int		wstatus;

	waitpid(s_pipex->pid_first, &wstatus, 0);
	waitpid(s_pipex->pid_last, &wstatus, 0);
	if (WIFEXITED(wstatus))
		s_pipex->exit_status = WEXITSTATUS(wstatus);
	else
		s_pipex->exit_status = EXIT_FAILURE;
}
