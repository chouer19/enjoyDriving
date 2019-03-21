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


/* from #include <linux/net_tstamp.h> - since Linux 2.6.30 */
#define SOF_TIMESTAMPING_SOFTWARE (1<<4)
#define SOF_TIMESTAMPING_RX_SOFTWARE (1<<3)
#define SOF_TIMESTAMPING_RAW_HARDWARE (1<<6)

#define MAXSOCK 16    /* max. number of CAN interfaces given on the cmdline */
#define MAXIFNAMES 30 /* size of receive name index to omit ioctls */
#define MAXCOL 6      /* number of different colors for colorized output */
#define ANYDEV "any"  /* name of interface to receive from any CAN interface */
#define ANL "\r\n"    /* newline in ASC mode */

#define SILENT_INI 42 /* detect user setting on commandline */
#define SILENT_OFF 0  /* no silent mode */
#define SILENT_ANI 1  /* silent mode with animation */
#define SILENT_ON  2  /* silent mode (completely silent) */

#define BOLD    ATTBOLD
#define RED     ATTBOLD FGRED
#define GREEN   ATTBOLD FGGREEN
#define YELLOW  ATTBOLD FGYELLOW
#define BLUE    ATTBOLD FGBLUE
#define MAGENTA ATTBOLD FGMAGENTA
#define CYAN    ATTBOLD FGCYAN

const char col_on [MAXCOL][19] = {BLUE, RED, GREEN, BOLD, MAGENTA, CYAN};
const char col_off [] = ATTRESET;

static char devname[MAXIFNAMES][IFNAMSIZ+1];
static int  dindex[MAXIFNAMES];
static int  max_devname_len; /* to prevent frazzled device name output */ 
const int canfd_on = 1;

#define MAXANI 4
const char anichar[MAXANI] = {'|', '/', '-', '\\'};
const char extra_m_info[4][4] = {"- -", "B -", "- E", "B E"};

static volatile int running = 1;


void sigterm(int signo)
{
	running = 0;
}

int idx2dindex(int ifidx, int socket) {

	int i;
	struct ifreq ifr;

	for (i=0; i < MAXIFNAMES; i++) {
		if (dindex[i] == ifidx)
			return i;
	}

	/* create new interface index cache entry */

	/* remove index cache zombies first */
	for (i=0; i < MAXIFNAMES; i++) {
		if (dindex[i]) {
			ifr.ifr_ifindex = dindex[i];
			if (ioctl(socket, SIOCGIFNAME, &ifr) < 0)
				dindex[i] = 0;
		}
	}

	for (i=0; i < MAXIFNAMES; i++)
		if (!dindex[i]) /* free entry */
			break;

	if (i == MAXIFNAMES) {
		fprintf(stderr, "Interface index cache only supports %d interfaces.\n",
		       MAXIFNAMES);
		exit(1);
	}

	dindex[i] = ifidx;

	ifr.ifr_ifindex = ifidx;
	if (ioctl(socket, SIOCGIFNAME, &ifr) < 0)
		perror("SIOCGIFNAME");

	if (max_devname_len < strlen(ifr.ifr_name))
		max_devname_len = strlen(ifr.ifr_name);

	strcpy(devname[i], ifr.ifr_name);

#ifdef DEBUG
	printf("new index %d (%s)\n", i, devname[i]);
#endif

	return i;
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

	if (nbytes > max_devname_len){
		max_devname_len = nbytes; /* for nice printing */
        }

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
