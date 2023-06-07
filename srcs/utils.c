/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:20:37 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/06 19:30:59 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void		ft_set_path(t_pipex *s_pipex);
void		ft_quit(t_pipex *s_pipex);
static void	ft_free_double_ptr(char **tab);

void	ft_set_path(t_pipex *s_pipex)
{
	int	i;

	i = 0;
	while (s_pipex->path[i] != NULL)
	{
		s_pipex->path[i] = ft_strjoin(s_pipex->path[i], "/");
		if (s_pipex->path[i] == NULL)
			ft_quit(s_pipex);
		++i;
	}	
}

void	ft_quit(t_pipex *s_pipex)
{
	free(s_pipex->path_cmd1);
	free(s_pipex->path_cmd2);
	if (s_pipex->path != NULL)
		ft_free_double_ptr(s_pipex->path);
	if (s_pipex->args_1 != NULL)
		ft_free_double_ptr(s_pipex->args_1);
	if (s_pipex->args_2 != NULL)
		ft_free_double_ptr(s_pipex->args_2);
	exit(s_pipex->exit_status);
}

static void	ft_free_double_ptr(char **tab)
{
	char	**ptr;

	ptr = tab;
	while (*tab != NULL)
		free(*tab++);
	free(ptr);
}
