/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:20:37 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/27 15:17:37 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_quit(t_pipex *s_pipex);
void	*ft_free_double_ptr(char **tab);
void	ft_close(int count, ...);

void	ft_quit(t_pipex *s_pipex)
{
	if (s_pipex->path != NULL)
		ft_free_double_ptr(s_pipex->path);
	if (s_pipex->args != NULL)
		ft_free_double_ptr(s_pipex->args);
	exit(s_pipex->exit_status);
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

void	ft_close(int count, ...)
{
	va_list			ap;

	va_start(ap, count);
	while (count-- > 0)
		close(va_arg(ap, int));
	va_end(ap);
}
