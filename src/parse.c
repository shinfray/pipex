/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:14:58 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/10 09:47:12 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int			ft_check_format(int argc, char **argv, t_pipex *pipex);
void		ft_parse_args(t_pipex *pipex, char *argv);
static void	ft_check_path_cmd(t_pipex *pipex);

int	ft_check_format(int argc, char **argv, t_pipex *pipex)
{
	const char	*err1 = "Usage: ./pipex file cmd ... cmd file";
	const char	*err2 = "Usage: ./pipex here_doc LIMITER file cmd ... cmd file";

	pipex->here_doc = (argc > 1 && ft_strncmp(argv[1], "here_doc", 9) == 0);
	if (pipex->here_doc == 0 && argc < 5)
	{
		ft_putendl_fd(err1, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (pipex->here_doc == 1 && argc < 6)
	{
		ft_putendl_fd(err2, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}

void	ft_parse_args(t_pipex *pipex, char *argv)
{
	pipex->args = ft_split(argv, ' ');
	if (pipex->args == NULL)
		perror("ft_split");
	ft_check_path_cmd(pipex);
}

static void	ft_check_path_cmd(t_pipex *pipex)
{
	int	i;

	if (pipex->args == NULL)
		return ;
	i = 0;
	if (pipex->args[0] != NULL && pipex->args[0][0] != '/')
		pipex->path_cmd = ft_strjoin(pipex->path[i], pipex->args[0]);
	else
		pipex->path_cmd = ft_strdup(pipex->args[0]);
	if (pipex->path_cmd == NULL)
	{
		perror("ft_strjoin");
		return ;
	}
	while (pipex->path_cmd != NULL && access(pipex->path_cmd, F_OK | X_OK) != 0)
	{
		++i;
		free(pipex->path_cmd);
		pipex->path_cmd = ft_strjoin(pipex->path[i], pipex->args[0]);
	}
}
