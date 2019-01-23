//
//  Pubsub envelope subscriber
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include <iostream>

#include "zmq/zhelpers.hpp"
#include "RuiCheng.pb.h"

int main () {
    //  Prepare our context and subscriber
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "control_frame", 1);

    Car_msg::Ruicheng_control control;

    while (1) {
 
		//  Read envelope with address
		std::string address = s_recv (subscriber);
		//  Read message contents
		std::string contents = s_recv (subscriber);

                control.ParseFromString(contents.c_str());


                std::cout<<"targetSteer is "<<control.targetsteeringangle() << std::endl;
                std::cout<<"targetSpeed is "<<control.targetspeed() << std::endl;
        std::cout << "[" << address << "] " << contents << std::endl;
    }
    return 0;
}
