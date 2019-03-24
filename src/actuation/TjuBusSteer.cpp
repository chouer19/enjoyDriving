//======================================================================
/*! \file TjuBusSteer.cpp
 * \copy from file
 *
 * \copydoc Copyright
 * \author Xue Chong(xc)
 * \date March 24, 2019
 *
 * project for connecting Deke Steering System
 * sub msg from others, pub msg to others, send CAN tu Deke
 *///-------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <stdint.h>
#include <math.h>
#include <signal.h>
#include <ctime>
#include "rs232/rs232.h"
#include "orientus/an_packet_protocol.h"
#include "orientus/orientus_packets.h"
#include "msgs/Vehicle.pb.h"
#include "zmq/zhelpers.hpp"
#include "config/config.h"
#include "common/address.h"

extern "C"{
#include "can/can.h"
#include "can/raw.h"
#include "can/lib.h"
}

static volatile int running = 1;

void sigterm(int signo)
{
        running = 0;
}

void print_usage(char *prg)
{
        fprintf(stderr, "\nUsage: %s [options] <parameter>+\n", prg);
        fprintf(stderr, "  (use CTRL-C to terminate %s)\n\n", prg);
        fprintf(stderr, "Options: -l                (use log function)\n");
        fprintf(stderr, "         -p <port>         (can port machine)\n");
        fprintf(stderr, "         -d <id>           (can id)\n\n");
}

int main(int argc, char **argv)
{
    signal(SIGTERM, sigterm);
    signal(SIGHUP, sigterm);
    signal(SIGINT, sigterm);

    /* print usage of this process */
    print_usage(basename(argv[0]));

    /* this node ,for pub */
    char address[sizeof("127.127.127.127:8888")+1];
    char topic[255];
    int ret = getAddressTopic(basename(argv[0]), address, topic);
    /* message and publisher */
    Car_msg::common_feedback deke_back_msg;
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind(address);

    /* message and subcriber */
    Car_msg::common_control deke_control_msg;
    ret = getAddressTopic("main", address, topic);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect(address);
    subscriber.setsockopt( ZMQ_SUBSCRIBE, topic, 1);

    int s; /* can raw socket */ 
    int required_mtu = 16;
    int mtu;
    int enable_canfd = 1;
    struct sockaddr_can addr;
    struct canfd_frame frame;
    struct ifreq ifr;
    
    /* parse CAN frame */
    required_mtu = parse_canframe("5A1#1122334455667788", &frame);
    if (!required_mtu){
        fprintf(stderr, "\nWrong CAN-frame format! Try:\n\n");
        fprintf(stderr, "    <can_id>#{data}            for 'classic' CAN 2.0 data frames\n");
        fprintf(stderr, "    <can_id>#R{len}            for 'classic' CAN 2.0 RTR frames\n");
        fprintf(stderr, "    <can_id>##<flags>{data}    for CAN FD frames\n\n");
        fprintf(stderr, "<can_id> can have 3 (SFF) or 8 (EFF) hex chars\n");
        fprintf(stderr, "{data} has 0..8 (0..64 CAN FD) ASCII hex-values (optionally");
        fprintf(stderr, " separated by '.')\n");
        fprintf(stderr, "{len} is an optional 0..8 value as RTR frames can contain a");
        fprintf(stderr, " valid dlc field\n");
        fprintf(stderr, "<flags> a single ASCII Hex value (0 .. F) which defines");
        fprintf(stderr, " canfd_frame.flags\n\n");
        fprintf(stderr, "e.g. 5A1#11.2233.44556677.88 / 123#DEADBEEF / 5AA# / ");
        fprintf(stderr, "123##1 / 213##311223344\n     1F334455#1122334455667788 / ");
        fprintf(stderr, "123#R / 00000123#R3\n\n");
        return 1;
    }
    
    /* open socket */
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("socket");
        return 1;
    }
    
    strncpy(ifr.ifr_name, argv[1], IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = '\0';
    ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
    if (!ifr.ifr_ifindex) {
        perror("if_nametoindex");
        return 1;
    }
    
    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    
    if (required_mtu > CAN_MTU) {
    
        /* check if the frame fits into the CAN netdevice */
        if (ioctl(s, SIOCGIFMTU, &ifr) < 0) {
            perror("SIOCGIFMTU");
            return 1;
        }
        mtu = ifr.ifr_mtu;
        
        if (mtu != CANFD_MTU) {
            printf("CAN interface is not CAN FD capable - sorry.\n");
            return 1;
        }
        
        /* interface is ok - try to switch the socket into CAN FD mode */
        if (setsockopt(s, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &enable_canfd, sizeof(enable_canfd))){
            printf("error when enabling CAN FD support\n");
            return 1;
        }
        
        /* ensure discrete CAN FD length values 0..8, 12, 16, 20, 24, 32, 64 */
        frame.len = can_dlc2len(can_len2dlc(frame.len));
    }
    
    /* disable default receive filter on this RAW socket */
    /* This is obsolete as we do not read from the socket at all, but for */
    /* this reason we can remove the receive list in the Kernel to save a */
    /* little (really a very little!) CPU usage.                          */
    setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);
    
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    	perror("bind");
    	return 1;
    }
    
    frame.can_id = 0x469;
    frame.data[0] = 0x89;
    frame.data[1] = 0x66;
    frame.data[2] = 0x89;
    frame.data[3] = 0x22;
    frame.data[4] = 0x89;
    frame.data[5] = 0x77;
    frame.data[6] = 0x89;
    frame.data[7] = 0x99;
    
    /* send frame */
    if (write(s, &frame, required_mtu) != required_mtu) {
    	perror("write");
    	return 1;
    }
    
    close(s);
    
    return 0;
}
