//======================================================================
/*! \file TjuBusAcc.cpp
 * \copy from file
 *
 * \copydoc Copyright
 * \author Xue Chong(xc)
 * \date March 26, 2019
 *
 * project for connecting DA DO control
 * wheel rotate by controlling voltage
 *///-------------------------------------------------------------------

#include <iostream>
#include "zmq/zhelpers.hpp"
#include "config/config.h"
#include "common/address.h"

#include "msgs/Vehicle.pb.h"

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <signal.h>
#include <ctime>

void print_usage(char *prg);
void thread_sub();
int CaculateCRC(unsigned char * data);
int CaculateWriteDO(int addr, int io, int voltage, unsigned char *data);
static volatile int running = 1;
int logg = 0;
void sigterm(int signo)
{
    running = 0;
}

// definations about boost serial_port
boost::asio::io_service io;
boost::asio::serial_port serial(io);

// definations about zmq
zmq::context_t context(1);

int main(int argc, char ** argv){
    int baudRate = 115200;
    std::string portName = "/dev/ttyUSB0";
    int opt = 0;
    while ((opt = getopt(argc, argv, "p:t:r:l")) != -1) {
        switch (opt) {
            case 'p':{
                portName = optarg;
                break;
            }
            case 'b':{
                baudRate= atoi(optarg);
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
    serial.set_option(boost::asio::serial_port_base::baud_rate(baudRate));
    serial.open(portName);

    return 1;
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

void thread_sub(){
    char address[sizeof("127.127.127.127:8888")+1];
    char topic[255];
    int ret;
    ret = getAddressTopic("main", address, topic);
    Car_msg::Common_control control_msg;

    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect(address);
    subscriber.setsockopt( ZMQ_SUBSCRIBE, topic, 1);
    double accVoltage = 0;

    unsigned char data[8] = {0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00};
    while(running){
        std::string address = s_recv (subscriber);
        std::string buff = s_recv (subscriber);
        control_msg.ParseFromString(buff);
        accVoltage = control_msg.targetacceleration();
        CaculateWriteDO(200, 0, accVoltage , data);
        boost::asio::write(serial , boost::asio::buffer(data, 8));
    }
}

unsigned short crcTable[256] = {
    0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241, 
    0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440, 
    0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40, 
    0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841, 
    0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40, 
    0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41, 
    0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641, 
    0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040, 
    0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240, 
    0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441, 
    0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41, 
    0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840, 
    0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41, 
    0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40, 
    0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640, 
    0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041, 
    0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240, 
    0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441, 
    0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41, 
    0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840, 
    0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41, 
    0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40, 
    0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640, 
    0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041, 
    0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241, 
    0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440, 
    0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40, 
    0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841, 
    0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40, 
    0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41, 
    0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641, 
    0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040
};

int CaculateCRC(unsigned char * data){
    unsigned char crc = 0xff;
    unsigned char tableIndex = 0;
    for(int i=0; i<6; i++){
        tableIndex = (unsigned char)(crc ^ data[i]);
        crc >> 8;
        crc ^= crcTable[tableIndex];
    }
    data[6] = (unsigned char)(crc & 0xff);
    data[7] = (unsigned char)(crc >> 8);
    return 1;
}

int CaculateWriteDO(int addr, int io, int voltage, unsigned char *data){
    data[0] = (unsigned char)addr;
    data[1] = 0x06;
    data[2] = 0x00;
    data[3] = (unsigned char)io;
    data[4] = (unsigned char)(voltage / 256);
    data[5] = (unsigned char)(voltage % 256);
    return CaculateCRC(data);
    //return 1;
}
