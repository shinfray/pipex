/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:58:52 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/30 13:08:45 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line_bonus.h"

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
	int		pipe[2];
	int		total_cmds;
	int		cmd_index;
	pid_t	pid_last;
	int		here_doc;
	int		exit_status;
}				t_pipex;

/*	SET_PIPEX FUNCTIONS	*/
void	ft_set_pipex(t_pipex *pipex, int argc, char **argv, char **envp);

/*	HERE_DOC FUNCTIONS	*/
int		ft_here_doc(char **argv);

/*	PARSE FUNCTIONS	*/
int		ft_check_format(int argc, char **argv, t_pipex *pipex);
void	ft_parse_args(t_pipex *pipex, char *args);

/*	PIPES FUNCTIONS	*/
// void	ft_create_pipes(t_pipex *pipex);
// void	ft_close_pipes(t_pipex *pipex);

/*	CHILD_PROCESS FUNCTIONS	*/
void	ft_exec_childs(t_pipex *pipex);
void	ft_wait(t_pipex *pipex);

/*	UTILS FUNCTIONS	*/
void	ft_quit(t_pipex *pipex);
void	*ft_free_double_ptr(char **tab);
void	ft_close(int count, ...);

#endif
