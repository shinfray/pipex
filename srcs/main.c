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

void	ft_open_files(t_pipex *s_pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pipex;

	if (argc != 5)
		return (0);
	s_pipex.argv = argv;
	s_pipex.path = ft_get_path(envp);
	s_pipex.infile = argv[1];
	s_pipex.outfile = argv[argc - 1];
	ft_open_files(&s_pipex);




	return (0);
}

void	ft_open_files(t_pipex *s_pipex)
{
	if (access(s_pipex->infile, F_OK | R_OK) != 0)
		return ;
	s_pipex->fd_in = open(s_pipex->infile, O_RDONLY);
	if (s_pipex->fd_in == -1)
		return ;
	if (dup2(s_pipex->fd_in, 0) == -1)	
		return ;
}

void	ft_parse_args(t_pipex *s_pipex)
{
	s_pipex->args_1 = ft_split(s_pipex->argv[2], ' ');
	s_pipex->args_2 = ft_split(s_pipex->argv[3], ' ');
	if (s_pipex->args_1 == NULL || s_pipex->args_2 == NULL)
		return ;
}

void	ft_set_path(t_pipex *s_pipex)
{
	int	i;

	i = 0;
	s_pipex->path[i] = ft_strjoin(s_pipex->path[i], "\\");
	if (s_pipex->path[i] = NULL)
		return ;

}