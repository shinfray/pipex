/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:59:53 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/02 16:00:23 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	int		i;

	(void)argc;
	(void)argv;
	path = ft_get_path(envp);
	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		printf("%s\n", path[i]);
		++i;
	}
	return (0);
}
