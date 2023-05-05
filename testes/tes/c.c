#include <unistd.h>

int main(int a, char **v, char **envp)
{

    write(1, "Antes\n", 6);
    execve("/usr/bin/clear", (char *[]){"clear", 0}, envp);
    write(1, "Depois\n", 7);
}