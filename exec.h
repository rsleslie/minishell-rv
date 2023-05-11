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