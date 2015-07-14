#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {

	// run if one argument was supplied that does not start with '-'
	if (argc == 2 && argv[1][0] != '-') {
		const char *myargs[] = {"/usr/bin/docker", "inspect", "--format={{.NetworkSettings.IPAddress}}", argv[1] };
        	return execlp(myargs[0], myargs[0], myargs[1], myargs[2], myargs[3], NULL);
	}
	return 0;
}

