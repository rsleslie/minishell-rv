#include "exec.h"
#include <errno.h>

void    pipex(int **fd, int i, int status, int size_counter)
{
    if (i == 0)//par 
    {
        dup2(fd[0][1], 1);
        close(fd[0][1]);
        close(fd[0][0]);
    }
    else if (i == 4)
    {
        dup2(fd[1][0], 0);
        close(fd[1][0]);
        close(fd[1][1]);
    }
    else
    {
        dup2(fd[0][0], 0);

        dup2(fd[1][1], 1);

        close(fd[0][0]);
        close(fd[1][1]);
    }

}

/*
             1      2
    array {{fd1}, {fd2}, {fd3}, {fd4}}

*/

int pipe_counter(char ***tokens)
{
    int counter;
    int i;

    counter = 0;
    i = -1;
    while (tokens[++i])
    {
        if (strncmp(tokens[i][0], "|", 2) == 0)
            counter++;
    }
    return (counter);
}

void    exec(char ***tokens)
{
    extern char **environ;
    int pid;
    int i;
    int **fd;
    int status;

    status = 0;
    fd = (int **)malloc(sizeof(int[2]) * pipe_counter(tokens));
    if (!fd)
        ; //chama funcao de exec sem pipe
    i = -1;
    while (++i < pipe_counter(tokens))
    {
        fd[i] = (int *)malloc(sizeof(int) * 2);
        pipe(fd[i]);
    }
    i = -1;
    while (tokens[++i])
    {
        if (strncmp(tokens[i][0], "|", 2) == 0)
        {
            status++;
            printf("status:      %i\n", status);
            continue;
        }
        pid = fork();
        if (pid == 0)
        {
            pipex(fd, i, status, pipe_counter(tokens));
            if (execve(tokens[i][0], tokens[i], environ) == -1)
                perror(strerror(errno));
        }
        if (i == 0) {
            close(fd[0][1]);
        }
        if (i == 2) {
            close(fd[0][0]);
            close(fd[1][1]);
        }
    }
    i = -1;
    while (++i < pipe_counter(tokens))
    {
        close(fd[i][0]);
        close(fd[i][1]);
    }
    i = -1;
    status = 0;
    while (++i < 3)
    {
        waitpid(pid, &status, 0);
    } 
}