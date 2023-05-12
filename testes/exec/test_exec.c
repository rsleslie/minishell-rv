//#include "../../minishell.h"
#include "exec.h"
// ls | grep exec.h | wc -l
char    ***tokens = (char **[]){ 
                        (char *[]){"/usr/bin/ls", 0},
                        (char *[]){"|", 0},
                        (char *[]){"/usr/bin/grep", "exec.h", 0},
                        (char *[]){"|", 0},
                        (char *[]){"/usr/bin/wc", "-l", 0},
                        0
                    };
char buf[1000];
t_exec *g_exec;

t_exec *values(void)
{
    g_exec->cmd = (char *[]){"/usr/bin/ls", 0};
    g_exec->redirect = NULL;
    g_exec->is_builtin = NULL;
    g_exec->index = 0;
    g_exec->
}

void run_test1()
{
    int i;
    int bkp;
    bzero((char *)buf, 1000);
    int fd = open("test1.txt", O_RDWR | O_CREAT, S_IRWXU);
    bkp = dup(1);
	dup2(fd, 1);
    exec(tokens);
	dup2(bkp, 1);

    fd = open("test1.txt", O_RDONLY);
    read(fd, &buf, 1000);
    if (strncmp("name\n", (char *)buf, 6) == 0)
        printf("Deu Bom!\n");
    else
        printf("Deu Ruim! :(\n");
}

void run_test2()
{
    // int i;
    // int bkp;
    // bzero((char *)buf, 1000);
    // int fd = open("test2.txt", O_RDWR | O_CREAT, S_IRWXU);
    // bkp = dup(1);
	// dup2(fd, 1);
    // exec(tokens);
	// dup2(bkp, 1);

    // fd = open("test2.txt", O_RDONLY);
    // read(fd, &buf, 1000);
    // if (strncmp("name\n", (char *)buf, 6) == 0)
    //     printf("Deu Bom!\n");
    // else
    //     printf("Deu Ruim! :(\n");
    exec(tokens);
}

int main()
{
    // run_test1();
    //sleep(1);
    run_test2();
    //sleep(1);
}