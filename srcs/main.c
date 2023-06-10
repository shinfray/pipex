/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:59:53 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/10 11:49:12 by shinfray         ###   ########.fr       */
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
	close(s_pipex.fd_in);
	close(s_pipex.fd_out);
	close(s_pipex.fd[0]);
	close(s_pipex.fd[1]);
	ft_wait(&s_pipex);
	ft_quit(&s_pipex);
}

static void	ft_exec_first_cmd(t_pipex *s_pipex)
{
	int	res[2];

	s_pipex->pid_first = fork();
	if (s_pipex->pid_first < 0)
	{
		perror("fork error");
		s_pipex->exit_status = EXIT_FAILURE;
		return ;
	}
	if (s_pipex->pid_first != 0)
		return ;
	close(s_pipex->fd[0]);
	close(s_pipex->fd_out);
	res[0] = dup2(s_pipex->fd_in, STDIN_FILENO);
	res[1] = dup2(s_pipex->fd[1], STDOUT_FILENO);
	close(s_pipex->fd_in);
	close(s_pipex->fd[1]);
	if (res[0] == -1 || res[1] == -1)
		exit(EXIT_FAILURE);
	ft_parse_args(s_pipex, s_pipex->argv[2]);
	ft_check_path_cmd(s_pipex);
	execve(s_pipex->path_cmd, s_pipex->args, s_pipex->envp);
	ft_putstr_fd("pipex: command not found: ", 2);
	if (s_pipex->args[0] != NULL)
		ft_putendl_fd(s_pipex->args[0], 2);
	exit(COMMAND_NOT_FOUND);
}

static void	ft_exec_last_cmd(t_pipex *s_pipex)
{
	int	res[2];

	s_pipex->pid_last = fork();
	if (s_pipex->pid_last < 0)
	{
		perror("fork error");
		s_pipex->exit_status = EXIT_FAILURE;
		return ;
	}
	if (s_pipex->pid_last != 0)
		return ;
	close(s_pipex->fd[1]);
	close(s_pipex->fd_in);
	res[0] = dup2(s_pipex->fd[0], STDIN_FILENO);
	res[1] = dup2(s_pipex->fd_out, STDOUT_FILENO);
	close(s_pipex->fd_out);
	close(s_pipex->fd[0]);
	if (res[0] == -1 || res[1] == -1)
		exit(EXIT_FAILURE);
	ft_parse_args(s_pipex, s_pipex->argv[s_pipex->argc - 2]);
	ft_check_path_cmd(s_pipex);
	execve(s_pipex->path_cmd, s_pipex->args, s_pipex->envp);
	ft_putstr_fd("pipex: command not found: ", 2);
	if (s_pipex->args[0] != NULL)
		ft_putendl_fd(s_pipex->args[0], 2);
	exit(COMMAND_NOT_FOUND);
}

static void	ft_wait(t_pipex *s_pipex)
{
	int		wstatus;

	waitpid(s_pipex->pid_first, &wstatus, 0);
	if (WIFEXITED(wstatus))
		s_pipex->exit_status = WEXITSTATUS(wstatus);
	waitpid(s_pipex->pid_last, &wstatus, 0);
	if (WIFEXITED(wstatus))
		s_pipex->exit_status = WEXITSTATUS(wstatus);
	else
		s_pipex->exit_status = EXIT_FAILURE;
}
