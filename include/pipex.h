/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:58:52 by shinfray          #+#    #+#             */
/*   Updated: 2023/07/04 23:31:05 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line_bonus.h"

# define COMMAND_NOT_FOUND 127

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	char	**path;
	char	*infile;
	char	*outfile;
	char	**args;
	char	*path_cmd;
	int		argc;
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	int		total_cmds;
	int		cmd_index;
	int		here_doc;
	int		exit_status;
	pid_t	pid_last;
}				t_pipex;

/*	SET_PIPEX FUNCTIONS	*/
void	ft_set_pipex(t_pipex *pipex, int argc, char **argv, char **envp);

/*	HERE_DOC FUNCTIONS	*/
int		ft_here_doc(char **argv);

/*	PARSE FUNCTIONS	*/
int		ft_check_format(int argc, char **argv, t_pipex *pipex);
void	ft_parse_args(t_pipex *pipex, char *args);

/*	CHILD_PROCESS FUNCTIONS	*/
void	ft_exec(t_pipex *pipex);
void	ft_wait(t_pipex *pipex);

/*	UTILS FUNCTIONS	*/
void	ft_quit(t_pipex *pipex);
void	*ft_free_double_ptr(char **tab);

#endif
