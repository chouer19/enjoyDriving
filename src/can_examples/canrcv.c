#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <libgen.h>
#include <time.h>
#include <errno.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <net/if.h>

#include "can/can.h"
#include "can/raw.h"

#include "can/terminal.h"
#define ANYDEV "any"  /* name of interface to receive from any CAN interface */

const int canfd_on = 1;

static volatile int running = 1;


void sigterm(int signo)
{
	running = 0;
}

int main(int argc, char **argv)
{
	fd_set rdfs;
	int sckt;
	unsigned char extra_msg_info = 0;
	unsigned char color = 0;
	int count = 0;
	int rcvbuf_size = 0;
	char *ptr;
	struct sockaddr_can addr;
	char ctrlmsg[CMSG_SPACE(sizeof(struct timeval) + 3*sizeof(struct timespec) + sizeof(__u32))];
	struct iovec iov;
	struct msghdr msg;
	struct cmsghdr *cmsg;
	struct canfd_frame frame;
	int nbytes;
	struct ifreq ifr;
        struct timeval timeout, timeout_config = { 0, 0 }, *timeout_current = NULL;
        int ret = 0;

	signal(SIGTERM, sigterm);
	signal(SIGHUP, sigterm);
	signal(SIGINT, sigterm);

	ptr = argv[1];

	sckt = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (sckt < 0) {
		perror("socket");
		return 1;
	}

 	nbytes = strlen(ptr); /* no ',' found => no filter definitions */

	addr.can_family = AF_CAN;

	memset(&ifr.ifr_name, 0, sizeof(ifr.ifr_name));
	strncpy(ifr.ifr_name, ptr, nbytes);

	if (strcmp(ANYDEV, ifr.ifr_name)) {
		if (ioctl(sckt, SIOCGIFINDEX, &ifr) < 0) {
                        perror("aaaaaaaa");
			perror("SIOCGIFINDEX");
			exit(1);
		}
		addr.can_ifindex = ifr.ifr_ifindex;
	} else{
		addr.can_ifindex = 0; /* any can interface */
        }

	/* try to switch the socket into CAN FD mode */
	setsockopt(sckt, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &canfd_on, sizeof(canfd_on));

	if (rcvbuf_size) { // 2. rcvbuf_size
		int curr_rcvbuf_size;
		socklen_t curr_rcvbuf_size_len = sizeof(curr_rcvbuf_size);

		/* try SO_RCVBUFFORCE first, if we run with CAP_NET_ADMIN */
		if (setsockopt(sckt, SOL_SOCKET, SO_RCVBUFFORCE,
			       &rcvbuf_size, sizeof(rcvbuf_size)) < 0) {
			if (setsockopt(sckt, SOL_SOCKET, SO_RCVBUF,
				       &rcvbuf_size, sizeof(rcvbuf_size)) < 0) {
				perror("setsockopt SO_RCVBUF");
				return 1;
			}

			if (getsockopt(sckt, SOL_SOCKET, SO_RCVBUF,
				       &curr_rcvbuf_size, &curr_rcvbuf_size_len) < 0) {
				perror("getsockopt SO_RCVBUF");
				return 1;
			}
		}
	} // 2. rcvbuf_size end

	if (bind(sckt, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		return 1;
	}

	/* these settings are static and can be held out of the hot path */
	iov.iov_base = &frame;
	msg.msg_name = &addr;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = &ctrlmsg;

	while (running) {

		FD_ZERO(&rdfs);
		FD_SET(sckt, &rdfs);

                if ((ret = select(sckt + 1, &rdfs, NULL, NULL, timeout_current)) <= 0) {
                        //perror("select");
                        running = 0;
                        continue;
                }


		if (FD_ISSET(sckt, &rdfs)) { // 3.0 FD_ISSET
			int idx;
			/* these settings may be modified by recvmsg() */
			iov.iov_len = sizeof(frame);
			msg.msg_namelen = sizeof(addr);
			msg.msg_controllen = sizeof(ctrlmsg);  
			msg.msg_flags = 0;

			nbytes = recvmsg(sckt, &msg, 0);
                        for(int datai = 0; datai<8; datai++){
                            printf("0x%0x ",frame.data[datai]);
                        }
                        printf("\n");
		}
	}
        close(sckt);
	return 0;
}
