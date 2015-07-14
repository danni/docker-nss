#include <unistd.h>

int main(int argc, char** argv)
{
    if (argc > 1) {
        const char* myargs[] = { "/usr/bin/docker", "inspect", "--format={{.NetworkSettings.IPAddress}}", argv[1] };
        return execlp(myargs[0], myargs[0], myargs[1], myargs[2], myargs[3], NULL);
    }
    return 0;
}
