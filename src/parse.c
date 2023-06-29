/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:14:58 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/29 01:45:44 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void		ft_parse_args(t_pipex *pipex, char *argv);
static void	ft_check_path_cmd(t_pipex *pipex);

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
		pipex->path_cmd = pipex->args[0];
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
