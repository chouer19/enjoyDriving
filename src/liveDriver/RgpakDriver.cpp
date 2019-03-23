//======================================================================
/*! \file OrientusDriver.cpp
 * \copy from file orientus_examples
 *
 * \copydoc Copyright
 * \author Xue Chong(xc)
 * \date March 16, 2019
 *
 * project for connecting RGPack982 and process the received
 * datas.
 *///-------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <signal.h>
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "rs232/rs232.h"
#include "orientus/an_packet_protocol.h"
#include "orientus/orientus_packets.h"
#include "msgs/Pos.pb.h"
#include "zmq/zhelpers.hpp"
#include "config/config.h"
#include "common/address.h"
#define RADIANS_TO_DEGREES (180.0/M_PI)

char comports[22][13]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3","/dev/ttyS4","/dev/ttyS5",
                       "/dev/ttyS6","/dev/ttyS7","/dev/ttyS8","/dev/ttyS9","/dev/ttyS10","/dev/ttyS11",
                       "/dev/ttyS12","/dev/ttyS13","/dev/ttyS14","/dev/ttyS15","/dev/ttyUSB0",
                       "/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5"};

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
        fprintf(stderr, "         -p <port>         (serial port machine)\n");
        fprintf(stderr, "         -b <baundrate>    (baundrate of serial port)\n\n");
}

int main(int argc, char *argv[])
{
    signal(SIGTERM, sigterm);
    signal(SIGHUP, sigterm);
    signal(SIGINT, sigterm);

    /* print usage of this process */
    print_usage(basename(argv[0]));
    /* get address and topic from config file "address.json" */
    char address[sizeof("127.127.127.127:8888")+1];
    char topic[255];
    int ret = getAddressTopic(basename(argv[0]), address, topic);
    printf("node is : %s\n",basename(argv[0]));
    printf("address is : %s\n",address);
    printf("topic is : %s\n",topic);
    /* message and publisher */
    Pos_msg::common_pos orientus_msg;
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind(address);
    /* default config for serial port machine and its rate */
    int com_port_number = 16;
    int baudRate = 115200;
    /* log */
    int log = 0;
    char logname[sizeof("orientus-2019-03-23_16:36:26.log")+1];
    
    // encode, packet
    an_decoder_t an_decoder;
    an_packet_t *an_packet;
    int bytes_received;
    
    /* Orientus packet */
    system_state_packet_t system_state_packet; // ID = 20
    status_packet_t status_packet; // ID = 23
    euler_orientation_standard_deviation_packet_t euler_orientation_standard_deviation_packet; // ID = 26
    raw_sensors_packet_t raw_sensors_packet; // ID = 28
    euler_orientation_packet_t euler_orientation_packet; // ID = 39
    external_position_velocity_packet_t external_position_velocity_packet; // ID = 44
    external_position_packet_t external_position_packet; // ID = 45
    external_velocity_packet_t external_velocity_packet; // ID = 46
    

    int opt = 0;
    while ((opt = getopt(argc, argv, "p:b:l")) != -1) {
        switch (opt) {
            case 'p':{
                for(int i=0; i < 22;i++){
                    if(!strcmp(optarg,comports[i])){
                        com_port_number = i;
                        break;
                    }
                }
                break;
            }
            case 'b':{
                baudRate = atoi(optarg);
                break;
            }
            case 'l':{
                log = 1;
                time_t now = time(0);
                tm *ltm = localtime(&now);
                sprintf(logname,"Orientus-%d-%02d-%02d_%02d:%02d:%02d.log",1900+ltm->tm_year, ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                break;
            }
            default:{
                break;
            }
        }
    }
    printf("\nport name is : %s\n",comports[com_port_number]);
    printf("baudRate is : %d\n",baudRate);
    printf("logfile is : %s\n\n",logname);
    
    /* open the com port */
    if (OpenComport(com_port_number, baudRate))
    {
    	exit(EXIT_FAILURE);
    }
    
    an_decoder_initialise(&an_decoder);
    
    while (running)
    {// big while start
        if ((bytes_received = PollComport(com_port_number, an_decoder_pointer(&an_decoder), an_decoder_size(&an_decoder))) > 0)
        {// if byte received start
            an_decoder_increment(&an_decoder, bytes_received);
            /* decode all the packets in the buffer */
            while ((an_packet = an_packet_decode(&an_decoder)) != NULL){// 1. an packet decode start
                if(an_packet->id == packet_id_system_state){ /* ID = 20, system state packet */
                    if(decode_system_state_packet(&system_state_packet, an_packet) == 0){
                        printf("System State Packet:\n");
                        printf("\tOrientation: Roll = %f, Pitch = %f, Heading = %f \n", system_state_packet.orientation[0],system_state_packet.orientation[1],system_state_packet.orientation[2]);
                        orientus_msg.clear_orientation();
                        orientus_msg.add_orientation(system_state_packet.orientation[0]);
                        orientus_msg.add_orientation(system_state_packet.orientation[1]);
                        orientus_msg.add_orientation(system_state_packet.orientation[2]);
                    }
                }else if(an_packet->id == packet_id_euler_orientation_standard_deviation){ // ID = 26, orientation deviation
                    if(decode_euler_orientation_standard_deviation_packet(&euler_orientation_standard_deviation_packet, an_packet) == 0){
                        printf("Euler orientation standard deviation packet:\n");
                        printf("\tDeviation: sigmaRoll = %f, sigmaPitch = %f, sigmaYaw = %f\n", euler_orientation_standard_deviation_packet.standard_deviation[0], euler_orientation_standard_deviation_packet.standard_deviation[1], euler_orientation_standard_deviation_packet.standard_deviation[2]);
                        orientus_msg.clear_orientationdeviation();
                        orientus_msg.add_orientationdeviation(euler_orientation_standard_deviation_packet.standard_deviation[0]);
                        orientus_msg.add_orientationdeviation(euler_orientation_standard_deviation_packet.standard_deviation[1]);
                        orientus_msg.add_orientationdeviation(euler_orientation_standard_deviation_packet.standard_deviation[2]);
                    }
                }else if (an_packet->id == packet_id_euler_orientation){ /*ID = 39, system state packet */
                    if(decode_euler_orientation_packet(&euler_orientation_packet, an_packet) == 0){
                        printf("Euler Orientation Packet:\n");
                        printf("\tRoll = %f, Pitch = %f, Yaw = %f\n", euler_orientation_packet.orientation[0] * RADIANS_TO_DEGREES, euler_orientation_packet.orientation[1] * RADIANS_TO_DEGREES, euler_orientation_packet.orientation[2] * RADIANS_TO_DEGREES);
                        orientus_msg.clear_orientation();
                        orientus_msg.add_orientation(euler_orientation_packet.orientation[0]);
                        orientus_msg.add_orientation(euler_orientation_packet.orientation[1]);
                        orientus_msg.add_orientation(euler_orientation_packet.orientation[2]);
                    }
                }else if(an_packet->id == packet_id_external_position_velocity){ // ID = 44
                    if(decode_external_position_velocity_packet(&external_position_velocity_packet, an_packet) == 0){
                        printf("Euler Orientation Packet:\n");
                        printf("\tLat = %f, Lon = %f, Height = %f\n", external_position_velocity_packet.position[0] * RADIANS_TO_DEGREES, external_position_velocity_packet.position[1] * RADIANS_TO_DEGREES, external_position_velocity_packet.position[2]);
                        orientus_msg.clear_position();
                        orientus_msg.add_position(external_position_velocity_packet.position[0]);
                        orientus_msg.add_position(external_position_velocity_packet.position[1]);
                        orientus_msg.add_position(external_position_velocity_packet.position[2]);
                        orientus_msg.clear_positiondeviation();
                        orientus_msg.add_positiondeviation(external_position_velocity_packet.position_standard_deviation[0]);
                        orientus_msg.add_positiondeviation(external_position_velocity_packet.position_standard_deviation[1]);
                        orientus_msg.add_positiondeviation(external_position_velocity_packet.position_standard_deviation[2]);
                        orientus_msg.clear_velocity();
                        orientus_msg.add_velocity(external_position_velocity_packet.velocity[0]);
                        orientus_msg.add_velocity(external_position_velocity_packet.velocity[1]);
                        orientus_msg.add_velocity(external_position_velocity_packet.velocity[2]);
                        orientus_msg.clear_velocitydeviation();
                        orientus_msg.add_velocitydeviation(external_position_velocity_packet.velocity_standard_deviation[0]);
                        orientus_msg.add_velocitydeviation(external_position_velocity_packet.velocity_standard_deviation[1]);
                        orientus_msg.add_velocitydeviation(external_position_velocity_packet.velocity_standard_deviation[2]);

                        std::string buf;
                        orientus_msg.SerializeToString(&buf);
                        s_sendmore (publisher, topic);
                        s_send (publisher, buf);

                        if(log){
                            ;
                        }
                    }
                }// if byte received start
                /* Ensure that you free the an_packet when your done with it or you will leak memory */
                an_packet_free(&an_packet);
            }// 1. an packet decode end
        }
#ifdef _WIN32
        Sleep(10);
#else
    // 1 s = 1 000 000 us, 10HZ = 1/1 00 000us, 20HZ = 1/ 50 000us
        usleep(10000);
#endif
    }// big while end
}
