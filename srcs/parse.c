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

void	ft_parse_args(t_pipex *s_pipex, char *args)
{
	s_pipex->args = ft_split(args, ' ');
	if (s_pipex->args == NULL)
		perror("ft_split");
}

void	ft_check_path_cmd(t_pipex *s_pipex)
{
	int	i;

	i = 0;
	s_pipex->path_cmd = ft_strjoin(s_pipex->path[i], s_pipex->args[0]);
	if (s_pipex->path_cmd == NULL)
		return (perror("ft_strjoin"));
	while (s_pipex->path_cmd != NULL \
		&& access(s_pipex->path_cmd, F_OK | X_OK) != 0)
	{
		++i;
		free(s_pipex->path_cmd);
		s_pipex->path_cmd = ft_strjoin(s_pipex->path[i], s_pipex->args[0]);
	}
}
