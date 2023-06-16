/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:14:58 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/15 13:27:52 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parse_args(t_pipex *s_pipex, char *argv)
{
	s_pipex->args = ft_split(argv, ' ');
	if (s_pipex->args == NULL)
		perror("ft_split");
	ft_check_path_cmd(s_pipex);
}

void	ft_check_path_cmd(t_pipex *s_pipex)
{
	int	i;

	if (s_pipex->args == NULL)
		return ;
	i = 0;
	if (s_pipex->args[0] != NULL && s_pipex->args[0][0] != '/')
		s_pipex->path_cmd = ft_strjoin(s_pipex->path[i], s_pipex->args[0]);
	else
		s_pipex->path_cmd = s_pipex->args[0];
	if (s_pipex->path_cmd == NULL)
	{
		perror("ft_strjoin");
		return ;
	}
	while (s_pipex->path_cmd != NULL \
		&& access(s_pipex->path_cmd, F_OK | X_OK) != 0)
	{
		++i;
		free(s_pipex->path_cmd);
		s_pipex->path_cmd = ft_strjoin(s_pipex->path[i], s_pipex->args[0]);
	}
}
