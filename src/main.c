/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:04:14 by shinfray          #+#    #+#             */
/*   Updated: 2023/08/25 11:13:58 by simonhinfray     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pipex;

	if (ft_check_format(argc, argv, &s_pipex) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_set_pipex(&s_pipex, argc, argv, envp);
	while (++s_pipex.cmd_index < s_pipex.total_cmds)
		ft_exec(&s_pipex);
	ft_wait(&s_pipex);
	ft_quit(&s_pipex);
}
