//======================================================================
/*! \file TjuBusAcc.cpp
 * \copy from file
 *
 * \copydoc Copyright
 * \author Xue Chong(xc)
 * \date March 28, 2019
 *
 * project for test DA DO control
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

void wait(int milliseconds)
{
  boost::this_thread::sleep_for(boost::chrono::milliseconds{milliseconds});
}

int main(){
    // definations about zmq
    zmq::context_t context(1);
    char address[sizeof("127.127.127.127:8888")+1];
    char topic[255];
    int ret;
    ret = getAddressTopic("main", address, topic);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind(address);
    Car_msg::Common_control control_msg;
    double voltage = 3.69;
    control_msg.set_targetacceleration(voltage);
    std::string buff;
    while(1){
        std::cin >> voltage;
        control_msg.set_targetacceleration(voltage);
        s_sendmore(publisher, topic);
        control_msg.SerializeToString(&buff);
        s_send(publisher, buff);
        //wait(900);
    }
}
