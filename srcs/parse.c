/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:14:58 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/06 20:16:54 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parse_args(t_pipex *s_pipex)
{
	s_pipex->args_1 = ft_split(s_pipex->argv[2], ' ');
	s_pipex->args_2 = ft_split(s_pipex->argv[3], ' ');
	if (s_pipex->args_1 == NULL || s_pipex->args_2 == NULL)
		ft_quit(s_pipex);
}

void	ft_check_path_cmd1(t_pipex *s_pipex)
{
	int	i;

	i = 0;
	s_pipex->path_cmd1 = ft_strjoin(s_pipex->path[i], s_pipex->args_1[0]);
	if (s_pipex->path_cmd1 == NULL)
		ft_quit(s_pipex);
	while (s_pipex->path_cmd1 != NULL \
		&& access(s_pipex->path_cmd1, F_OK | X_OK) != 0)
	{
		++i;
		free(s_pipex->path_cmd1);
		s_pipex->path_cmd1 = ft_strjoin(s_pipex->path[i], s_pipex->args_1[0]);
	}
	if (s_pipex->path_cmd1 == NULL)
	{
		write(2, "pipex: command not found: ", 26);
		ft_putendl_fd(s_pipex->args_1[0], 2);
	}
}

void	ft_check_path_cmd2(t_pipex *s_pipex)
{
	int	i;

	i = 0;
	s_pipex->path_cmd2 = ft_strjoin(s_pipex->path[i], s_pipex->args_2[0]);
	if (s_pipex->path_cmd2 == NULL)
		ft_quit(s_pipex);
	while (s_pipex->path_cmd2 != NULL \
		&& access(s_pipex->path_cmd2, F_OK | X_OK) != 0)
	{
		++i;
		free(s_pipex->path_cmd2);
		s_pipex->path_cmd2 = ft_strjoin(s_pipex->path[i], s_pipex->args_2[0]);
	}
	if (s_pipex->path_cmd2 == NULL)
	{
		write(2, "pipex: command not found: ", 26);
		ft_putendl_fd(s_pipex->args_2[0], 2);
	}
}
