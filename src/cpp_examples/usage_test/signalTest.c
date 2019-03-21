#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <libgen.h>
#include <time.h>

static volatile int running = 1;

void sigterm(int signo)
{
	running = 0;
}

int main(int argc, char **argv)
{
	signal(SIGTERM, sigterm);
	signal(SIGHUP, sigterm);
	signal(SIGINT, sigterm);

	while (running) {
            printf("running......\n");
            printf("\n");
	}
        printf("done ......\n");
	return 0;
}
