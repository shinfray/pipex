/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 01:18:58 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/30 13:33:29 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void		ft_exec_childs(t_pipex *pipex);
void		ft_wait(t_pipex *pipex);
static void	ft_redirect(int read, int write, t_pipex *pipex);

void	ft_createpipe(t_pipex *pipex)
{
	if (pipe(pipex->pipe) == -1)
	{
		perror("pipe creation");
		pipex->pipe[0] = -1;
		pipex->pipe[1] = -1;
	}
}

void	ft_exec_childs(t_pipex *pipex)
{
	const int	fd_to_read = pipex->pipe[0];
	pid_t		pid;
	int			fd_to_write;

	if (pipex->cmd_index < pipex->total_cmds - 1)
		ft_createpipe(pipex);
	else
		pipex->pipe[1] = pipex->fd_out;
	fd_to_write = pipex->pipe[1];
	pid = fork();
	if (pid == 0)
	{
		ft_redirect(fd_to_read, fd_to_write, pipex);
		if (pipex->cmd_index < pipex->total_cmds -1)
			close(pipex->pipe[0]);
		ft_parse_args(pipex, pipex->argv[2 + pipex->cmd_index + pipex->here_doc]);
		execve(pipex->path_cmd, pipex->args, pipex->envp);
		ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
		ft_putendl_fd(pipex->args[0], STDERR_FILENO);
		pipex->exit_status = COMMAND_NOT_FOUND;
		ft_quit(pipex);
	}
	ft_close(2, fd_to_read, fd_to_write);
	if (pid < 0)
	{
		pipex->exit_status = EXIT_FAILURE;
		perror("fork error");
	}
	if (pipex->cmd_index == pipex->total_cmds - 1)
		pipex->pid_last = pid;
}

void	ft_wait(t_pipex *pipex)
{
	int		wstatus;

	if (pipex->pid_last > 0)
	{
		waitpid(pipex->pid_last, &wstatus, 0);
		if (WIFEXITED(wstatus))
			pipex->exit_status = WEXITSTATUS(wstatus);
		else
			pipex->exit_status = EXIT_FAILURE;
	}
	else
		pipex->exit_status = EXIT_FAILURE;
	while (wait(NULL) != -1 || errno != ECHILD)
		;
}

static void	ft_redirect(int read, int write, t_pipex *pipex)
{
	int	res[2];

	res[0] = dup2(read, STDIN_FILENO);
	res[1] = dup2(write, STDOUT_FILENO);
	ft_close(2, read, write);
	if (res[0] == -1 || res[1] == -1)
	{
		pipex->exit_status = EXIT_FAILURE;
		ft_quit(pipex);
	}
}
