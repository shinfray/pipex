/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:20:37 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/10 09:57:16 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_quit(t_pipex *pipex);
void	*ft_free_double_ptr(char **tab);

void	ft_quit(t_pipex *pipex)
{
	if (pipex->path != NULL)
		ft_free_double_ptr(pipex->path);
	if (pipex->args != NULL)
		ft_free_double_ptr(pipex->args);
	if (pipex->path != NULL)
		free(pipex->path_cmd);
	exit(pipex->exit_status);
}

void	*ft_free_double_ptr(char **ptr)
{
	char	**save;

	save = ptr;
	while (*ptr != NULL)
		free(*ptr++);
	free(save);
	return (NULL);
}
