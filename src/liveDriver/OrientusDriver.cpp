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

#define RADIANS_TO_DEGREES (180.0/M_PI)


char comports[22][13]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3","/dev/ttyS4","/dev/ttyS5",
                       "/dev/ttyS6","/dev/ttyS7","/dev/ttyS8","/dev/ttyS9","/dev/ttyS10","/dev/ttyS11",
                       "/dev/ttyS12","/dev/ttyS13","/dev/ttyS14","/dev/ttyS15","/dev/ttyUSB0",
                       "/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5"};

int main(int argc, char *argv[])
{
        int com_port_number = 16;
        int baudRate = 115200;
        int log = 0;
        char logname[sizeof("orientus-2019-03-23_163626.log")+1];
	an_decoder_t an_decoder;
	an_packet_t *an_packet;
	
        system_state_packet_t system_state_packet; // ID = 20
	status_packet_t status_packet; // ID = 23
	euler_orientation_standard_deviation_packet_t euler_orientation_standard_deviation_packet; // ID = 26
	raw_sensors_packet_t raw_sensors_packet; // ID = 28
	euler_orientation_packet_t euler_orientation_packet; // ID = 39
        external_position_velocity_packet_t external_position_velocity_packet; // ID = 44
        external_position_packet_t external_position_packet; // ID = 45
        external_velocity_packet_t external_velocity_packet; // ID = 46
	
	int bytes_received;

        while ((opt = getopt(argc, argv, "c:b:l")) != -1) {
            switch (opt) {
                case 'c':{
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
                    break;
                }
                default:{
                    break;
                }
            }
        }
        printf("port name is : %s\n",comport[com_port_number]);
        printf("baudRate is : %d\n",baudRate);
        printf("logfile is : %s\n",logname);

	/* open the com port */
	if (OpenComport(com_port_number, atoi(argv[2])))
	{
		exit(EXIT_FAILURE);
	}
	
	an_decoder_initialise(&an_decoder);

	while (1)
	{
		if ((bytes_received = PollComport(com_port_number, an_decoder_pointer(&an_decoder), an_decoder_size(&an_decoder))) > 0)
		{
			/* increment the decode buffer length by the number of bytes received */
			an_decoder_increment(&an_decoder, bytes_received);
			
			/* decode all the packets in the buffer */
			while ((an_packet = an_packet_decode(&an_decoder)) != NULL)
			{
				if(an_packet->id == packet_id_system_state) /* ID = 20, system state packet */
				{
					if(decode_system_state_packet(&system_state_packet, an_packet) == 0)
					{
						printf("System State Packet:\n");
						printf("\tOrientation: Roll = %f, Pitch = %f, Heading = %f \n", system_state_packet.orientation[0],system_state_packet.orientation[1],system_state_packet.orientation[2]);
					}
				}
				/*else if(an_packet->id == packet_id_status) // ID = 23, status packet 
				{
					if(decode_status_packet(&status_packet, an_packet) == 0)
					{
						printf("Status Packet:\n");
						printf("\tFilter Ready = %d\n", status_packet.filter_status.b.orientation_filter_initialised);
					}
				}*/
                                else if(an_packet->id == packet_id_euler_orientation_standard_deviation){ // ID = 26, orientation deviation
                                        if(decode_euler_orientation_standard_deviation_packet(euler_orientation_standard_deviation_packet) == 0){
                                                printf("Euler orientation standard deviation packet:\n");
                                                printf("\tDeviation: sigmaRoll = %f, sigmaPitch = %f, sigmaYaw = %f\n", euler_orientation_standard_deviation_packet.standard_deviation[0], euler_orientation_standard_deviation_packet.standard_deviation[1], euler_orientation_standard_deviation_packet.standard_deviation[2]);
                                        }
                                }
				else if (an_packet->id == packet_id_euler_orientation) /*ID = 39, system state packet */
				{
					/* copy all the binary data into the typedef struct for the packet */
					/* this allows easy access to all the different values             */
					if(decode_euler_orientation_packet(&euler_orientation_packet, an_packet) == 0)
					{
						printf("Euler Orientation Packet:\n");
						printf("\tRoll = %f, Pitch = %f, Yaw = %f\n", euler_orientation_packet.orientation[0] * RADIANS_TO_DEGREES, euler_orientation_packet.orientation[1] * RADIANS_TO_DEGREES, euler_orientation_packet.orientation[2] * RADIANS_TO_DEGREES);
					}
				}
                                else if(an_packet->id == packet_id_external_position_velocity) // ID = 44
                                {
					/* copy all the binary data into the typedef struct for the packet */
					/* this allows easy access to all the different values             */
					if(decode_external_position_velocity_packet(&external_position_velocity_packet, an_packet) == 0)
					{
						printf("Euler Orientation Packet:\n");
						printf("\tLat = %f, Lon = %f, Height = %f\n", external_position_velocity_packet.position[0] * RADIANS_TO_DEGREES, external_position_velocity_packet.position[1] * RADIANS_TO_DEGREES, external_position_velocity_packet.position[2]);
					}
                                
                                }

				/* Ensure that you free the an_packet when your done with it or you will leak memory */
				an_packet_free(&an_packet);
			}
		}
#ifdef _WIN32
    Sleep(10);
#else
    // 1 s = 1 000 000 us, 10HZ = 1/1 00 000us, 20HZ = 1/ 50 000us
    usleep(10000);
#endif
	}
}
