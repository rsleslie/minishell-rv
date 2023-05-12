#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

void    exec(char ***tokens);

typedef struct s_exec {
    char    **cmd;
    char    **redirect;
    int     is_builtin;
    int     index;
    struct s_exec *next;
}   t_exec;
