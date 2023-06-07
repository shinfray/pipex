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

void	ft_quit(t_pipex *s_pipex);
void	*ft_free_double_ptr(char **tab);

void	ft_quit(t_pipex *s_pipex)
{
	if (s_pipex->path != NULL)
		ft_free_double_ptr(s_pipex->path);
	exit(s_pipex->exit_status);
}

void	*ft_free_double_ptr(char **tab)
{
	char	**ptr;

	ptr = tab;
	while (*tab != NULL)
		free(*tab++);
	free(ptr);
	return (NULL);
}
