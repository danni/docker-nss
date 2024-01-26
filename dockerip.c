#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    // run if one argument was supplied that does not start with '-'
    if (argc == 2 && strnlen(argv[1], 255) > 2 && argv[1][0] != '-') {
        const char* myargs[] = { "/usr/bin/docker", "inspect", "--format={{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}", argv[1] };
        return execlp(myargs[0], myargs[0], myargs[1], myargs[2], myargs[3], NULL);
    }
    printf("usage: %s <container>\n", argv[0]);
    return 1;
}
