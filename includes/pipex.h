/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:58:52 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/06 17:09:40 by shinfray         ###   ########.fr       */
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
    char    **argv;
    char    **envp;
    char    **path;
    int     fd_in;
    int     fd_out;
    char    *infile;
    char    *outfile;
    char    **args_1;
    char    **args_2;
    char    *path_cmd1;
    char    *path_cmd2;
    int     fd[2];
    int     pid1;
    int     pid2;
}               t_pipex;

char    **ft_get_path(char **envp);
void	ft_quit(t_pipex *s_pipex);

#endif
