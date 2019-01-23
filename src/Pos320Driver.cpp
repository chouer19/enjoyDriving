#include <stdio.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/endian/arithmetic.hpp>
#include "msgs/POS320.pb.h"

using namespace boost::endian;

int main(int argc, char **argv){
  std::cout<<"pos320's driver is ready runing now!\n";

  Pos_msg::pos320 msg;

  std::cout.precision(11);
  std::cout.precision(9);

  /// defination of serial port for pos320
  /// set options for pos320_sp
  boost::asio::io_service io;
  boost::asio::serial_port pos320_sp(io,"/dev/ttyUSB0");
  pos320_sp.set_option(boost::asio::serial_port_base::baud_rate(115200));
  pos320_sp.set_option(boost::asio::serial_port_base::character_size(8));
  pos320_sp.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
  pos320_sp.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
  pos320_sp.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
  boost::system::error_code ec;
  /// open serial port
  pos320_sp.open("/dev/ttyUSB0", ec );
  if( !pos320_sp.is_open()){
    std::cout<< "port not opened" << std::endl;
  }
  std::cout<< "port opened" << std::endl;

  bool is_initialized = false;

  while(true)
  {
    /// read pos32 data from serial port
    unsigned char c = 0;
    boost::asio::read(pos320_sp, boost::asio::buffer(&c, 1));
    if (0xaa != c && !is_initialized) {
       /// initializing
       if(c != 83){
         std::cout<<"Initializing, " << (int)c/ 2 <<"\% completed ......" << std::endl;
       }
       if(c == 200){is_initialized = true;}
       continue;
    }
    boost::asio::read(pos320_sp, boost::asio::buffer(&c, 1));
    if (0x55 != c) {
       continue;
    }
    unsigned short length;
    boost::asio::read(pos320_sp, boost::asio::buffer(&length, sizeof(length)));
    msg.set_length(length);

    unsigned short mode;
    boost::asio::read(pos320_sp, boost::asio::buffer(&mode, sizeof(mode)));
    msg.set_mode(mode);

    unsigned short time1;
    boost::asio::read(pos320_sp, boost::asio::buffer(&time1, sizeof(time1)));
    msg.set_time1(time1);

    unsigned short time2;
    boost::asio::read(pos320_sp, boost::asio::buffer(&time2, sizeof(time2)));
    msg.set_time2(time2);

    unsigned short num;
    boost::asio::read(pos320_sp, boost::asio::buffer(&num, sizeof(num)));
    msg.set_num(num);

    double lat;
    boost::asio::read(pos320_sp, boost::asio::buffer(&lat, sizeof(lat)));
    msg.set_num(num);

    double lon;
    boost::asio::read(pos320_sp, boost::asio::buffer(&lon, sizeof(lon)));
    msg.set_num(num);

    float height;
    boost::asio::read(pos320_sp, boost::asio::buffer(&height, sizeof(height)));
    msg.set_num(num);

    float v_n;
    boost::asio::read(pos320_sp, boost::asio::buffer(&v_n, sizeof(v_n)));
    msg.set_num(num);

    float v_e;
    boost::asio::read(pos320_sp, boost::asio::buffer(&v_e, sizeof(v_e)));
    msg.set_num(num);

    float v_earth;
    boost::asio::read(pos320_sp, boost::asio::buffer(&v_earth, sizeof(v_earth)));
    msg.set_num(num);

    float roll;
    boost::asio::read(pos320_sp, boost::asio::buffer(&roll, sizeof(roll)));
    msg.set_num(num);

    float pitch ;
    boost::asio::read(pos320_sp, boost::asio::buffer(&pitch, sizeof(pitch)));
    msg.set_pitch(pitch/100);

    float head  ;
    boost::asio::read(pos320_sp, boost::asio::buffer(&head, sizeof(head)));
    msg.set_num(num);

    short a_n   ;
    boost::asio::read(pos320_sp, boost::asio::buffer(&a_n, sizeof(a_n)));
    msg.set_num(num);

    short a_e   ;
    boost::asio::read(pos320_sp, boost::asio::buffer(&a_e, sizeof(a_e)));
    msg.set_num(num);

    short a_earth;
    boost::asio::read(pos320_sp, boost::asio::buffer(&a_earth, sizeof(a_earth)));
    msg.set_num(num);

    short v_roll;
    boost::asio::read(pos320_sp, boost::asio::buffer(&v_roll, sizeof(v_roll)));
    msg.set_num(num);

    short v_pitch;
    boost::asio::read(pos320_sp, boost::asio::buffer(&v_pitch, sizeof(v_pitch)));
    msg.set_num(num);

    short v_head;
    boost::asio::read(pos320_sp, boost::asio::buffer(&v_head, sizeof(v_head)));
    msg.set_num(num);

    char status;
    boost::asio::read(pos320_sp, boost::asio::buffer(&status, sizeof(status)));
    //msg.set_status(status);

    int status1 = (status & 0xC0) >> 6;
    msg.set_status1(status1);

    int status2 = status & 0x3f;
    msg.set_status2(status2);

    boost::asio::read(pos320_sp, boost::asio::buffer(&c, 1));
    msg.set_num(num);


    std::cout<< lat<< "\t"<< lon << "\n";

  }

  return 0;
}
