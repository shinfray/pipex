#include "pipex.h"

char    **ft_get_path(char **envp)
{
    char    **path;

    if (envp == NULL)
    {
        ft_putendl_fd("PATH unavailable", 2);
        return (NULL);
    }
    path = NULL;
    while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5) != 0)
        (*envp)++;
    if (*envp != NULL)
    {
        path = ft_split(*envp + 5, ':');
        if (path == NULL)
        {
            perror("split");
            exit(EXIT_FAILURE);
        }
    }
    return (path);
}

int **ft_init_pipe(int argc)
{
    int **fd;

    fd = ft_calloc((argc - 2) * 2, sizeof(int));
    while (argc - 2 > 0)
    {
        pipe(*fd);
    }
}