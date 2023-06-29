/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:04:14 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/29 11:53:26 by shinfray         ###   ########.fr       */
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

int	ft_check_format(int argc, char **argv, t_pipex *pipex)
{
	if (argc > 1 && ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipex->here_doc == 1;
	else
		pipex->here_doc == 0;
	if (pipex->here_doc == 0 && argc < 5)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2  ... cmd5 outfile", 2);
		return (EXIT_FAILURE);
	}
	else if (pipex->here_doc == 1 && argc < 6)
	{
		ft_putendl_fd("Usage: ./pipex here_doc LIMITER infile cmd1 cmd2  ... cmd5 outfile", 2);
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}
