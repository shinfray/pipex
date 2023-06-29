/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:04:14 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/29 15:02:19 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_format(int argc, char **argv, t_pipex *pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pipex;

	if (ft_check_format(argc, argv, &s_pipex) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_set_pipex(&s_pipex, argc, argv, envp);
	ft_create_pipes(&s_pipex);
	while (++s_pipex.pipe_index < s_pipex.total_cmds)
		ft_exec_childs(&s_pipex);
	ft_close_pipes(&s_pipex);
	ft_wait(&s_pipex);
	ft_quit(&s_pipex);
}
