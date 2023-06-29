/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 01:18:58 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/29 13:49:17 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void		ft_exec_childs(t_pipex *pipex);
void		ft_wait(t_pipex *pipex);
static void	ft_chooses_pipes(t_pipex *pipex);
static void	ft_redirect(int read, int write, t_pipex *pipex);

void	ft_exec_childs(t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		pipex->exit_status = EXIT_FAILURE;
		perror("fork error");
		return ;
	}
	if (pid != 0)
	{
		if (pipex->pipe_index == pipex->total_cmds - 1)
			pipex->pid_last = pid;
		return ;
	}
	ft_chooses_pipes(pipex);
	ft_parse_args(pipex, pipex->argv[2 + pipex->pipe_index + pipex->here_doc]);
	execve(pipex->path_cmd, pipex->args, pipex->envp);
	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
	ft_putendl_fd(pipex->args[0], STDERR_FILENO);
	pipex->exit_status = COMMAND_NOT_FOUND;
	ft_quit(pipex);
}

void	ft_wait(t_pipex *pipex)
{
	int		wstatus;

	waitpid(pipex->pid_last, &wstatus, 0);
	if (WIFEXITED(wstatus))
		pipex->exit_status = WEXITSTATUS(wstatus);
	else
		pipex->exit_status = EXIT_FAILURE;
	while (wait(NULL) != -1 || errno != ECHILD)
		;
}

static void	ft_chooses_pipes(t_pipex *pipex)
{
	if (pipex->pipe_index == 0)
		ft_redirect(pipex->fd_in, pipex->fds[1], pipex);
	else if (pipex->pipe_index == pipex->total_cmds - 1)
		ft_redirect(pipex->fds[2 * pipex->pipe_index - 2], \
					pipex->fd_out, pipex);
	else
		ft_redirect(pipex->fds[2 * pipex->pipe_index - 2], \
					pipex->fds[2 * pipex->pipe_index + 1], pipex);
}

static void	ft_redirect(int read, int write, t_pipex *pipex)
{
	int	res[2];

	res[0] = dup2(read, STDIN_FILENO);
	res[1] = dup2(write, STDOUT_FILENO);
	ft_close_pipes(pipex);
	if (res[0] == -1 || res[1] == -1)
	{
		pipex->exit_status = EXIT_FAILURE;
		ft_quit(pipex);
	}
}
