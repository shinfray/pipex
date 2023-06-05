/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:58:52 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/02 16:06:54 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_pipex
{
    int     **argv;
    char    **path;
    int     fd_in;
    int     fd_out;
    char    *infile;
    char    *outfile;
    char    **args_1;
    char    **args_2;
    char    *path_cmd1;
    char    *path_cmd2;
}               t_pipex;

char    **ft_get_path(char **envp);

#endif
