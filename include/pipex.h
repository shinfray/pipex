/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:58:52 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/28 20:32:11 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft.h"

# define COMMAND_NOT_FOUND 127

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
	char	*infile;
	char	*outfile;
	char	**args;
	char	*path_cmd;
	int		fd_in;
	int		fd_out;
	int		*fds;
	pid_t	pid_first;
	pid_t	pid_last;
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
void	ft_close(int count, ...);

#endif
