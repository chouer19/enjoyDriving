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

#define RADIANS_TO_DEGREES (180.0/M_PI)

int com_port_number;

int an_packet_transmit(an_packet_t *an_packet)
{
	an_packet_encode(an_packet);
	return SendBuf(com_port_number, an_packet_pointer(an_packet), an_packet_size(an_packet));
}

/*
 * This is an example of sending a configuration packet to Orientus.
 *
 * 1. First declare the structure for the packet, in this case sensor_ranges_packet_t.
 * 2. Set all the fields of the packet structure
 * 3. Encode the packet structure into an an_packet_t using the appropriate helper function
 * 4. Send the packet
 * 5. Free the packet
 */
void set_sensor_ranges()
{
	an_packet_t *an_packet;
	sensor_ranges_packet_t sensor_ranges_packet;

	sensor_ranges_packet.permanent = TRUE;
	sensor_ranges_packet.accelerometers_range = accelerometer_range_4g;
	sensor_ranges_packet.gyroscopes_range = gyroscope_range_500dps;
	sensor_ranges_packet.magnetometers_range = magnetometer_range_2g;

	an_packet = encode_sensor_ranges_packet(&sensor_ranges_packet);

	an_packet_transmit(an_packet);

	an_packet_free(&an_packet);
}

int main(int argc, char *argv[])
{
	an_decoder_t an_decoder;
	an_packet_t *an_packet;
	
        system_state_packet_t system_state_packet; // ID = 20
	status_packet_t status_packet; // ID = 23
	raw_sensors_packet_t raw_sensors_packet; // ID = 28
        //raw_gnss_packet_t raw_gnss_packet; // ID = 29
	euler_orientation_packet_t euler_orientation_packet; // ID = 39
        external_position_velocity_packet_t external_position_velocity_packet; // ID = 44
        external_position_packet_t external_position_packet; // ID = 45
        external_velocity_packet_t external_velocity_packet; // ID = 46
	
	int bytes_received;

	if (argc != 3)
	{
		printf("Usage - program com_port_number baud_rate\nExample - packet_example.exe 0 115200\n");
		exit(EXIT_FAILURE);
	}

	com_port_number = atoi(argv[1]);
	
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
				/*else if (an_packet->id == packet_id_raw_sensors) // ID = 28, raw sensors packet
				{
					// copy all the binary data into the typedef struct for the packet 
					// this allows easy access to all the different values             
					if(decode_raw_sensors_packet(&raw_sensors_packet, an_packet) == 0)
					{
						printf("Raw Sensors Packet:\n");
						printf("\tAccelerometers X: %f Y: %f Z: %f\n", raw_sensors_packet.accelerometers[0], raw_sensors_packet.accelerometers[1], raw_sensors_packet.accelerometers[2]);
						printf("\tGyroscopes X: %f Y: %f Z: %f\n", raw_sensors_packet.gyroscopes[0] * RADIANS_TO_DEGREES, raw_sensors_packet.gyroscopes[1] * RADIANS_TO_DEGREES, raw_sensors_packet.gyroscopes[2] * RADIANS_TO_DEGREES);
					}
				}*/
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

				else
				{
					//printf("Packet ID %u of Length %u\n", an_packet->id, an_packet->length);
				}
				
				/* Ensure that you free the an_packet when your done with it or you will leak memory */
				an_packet_free(&an_packet);
			}
		}
#ifdef _WIN32
    Sleep(10);
#else
    usleep(10000);
#endif
	}
}
