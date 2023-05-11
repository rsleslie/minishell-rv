#include "../exec.h"
#include <errno.h>

void    pipex(int fd[2], int i)
{
    if (i == 0)
    {
        printf("if\n");
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        printf("if\n");
    }
    else
    {
        printf("else\n");
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        printf("else\n");
    }
}

void    exec(char ***tokens)
{
    extern char **environ;
    int pid;
    int i;
    int fd[2];
    int status = 0;

    i = -1;
    pipe(fd);
    while (tokens[++i])
    {
        if (strncmp(tokens[i][0], "|", 2) == 0)
            continue;
        pid = fork();
        if (pid == 0)
        {
            pipex(fd, i);
            if (execve(tokens[i][0], tokens[i], environ) == -1)
                perror(strerror(errno));
        }
    }
    close(fd[0]);
    close(fd[1]);
    i = -1;
    while (++i < 2)
    {
        waitpid(pid, &status, 0);
    } 
}