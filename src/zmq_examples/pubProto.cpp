//
//  Pubsub envelope publisher
//  Note that the zhelpers.h file also provides s_sendmore
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include <iostream>

#include "zmq/zhelpers.hpp"
#include "Vehicle.pb.h"

int main () {
    //  Prepare our context and publisher
    std::cout << "Function of pubPrto..." << std::endl;
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5563");
    //publisher.bind("tcp://*:5563");
    Car_msg::Ruicheng_control control;
    control.set_targetsteeringangle(0);
    control.set_targetspeed(6);
    std::string buff;
    control.SerializeToString(&buff);

    while (1) {
        //  Write two messages, each with an envelope and content
        s_sendmore (publisher, "control_frame");
        s_send (publisher, buff);
        s_sendmore (publisher, "B");
        s_send (publisher, "We would like to see this");
        sleep (1);
    }
    return 0;
}
