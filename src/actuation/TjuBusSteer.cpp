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

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

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

int s; /* can raw socket */
static volatile int running = 1;
int logg = 0;
zmq::context_t context(1);

const int canfd_on = 1;
struct sockaddr_can addr;
canid_t pc2ecu_id = 0x469;
canid_t ecu2pc_id = 0x401;

void sigterm(int signo)
{
        running = 0;
}

void wait(int milliseconds)
{
  boost::this_thread::sleep_for(boost::chrono::milliseconds{milliseconds});
}

void print_usage(char *prg)
{
        fprintf(stderr, "\nUsage: %s [options] <parameter>+\n", prg);
        fprintf(stderr, "  (use CTRL-C to terminate %s)\n\n", prg);
        fprintf(stderr, "Options: -l                (use log function)\n");
        fprintf(stderr, "         -p <port>         (can port machine)\n");
        fprintf(stderr, "         -t <id>           (can id)\n\n");
        fprintf(stderr, "         -r <id>           (can id)\n\n");
}

void sub_thread(){
    char address[sizeof("127.127.127.127:8888")+1];
    char topic[255]; 
    int ret;
    ret = getAddressTopic("main", address, topic);
    Car_msg::Common_control control_msg;

    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect(address);
    subscriber.setsockopt( ZMQ_SUBSCRIBE, topic, 1);

    struct canfd_frame write_frame;
    write_frame.can_id = pc2ecu_id;
    int required_mtu = 16;
    /* parse CAN frame */
    required_mtu = parse_canframe("5A1#1122334455667788", &write_frame);

    while(running){
        std::string address = s_recv (subscriber);
        std::string buff = s_recv (subscriber);
        control_msg.ParseFromString(buff);
        write_frame.data[0] = control_msg.steeringmode(); // 0: stop control, 0x10: manul control, 0x20: pc contol
        write_frame.data[1] = 0x00; // reserved
        write_frame.data[2] = 0x02; // reserved
        write_frame.data[3] = (control_msg.targetsteeringangle() + 1024) / 256;
        write_frame.data[4] = (control_msg.targetsteeringangle() + 1024) % 256;
        write_frame.data[5] = 0x00;
        write_frame.data[6] = 0x00;
        write_frame.data[7] = write_frame.data[0]
                            ^ write_frame.data[1] 
                            ^ write_frame.data[2] 
                            ^ write_frame.data[3] 
                            ^ write_frame.data[4] 
                            ^ write_frame.data[5] 
                            ^ write_frame.data[6];

        /* send frame */
        if (write(s, &write_frame, required_mtu) != required_mtu) {
                perror("write");
                //return 1;
                continue;
        }
    }
}

void pub_thread(char ** argv){
    struct canfd_frame read_frame;
    fd_set rdfs;
    struct iovec iov;
    struct msghdr msg;
    struct cmsghdr *cmsg;
    char ctrlmsg[CMSG_SPACE(sizeof(struct timeval) + 3*sizeof(struct timespec) + sizeof(__u32))];
    struct timeval *timeout_current = NULL;

    /* these settings are static and can be held out of the hot path */
    iov.iov_base = &read_frame;
    msg.msg_name = &addr;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = &ctrlmsg;

    char address[sizeof("127.127.127.127:8888")+1];
    char topic[255];
    int ret = getAddressTopic(basename(argv[0]), address, topic);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind(address);
    Car_msg::Common_feedback back_msg;
    std::string buff;

    char logname[sizeof("deke-2019-03-23_16:36:26.log")+1];
    if(logg){
    //if(1){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        sprintf(logname,"Orientus-%d-%02d-%02d_%02d:%02d:%02d.log",1900+ltm->tm_year, ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    }

    while(running){
        FD_ZERO(&rdfs);
        FD_SET(s, &rdfs);

        if ((select(s + 1, &rdfs, NULL, NULL, timeout_current)) <= 0) {
            //perror("select");
            running = 0;
            continue;
        }
        if (FD_ISSET(s, &rdfs)) { // 3.0 FD_ISSET
            /* these settings may be modified by recvmsg() */
            iov.iov_len = sizeof(read_frame);
            msg.msg_namelen = sizeof(addr);
            msg.msg_controllen = sizeof(ctrlmsg);
            msg.msg_flags = 0;
            if(recvmsg(s, &msg, 0) > 0){
                for(int datai = 0; datai<8; datai++){
                    printf("0x%0x ",read_frame.data[datai]);
                }
                printf("\n");
                // frame_id ?
                back_msg.set_steer(read_frame.data[3] * 256 - read_frame.data[4]);
                back_msg.SerializeToString(&buff);
                s_sendmore(publisher, topic);
                s_sendmore(publisher, buff);
                if(logg){
                //if(1){
                    ;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    signal(SIGTERM, sigterm);
    signal(SIGHUP, sigterm);
    signal(SIGINT, sigterm);

    int enable_canfd = 1;
    struct ifreq ifr;
    strncpy(ifr.ifr_name, "can0", IFNAMSIZ - 1);

    int opt = 0;
    while ((opt = getopt(argc, argv, "p:t:r:l")) != -1) {
        switch (opt) {
            case 'p':{
                strncpy(ifr.ifr_name, optarg, IFNAMSIZ - 1);
                break;
            }
            case 't':{
                pc2ecu_id= atoi(optarg);
                break;
            }
            case 'r':{
                ecu2pc_id= atoi(optarg);
                break;
            }
            case 'l':{
                logg = 1;
                break;
            }
            default:{
                break;
            }
        }
    }


    /* open socket */
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
            perror("socket");
            return 1;
    }
    // assign can port name, like can0, can1, ......
    ifr.ifr_name[IFNAMSIZ - 1] = '\0';
    ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
    if (!ifr.ifr_ifindex) {
            perror("if_nametoindex");
            return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    /* try to switch the socket into CAN FD mode */
    setsockopt(s, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &canfd_on, sizeof(canfd_on));
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }

    boost::thread t_pub{pub_thread, argv};
    boost::thread t_sub{sub_thread};

    while (running) {
        wait(500);
    }

    t_pub.join();
    t_sub.join();

    return 0;
}
