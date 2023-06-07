/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:58:52 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/07 10:13:54 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	char	**path;
	char	*infile;
	char	*outfile;
	char	**args;
	char	*path_cmd;
	int		fd_in;
	int		fd_out;
	int		fd[2];
	int		pid1;
	int		pid2;
	int		exit_status;
}				t_pipex;

/*	SET_PIPEX FUNCTIONS	*/
void	ft_set_pipex(t_pipex *s_pipex, int argc, char **argv, char **envp);

/*	PARSE FUNCTIONS	*/
void	ft_parse_args(t_pipex *s_pipex, char *args);
void	ft_check_path_cmd(t_pipex *s_pipex);

/*	UTILS FUNCTIONS	*/
void	ft_quit(t_pipex *s_pipex);
void	*ft_free_double_ptr(char **tab);

#endif
