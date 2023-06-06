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
	free(s_pipex->path_cmd1);
	free(s_pipex->path_cmd2);
	if (s_pipex->path != NULL)
		ft_free_double_ptr(s_pipex->path);
	if (s_pipex->args_1 != NULL)
		ft_free_double_ptr(s_pipex->args_1);
	if (s_pipex->args_2 != NULL)
		ft_free_double_ptr(s_pipex->args_2);
	if (errno != 0)
		perror("pipex");
	exit(EXIT_FAILURE);
}