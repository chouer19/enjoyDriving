
#include <stdio.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/endian/arithmetic.hpp>
#include "msgs/Pos.pb.h"
#include "config/config.h"

using namespace boost::endian;

int main(int argc, char **argv){

  std::cout<< VERSION_MAJOR << std::endl;
  std::cout<< ADDRESS_CFG_PATH << std::endl;

  return 0;
}
