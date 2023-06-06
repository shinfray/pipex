#include "pipex.h"

char    **ft_get_path(char **envp)
{
    char    **path;

    if (envp == NULL)
    {
        ft_putendl_fd("PATH unavailable", 2);
        exit(EXIT_FAILURE);
    }
    path = NULL;
    while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5) != 0)
        (*envp)++;
	if (*envp == NULL)
    {
        ft_putendl_fd("PATH unavailable", 2);
        exit(EXIT_FAILURE);
    }
	path = ft_split(*envp + 5, ':');
	if (path == NULL)
	{
		perror("split");
		exit(EXIT_FAILURE);
	}
    return (path);
}

static void	ft_free_double_ptr(char **tab)
{
	char	**ptr;

	ptr = tab;
	while (*tab != NULL)
		free(*tab++);
	free(ptr);
}

void	ft_quit(t_pipex *s_pipex)
{
	// if (s_pipex->fd[0] != -1)
	// 	close(s_pipex->fd[0]);
	// if (s_pipex->fd[1] != -1)
	// 	close(s_pipex->fd[1]);
	free(s_pipex->path_cmd1);
	free(s_pipex->path_cmd2);
	if (s_pipex->path != NULL)
		ft_free_double_ptr(s_pipex->path);
	if (s_pipex->args_1 != NULL)
		ft_free_double_ptr(s_pipex->args_1);
	if (s_pipex->args_2 != NULL)
		ft_free_double_ptr(s_pipex->args_2);
	if (s_pipex->exit_status == EXIT_FAILURE)
		perror("pipex");
	exit(s_pipex->exit_status);
}


void	ft_set_pipex(t_pipex *s_pipex, int argc, char **argv, char **envp)
{
	s_pipex->exit_status = EXIT_FAILURE;
	s_pipex->argv = argv;
	s_pipex->envp = envp;
	s_pipex->path = ft_get_path(envp);
	s_pipex->infile = argv[1];
	s_pipex->outfile = argv[argc - 1];
	s_pipex->args_1 = NULL;
	s_pipex->args_2 = NULL;
	s_pipex->path_cmd1 = NULL;
	s_pipex->path_cmd2 = NULL;
	s_pipex->fd[0] = -1;
	s_pipex->fd[1] = -1;
	s_pipex->fd_out = -1;
	s_pipex->fd_in = -1;
}